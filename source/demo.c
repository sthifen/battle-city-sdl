// Using libs SDL, glibc
#include <SDL2/SDL.h> //SDL version 2.0
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>



#include <string.h>
#include <time.h>
#include <unistd.h>


#include <SDL2/SDL_ttf.h>




// This is a simple game that uses SDL to create a window and draw a block

// Numbers bitmap, some routines and and SDL initialization taken from
// https://github.com/flightcrank/pong

// Please follow the coding guidelines described in:
// https://users.ece.cmu.edu/~eno/coding/CCodingStandard.html

/* Do not use magic numbers in the code, define the meaning of the number
   in this section and the use the define across the code. This increases
   readability accross the code
*/
// tratto de sibir al master
// hola Isa esto es una prueba
//  The constants used to define the size of the window
#define SCREEN_WIDTH 1900// window height
#define SCREEN_HEIGHT 900 // window width
// The constants used for the movement of the block
#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3

// Block size that will be used for drawing on the screen
#define BLOCK_SIZE 50

// Coordinates of the starting player
#define PLAYER_START_X 700
#define PLAYER_START_Y 800

// For the return of the functions
#define SUCCESS 0
#define FAILURE 1

// Defines of the game states of each screen
#define START_SCREEN 0
#define LEVEL_1 1
#define GAME_OVER 2

// Defines for states
#define FALSE 0
#define TRUE 1

// The colors used in the game
#define BLACK 0x000000ff
#define WHITE 0xffffffff

// Timing delays
#define INPUT_DELAY_MS 500

// Time to render a frame in ms = 1000/60
#define FRAME_TIME_MS 16

// Movement diferential
#define MOVEMENT_DELTA 5

// Definimos el numero de bloques que vamos a dibujar
#define NumBlocks 4

#define SPECIAL_BLOCK 5 // Nuevo bloque especial con imagen

#define MAD_ENEMIES 20
#define ENEMIES_PER_WAVE 3



#define ENEMY_SPAWN_INTERVAL 5000 // Intervalo de aparición en milisegundos
#define MAX_ENEMIES 50 // Número máximo de enemigos simultáneos
#define NUM_SPAW_POINTS 6 // Numero de puntos de spawn de enemigos

////////////////////////////////////////////////

#define PROJECTILE_SPEED 5
#define ENEMY_BULLET_COOLDOWN 2000  // 2 segundos de cooldown
#define BULLET_SPEED 10  // Velocidad de las balas

#define PROJECTILE_SPEED_PLAYER (1/3)

int bulletSpeed = PROJECTILE_SPEED; // Variable to store the current bullet speed
int bulletSpeedPlayer = PROJECTILE_SPEED_PLAYER; // Variable to store the current bullet speed
int maxBullets = 2; // Variable to store the maximum number of bullets
int bulletDestroySteel = 0; // Variable to store if bullets can destroy steel
int bulletDamageBrick = 1; // Variable to store the damage bullets do to bricks



#define brick_texture_X_plus_block 32
#define brick_texture_X_minus_block 33
#define brick_texture_Y_plus_block 34
#define brick_texture_Y_minus_block 35


#define SPAWN0_animation_block  37 // Nuevo tipo de bloque para la bomb
#define SPAWN1_animation_block  38 // Nuevo tipo de bloque para la bomb
#define SPAWN2_animation_block  39 // Nuevo tipo de bloque para la bomb
#define SPAWN3_animation_block  40 // Nuevo tipo de bloque para la bomb

#define EXPLOSION 36 // Nuevo tipo de bloque para la bomba



#define SPAWN_FRAME_DELAY 100
#define NUM_SPAWN_FRAMES 4



//#define ENEMY_BULLET_COOLDOWN 5000// PARA CAMBIAR TIEMPO ENTRE CADA BALA  
Uint32 lastEnemyShotTime = 0; // Tiempo del ultimo disparo del enemigo
uint32_t lastEnemyShotTime2 = 0; // Tiempo del ultimo disparo del enemigo 
/////////////////////////////////////////////////////
Uint32 lastplayershoottime = 0; // Tiempo del ultimo disparo del jugador


#define MAP_WIDTH 40
#define MAP_HEIGHT 30




#define BLOCK_RED 0     // Bloque rojo (colisión)
#define BLOCK_GREEN 1   // Bloque verde (traspasable)
#define BLOCK_BLUE 2    // Bloque azul (colisión)
#define BLOCK_YELLOW 3  // Bloque amarillo (destructible)
#define BLOCK_WHITE 4   // Bloque blanco (colisión)
#define SPECIAL_BLOCK 5 // Bloque especial (colisión)
#define Pause_screen 6
#define BLOCK_ENEMY 6 // Nuevo tipo de bloque para los enemigos
#define BOMB_BLOCK 7 //NUEVO BLOQUE BOMBA  
#define HELMET_BLOCK 8 //NUEVO BLOQUE CASCO 


#define  vidas_texture_BLOCK 110 //NUEVO BLOQUE VIDAS
#define  tanques_texture_BLOCK 120 //NUEVO BLOQUE TANQUES
//#define NUM_Spaw_frames 4 // Numero de frames de spawn de enemigos<






#define NUM_SPAWN_FRAMES 4
#define SPAWN_FRAME_DELAY 100
#define SPAWN_ANIMATION_DURATION (NUM_SPAWN_FRAMES * SPAWN_FRAME_DELAY)




#define PLAYER_COOLDOWN 500 // Cooldown del jugador en milisegundos
///////////////////////////////////////////////////////////////////////                   
Uint32 shieldStartTime = 0; // Tiempo en que se activó el escudo/     //
int shieldActive = 0;       // 0: Sin escudo, 1: Escudo activo        //
                                                                      //
Uint32 helmetSpawnTime = 0; // Última vez que apareció un casco       //
int helmetX = -1, helmetY = -1; // Posición del casco                 //
int helmetActive = 0; // 1 si está en pantalla, 0 si no               // 
////////////////////////////////////////////////////////////////////////
#define TANQUE_PODER_BLOCK 9//NUEVO BLOQUE TANQUE DE PODER  
/////////////////////////////////////////////////////////////////////////////
Uint32 tanquePoderSpawnTime = 0;// Ultima vez que aparecio un tanque poder //
int tanquePoderX = -1, tanquePoderY = -1; // Posicion del tanque de poder  //
int tanquePoderActive = 0; // 1 si esta en pantalla, 0 si no               //
/////////////////////////////////////////////////////////////////////////////
#define TEMPORIZADOR_PODER_BLOCK 10  // Nuevo bloque 
int enemigosCongelados = 0, balasCongeladas = 0, disparoBloqueado = 0;
Uint32 temporizadorSpawnTime = 0;
Uint32 tiempoCongelacion = 0;
                                                                      //
///////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define PALA_BLOCK 11 //NUEVO BLOQUE PALA                                                                                      ///
Uint32 palaSpawnTime = 0;      // Tiempo de aparición de la pala                                                              ////
Uint32 palaEffectStartTime = 0; // Tiempo de inicio del efecto de la pala                                                      ///                                                                 
int palaX = -1, palaY = -1;    // Posición de la Pala en la matriz del mapa                                                    ///
int palaActive = 0;            // Estado de la pala (0 = no generada, 1 = esperando ser recogida, 2 = efecto activo)           ///                                                                                                                            ///                                                                                                                                                                                                                                  ///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define STAR_BLOCK 12                                                                                                          ///
#define MAX_POWER_LEVEL 13
Uint32 starSpawnTime = 0;      // Tiempo de aparición de la estrella
Uint32 starEffectStartTime = 0; // Tiempo de inicio del efecto de la estrella
int starX = -1, starY = -1;    // Posición de la estrella en el mapa
int starActive = 0;            // Estado de la estrella (0 = no generada, 1 = esperando ser recogida, 2 = efecto activo)
int powerLevel = 0;            // Nivel de poder del jugador
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int grand_total_score;  //almacena puntaje total de todos los niveles pasados                                                   //
                                                                                                                                //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define SCORE_SCREEN 51

#define MAX_LEVELS 32 




#define MAX_PROJECTILES 10 // Número máximo de proyectiles simultáneos







//PUNTAJES TOTALES POR NIVEL
int level_scores[MAX_LEVELS] = {0};
int enemies_killed = 0;

//DEFINIR LOS PUNATJES ACUMULADOS POR CADA TIPO DE TANQUE EN CADA NIVEL
int tank_scores[MAX_LEVELS][6]= {0}; //pntaje por tanques
/// DEFINIR CONTADORES DE MUERTES POR TIPO DE TANQUE EN CADA NIVEL
int tank_1_kill_count[MAX_LEVELS] = {0};
int tank_2_kill_count[MAX_LEVELS] = {0};
int tank_3_kill_count[MAX_LEVELS] = {0};
int tank_4_kill_count[MAX_LEVELS] = {0};
int tank_5_kill_count[MAX_LEVELS] = {0};
int tank_6_kill_count[MAX_LEVELS] = {0};

///////////////////////////////////////////////
// Puntaje total acumulado por cada tipo de tanque en todos los niveles
int total_score_tank1 = 0;
int total_score_tank2 = 0;
int total_score_tank3 = 0;
int total_score_tank4 = 0;
int total_score_tank5 = 0;
int total_score_tank6 = 0;

///////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////





SDL_Surface *brick_texture = NULL; // IMAGEN PARA LADRILLOF
SDL_Surface *Water_texture = NULL; // IMAGEN PARA AGUA
SDL_Surface *Grass_texture = NULL; // IMAGEN PARA PASTO
SDL_Surface *Hierro_texture = NULL;  // IMAGEN PARA HIERRO
SDL_Surface *special_block_image = NULL; // Imagen del bloque especial
SDL_Surface *tank_texture = NULL; // Imagen del tanque

SDL_Surface *Nivel_2 = NULL; //imagen de nivel 2
SDL_Surface *Nivel_3 = NULL; //imagen de nivel 3
SDL_Surface *Nivel_4 = NULL; //imagen de nivel 4
SDL_Surface *Nivel_5 = NULL; //imagen de nivel 5
SDL_Surface *Graciasporjugar = NULL; //imagen de nivel 6
SDL_Surface *bomb_texture = NULL; // imagen bomba 
SDL_Surface *helmet_texture = NULL; // imagen casco
SDL_Surface *tanquePoder_texture = NULL; // imagen tanque de poder
SDL_Surface *temporizadorPoder_texture = NULL; //imagen temporizador poder 

SDL_Surface *pala_texture = NULL; // imagen pala 
SDL_Surface *star_texture = NULL; // imagen estrella


SDL_Surface *vidas_texture = NULL; // imagen vidas
SDL_Surface *tanques_texture = NULL; // imagen tanques

//se cargan varias imagenes para dar la sensacion de que se rompe el bloque 

SDL_Surface *brick_texture_X_plus = NULL;
SDL_Surface *brick_texture_X_minus = NULL;
SDL_Surface *brick_texture_Y_plus = NULL;
SDL_Surface *brick_texture_Y_minus = NULL;



//animaciones
SDL_Surface *spawn0_animation = NULL; // Animación de spawn de enemigos
SDL_Surface *spawn1_animation = NULL; // Animación de spawn de enemigos
SDL_Surface *spawn2_animation = NULL; // Animación de spawn de enemigos
SDL_Surface *spawn3_animation = NULL; // Animación de spawn de enemigos




// function prototypes
// initialise SDL
int init_SDL(int w, int h, int argc, char *args[]);

// load texture
SDL_Texture* load_texture(SDL_Renderer* renderer, const char* filename);

//////////////////////////////////////
//////////////////////////////////////
  // 1850 extremo del derecho del
  // 0 extremo izquierdo del mapa
  // 925 la mitad de la pantalla
  // int y_position = 670; extemo abajo de la pantallaS
  // int y_position = 0; extemo arriba de la pantalla
  // int y_position = 350; mitad de la pantalla


//////////////////////////////////////

//matrices
#define RIGHT_BORDER_WIDTH 3  // Ancho del borde DERECHO


#define MAX_TANK_BLOCKS 20

typedef struct {
    int x;
    int y;
    int active;
} TankBlock;

TankBlock tank_blocks[MAX_TANK_BLOCKS] = {
    {1800, 50, 1},
    {1850, 50, 1},
    {1800, 100, 1},
    {1850, 100, 1},
    {1800, 150, 1},
    {1850, 150, 1},
    {1800, 200, 1},
    {1850, 200, 1},
    {1800, 250, 1},
    {1850, 250, 1},
    {1800, 300, 1},
    {1850, 300, 1},
    {1800, 350, 1},
    {1850, 350, 1},
    {1800, 400, 1},
    {1850, 400, 1},
    {1800, 450, 1},
    {1850, 450, 1},
    {1800, 500, 1},
    {1850, 500, 1}


    //x,y,active
};





int map[MAP_HEIGHT][MAP_WIDTH] = {

    // Borde superior
    {BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED},
  
    // Filas intermedias con un borde izquierdo más ancho
  
  
    {BLOCK_RED,-1,  -1,  -1, -1,  4,  3, -1, -1, -1, -1,  4,  3, -1, -1,  4, 4, -1,  4,  4, -1, -1,  3,  4, -1, -1, -1, -1,  3,  4, -1, -1, -1,      -1, BLOCK_RED,BLOCK_RED,BLOCK_RED},
    {BLOCK_RED, 1,   3,  -1, -1,  3,  4, -1, -1, -1  -1, -1,  4,  3, -1, -1, 4, 4,  -1,  3, 3, -1,  -1,  3,  4, -1, -1, -1, -1,  4,  3,  -1,   -1,  3, 1, BLOCK_RED,BLOCK_RED,BLOCK_RED},
    {BLOCK_RED, 3,   1,  -1, -1, -1, -1, -1, -1, -1, -1,  4,  3, -1, -1,  3, 3, -1,  3,  3, -1, -1,  3,   4,  -1, -1, -1, -1, -1, -1, -1, -1,  1,  3,    BLOCK_RED,BLOCK_RED,BLOCK_RED},
    {BLOCK_RED,-1,  -1,  -1, -1, -1, -1, -1, -1, -1, -1,  4,  3, -1, -1,  3, 3, -1,  3,  3, -1, -1,  3,  4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,      BLOCK_RED,BLOCK_RED,BLOCK_RED},
    {BLOCK_RED,-1,  -1,  -1, -1, -1, -1, -1, -1, -1, -1,  4,  3, -1, -1, -1,-1, -1, -1, -1, -1, -1,  3,  4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,      BLOCK_RED,BLOCK_RED,BLOCK_RED},
    {BLOCK_RED, 4,  -1,  -1, -1, -1, -1, -1, -1, -1, -1, -1  -1, -1, -1, -1,-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  -1, 4,  BLOCK_RED,BLOCK_RED,BLOCK_RED},
    {BLOCK_RED, 4,  -1,  -1,  3,  4,  4,  3, -1, -1,  3,  3,  3, -1, -1,  3, 3, -1,  3,  3, -1, -1,  3,  3,  3, -1, -1,  3,  4,  3,  4,  3, -1,  4,      BLOCK_RED,BLOCK_RED,BLOCK_RED},
    {BLOCK_RED, 4,  -1,  -1,  3,  4,  4,  3, -1, -1,  3,  3,  3, -1, -1, -1,-1, -1, -1, -1, -1, -1,  3,  3,  3, -1, -1,  3,  4,  3,  4,  3, -1,  4,      BLOCK_RED,BLOCK_RED,BLOCK_RED},
    {BLOCK_RED, 4,  -1,  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  3, 3, -1,  3,  3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  4,      BLOCK_RED,BLOCK_RED,BLOCK_RED},
    {BLOCK_RED, 4,  -1,  -1, -1,  3,  4, -1,  3,  3, -1,  3,  3,  4, -1,  3, 3,  4,  3,  3, -1,  3,  3, -1,  3,  3, -1, -1, -1,  4,  4, -1, -1,  4,      BLOCK_RED,BLOCK_RED,BLOCK_RED},
    {BLOCK_RED, 4,  -1,  -1, -1,  3,  4, -1,  3,  3,  4,  3,  3,  4, -1,  3, 3, -1,  3,  3, -1,  3,  3, -1,  3,  3, -1, -1, -1,  4,  4, -1, -1,  4,      BLOCK_RED,BLOCK_RED,BLOCK_RED},
    {BLOCK_RED,-1,  -1,  -1, -1,  3,  4, -1,  3,  3,  4,  3,  3,  4, -1,  3, 3, -1,  3,  3, -1,  3,  3,  4,  3,  3, -1, -1, -1,  4,  4, -1, -1, -1,      BLOCK_RED,BLOCK_RED,BLOCK_RED},
    {BLOCK_RED,-1,  -1,  -1, -1,  4,  4, -1,  3,  3, -1,  3,  3,  4, -1, -1,-1, -1, -1, -1, -1,  3,  3, -1,  3,  3, -1, -1, -1,  4,  4, -1, -1, -1,      BLOCK_RED,BLOCK_RED,BLOCK_RED},
    {BLOCK_RED, 3,   1,  -1, -1,  4,  4, -1, -1, -1, -1, -1, -1,  1, -1, -1,-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  3,  3, -1,  1,  3,      BLOCK_RED,BLOCK_RED,BLOCK_RED},
    {BLOCK_RED, 1,   3,  -1, -1,  4,  4, -1, -1,  3,  3,  3,  3, -1, -1, -1, 3,  3,  3, -1, -1,  3,  3,  3,  3, -1, -1, -1, -1,  3,  3, -1,  3,  1,      BLOCK_RED,BLOCK_RED,BLOCK_RED},
    {BLOCK_RED,-1,  -1,  -1, -1,  4,  4, -1, -1,  3,  3,  3,  3, -1, -1, -1, 3,  SPECIAL_BLOCK,  3, -1, -1,  3,  3,  3,  3, -1, -1, -1, -1,  1,  1, -1, -1, -1, BLOCK_RED,BLOCK_RED,BLOCK_RED},
  
  
  
  
    //Borde inferior
    {BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED}
  };

  
  int map2 [MAP_HEIGHT ][MAP_WIDTH] = {
  // Borde superior
  {BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED},
  
  // Filas intermedias con un borde izquierdo más ancho
  // Filas intermedias con un borde izquierdo más ancho
  {BLOCK_RED,-1,  -1,  -1, -1,  4,  -1, -1, -1, -1, -1,  4,  -1, -1, -1,  4, 4, -1,  4,  4, -1, -1,  3,  4, -1, -1, -1, -1,  3,  4, -1, -1, -1,      -1, BLOCK_RED,BLOCK_RED,BLOCK_RED},
  
  {BLOCK_RED,-1,  -1,  -1, -1,  4,  -1, -1, -1, -1, -1,  4,  -1, -1, -1,  4, 4, -1,  4,  4, -1, -1,  3,  4, -1, -1, -1, -1,  3,  4, -1, -1, -1,      -1, BLOCK_RED,BLOCK_RED,BLOCK_RED},
  
  {BLOCK_RED,-1,  -1,  -1, -1,  4,  -1, -1, -1, -1, -1,  4,  -1, -1, -1,  4, 4, -1,  4,  4, -1, -1,  3,  4, -1, -1, -1, -1,  3,  4, -1, -1, -1,      -1, BLOCK_RED,BLOCK_RED,BLOCK_RED},
  
  {BLOCK_RED,-1,  -1,  -1, -1,  4,  -1, -1, -1, -1, -1,  4,  -1, -1, -1,  4, 4, -1,  4,  4, -1, -1,  3,  4, -1, -1, -1, -1,  3,  4, -1, -1, -1,      -1, BLOCK_RED,BLOCK_RED,BLOCK_RED},
  
  {BLOCK_RED,-1,-1,-1,-1,-1,-1, -1,-1,-1, 3,-1,-1,-1,-1,-1,-1,-1, 4, 4,-1,-1,-1, 3,-1,-1, 4, 4, 4, 4,-1, 3, 3, 3,BLOCK_RED,BLOCK_RED,BLOCK_RED},
  
  {BLOCK_RED, 1, 1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 3, 3, 3, 3, 3,-1,-1,-1,-1,-1,-1,-1,-1, 3, 3,-1, 1, 1, 1,BLOCK_RED,BLOCK_RED,BLOCK_RED},
  
  {BLOCK_RED, 3, 3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 3, 3,-1,-1,-1,-1,BLOCK_RED,BLOCK_RED,BLOCK_RED},
  
  {BLOCK_RED, 3, 3,-1, 4, 4, 4, 4,-1,-1,-1,-1,-1,-1,-1, 3, 3, 3, 3, 3,-1,-1,-1,-1,-1,-1,-1,-1, 3, 3,-1,-1,-1,-1,BLOCK_RED,BLOCK_RED,BLOCK_RED},
  
  {BLOCK_RED, 3, 3,-1, 3, 3,-1,-1, 3, 3, 4,-1,-1,-1,-1, 4, 4, 4, 4, 4,-1,-1, 4, 3, 3, 1, 4, 4, 4, 4,-1,-1,-1,-1,BLOCK_RED,BLOCK_RED,BLOCK_RED},
  
  {BLOCK_RED,-1,-1,-1, 3, 3,-1,-1, 3, 3, 4,-1,-1,-1,-1,-1,-1, 1,-1,-1,-1,-1, 4, 3, 3, 1,-1,-1,-1,-1,-1, 3, 3, 3,BLOCK_RED,BLOCK_RED,BLOCK_RED},
  
  {BLOCK_RED, 3, 3,-1, 3, 3,-1,-1, 3, 3, 4,-1,-1,-1,-1,-1,-1, 1,-1,-1,-1,-1, 4, 3, 3, 1,-1,-1,-1,-1,-1, 3, 3, 3,BLOCK_RED,BLOCK_RED,BLOCK_RED},
  
  {BLOCK_RED, 3, 3,-1, 4, 4, 4, 4, 3, 3, 4,-1,-1,-1,-1, 4, 4, 4, 4, 4,-1,-1, 4, 3, 3, 1,-1,-1,-1,-1,-1,-1,-1,-1,BLOCK_RED,BLOCK_RED,BLOCK_RED},
  
  {BLOCK_RED,-1,-1,-1, 3, 3,-1,-1, 3, 3, 4,-1,-1,-1,-1, 3, 3, 3, 3, 3,-1,-1, 4, 3, 3, 1,-1, 1, 3,-1,-1,-1, 3, 4,BLOCK_RED,BLOCK_RED,BLOCK_RED},
  
  {BLOCK_RED,-1,-1,-1, 3, 3,-1,-1,-1,-1,-1,-1,3,3,3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 1, 3,-1,-1,-1, 3, 4,BLOCK_RED,BLOCK_RED,BLOCK_RED},
  
  {BLOCK_RED, 3, 3,-1, 3, 3,-1,-1,-1, 3, 3, 3,-1,-1,-1,-1, 3, 3, 3,-1,-1,-1, 3, 3, 3,-1,-1, 1, 3,-1, 3,-1, 3, 4,BLOCK_RED,BLOCK_RED,BLOCK_RED},
  
  {BLOCK_RED, 3, 3,-1, 4, 4, 4, 4,-1, 4, 4, 4,-1,-1,-1,-1, 3, SPECIAL_BLOCK, 3,-1,-1,-1, 4, 4, 4,-1,-1, 1, 3,-1, 3,-1, 3, 4,BLOCK_RED,BLOCK_RED,BLOCK_RED},
  
  {BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED}
  // Borde inferior
  };
  
  
  int map3 [MAP_HEIGHT ][MAP_WIDTH] = {
  // Borde superior
  {BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED},
  
  {BLOCK_RED,-1,  -1,  -1, -1,  4,  -1, -1, -1, -1, -1,  4,  -1, -1, -1,  -1, -1, -1,  -1,  -1, -1, -1,  3,  4, -1, -1, -1, -1,  3,  4, -1, -1, -1,      -1, BLOCK_RED,BLOCK_RED,BLOCK_RED},
  {BLOCK_RED,-1,  -1,  -1, -1,  4,  -1, -1, -1, -1, -1,  4,  -1, -1, -1,  4, 4, -1,  4,  4, -1, -1,  3,  4, -1, -1, -1, -1,  3,  4, -1, -1, -1,      -1, BLOCK_RED,BLOCK_RED,BLOCK_RED},
  {BLOCK_RED,-1,  -1,  -1, -1,  4,  -1, -1, -1, -1, -1,  4,  -1, -1, -1,  4, 4, -1,  4,  4, -1, -1,  3,  4, -1, -1, -1, -1,  3,  4, -1, -1, -1,      -1, BLOCK_RED,BLOCK_RED,BLOCK_RED},
  {BLOCK_RED, 2,-1,-1, 3, 3, 3, 3, 3, 3,-1, 3, 4, 4, 4, 4,-1, 3,-1, 4, 4, 4, 4,-1, 3, 3, 3, 3, 3, 3,-1,-1,-1, 2,BLOCK_RED,BLOCK_RED,BLOCK_RED},
  {BLOCK_RED, 1,-1,-1,-1, 3, 3, 3, 3,-1,-1, 3, 4,-1,-1,-1,-1, 3,-1, 4,-1,-1,-1,-1,-1, 3, 3, 3, 3,-1,-1,-1,-1, 1,BLOCK_RED,BLOCK_RED,BLOCK_RED},
  {BLOCK_RED, 1,-1,-1,-1,-1, 3, 3,-1,-1,-1, 3, 4,-1,-1,-1,-1, 3,-1, 4,-1,-1,-1,-1,-1,-1, 3, 3,-1,-1,-1,-1,-1, 1,BLOCK_RED,BLOCK_RED,BLOCK_RED},
  {BLOCK_RED, 1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 3, 4, 4, 4, 4,-1, 3,-1, 4, 4, 4,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 1,BLOCK_RED,BLOCK_RED,BLOCK_RED},
  {BLOCK_RED, 4,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 4, 1, 1, 1, 4,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 4,BLOCK_RED,BLOCK_RED,BLOCK_RED},
  
  {BLOCK_RED, 4, 4,-1,-1, 4,-1, 4,-1, 4,-1, 4,-1,-1,-1, 4, 1, 3, 1, 4,-1, 4,-1, 4,-1, 4,-1, 4,-1, 4,-1,-1, 4, 4,BLOCK_RED, BLOCK_RED, BLOCK_RED},
  
  {BLOCK_RED, 4, 4, 4,-1,-1, 3, 4,-1,-1,-1,-1, 4, 4, 4, 4,-1, 3,-1, 4,-1,-1,-1,-1,-1,-1,-1, 4, 3,-1,-1, 4, 4, 4,BLOCK_RED,BLOCK_RED,BLOCK_RED},
  {BLOCK_RED, 4, 4,-1,-1,-1, 3, 4, 1,-1, 2, 1,-1,-1,-1,-1,-1, 3,-1,-1,-1,-1,-1, 1, 2,-1, 1, 4, 3,-1,-1,-1, 4, 4,BLOCK_RED,BLOCK_RED,BLOCK_RED},
  {BLOCK_RED, 4,-1,-1,-1,-1, 3, 4, 1,-1, 2, 1,-1, 3, 3, 3,-1, 3,-1, 3, 3, 3,-1, 1, 2,-1, 1, 4, 3,-1,-1,-1,-1, 4,BLOCK_RED,BLOCK_RED,BLOCK_RED},
  {BLOCK_RED,-1,-1,-1,-1,-1, 3, 4,-1,-1,-1,-1, 1, 3, 4,-1,-1, 3,-1,-1, 4, 3, 1,-1,-1,-1,-1, 4, 3,-1,-1,-1,-1,-1,BLOCK_RED,BLOCK_RED,BLOCK_RED},
  
  {BLOCK_RED, 3,-1, 3,-1, 3,-1, 3,-1, 3,-1, 3, 1, 3, 4,-1,-1,-1,-1,-1, 4, 3, 1, 3,-1, 3,-1, 3,-1, 3,-1, 3, -1, 3, BLOCK_RED, BLOCK_RED, BLOCK_RED},
  
  {BLOCK_RED, 3, 3, 3, 3, 3,-1,-1, 2,-1,-1,-1, 1, 3, 4,-1, 3, 3, 3,-1, 4, 3, 1,-1,-1,-1, 2,-1,-1, 3, 3, 3, 3, 3,BLOCK_RED,BLOCK_RED,BLOCK_RED},
  {BLOCK_RED,-1, 4, 4, 4,-1,-1, 2, 2, 2,-1,-1, 1, 3,-1,-1, 3, SPECIAL_BLOCK, 3,-1, 4, 3, 1,-1,-1, 2, 2, 2,-1,-1, 4, 4, 4,-1,BLOCK_RED,BLOCK_RED,BLOCK_RED},
  
  {BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED}
  
  };
  
  int map4 [MAP_HEIGHT ][MAP_WIDTH] = {
  // Borde superior
  {BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED},
  {BLOCK_RED,-1,-1,-1,-1,-1,-1, 3,-1,-1, 3,-1,-1,-1,-1,-1,-1,-1, 4, 4,-1,-1,-1, 3,-1,-1, 4, 4, 4, 4,-1, -1, -1, -1,BLOCK_RED,BLOCK_RED,BLOCK_RED},
  {BLOCK_RED,-1,-1,-1,-1,-1,-1, 3,-1,-1, 3,-1,-1,-1,-1,-1,-1,-1, 4, 4,-1,-1,-1, 3,-1,-1, 4, 4, 4, 4,-1, -1, -1, -1,BLOCK_RED,BLOCK_RED,BLOCK_RED},
  {BLOCK_RED, 4, -1, -1,-1,-1, -1, 1,-1,-1, 2,-1,-1, 2, 2, 2, 2, 2, 2, 2, 2, 2,-1,-1, 2,-1,-1, 1, 2,-1,-1, -1, -1, -1,BLOCK_RED,BLOCK_RED,BLOCK_RED},
  {BLOCK_RED, 4,-1,-1,-1,-1, -1, 2,-1,-1, 2,-1,-1,-1, 2, 2, 2, 2, 2, 2, 2,-1,-1,-1, 2,-1,-1, 2, 2,-1,-1,-1,-1, 4,BLOCK_RED,BLOCK_RED,BLOCK_RED},
  {BLOCK_RED,-1,-1,-1, 4,-1,-1,-1,-1, 2, 2, 2,-1,-1,-1, 3, 3, 3, 3, 3,-1,-1,-1, 2, 2, 2,-1,-1,-1,-1,-1,-1,-1,-1,BLOCK_RED,BLOCK_RED,BLOCK_RED},
  {BLOCK_RED,-1,-1, 1, 1, 1,-1,-1,-1,-1,-1,-1, 3,-1,-1,-1, 4, 4, 4,-1,-1,-1,-1, 3,-1,-1,-1,-1,-1,-1, 1, 1,-1,-1,BLOCK_RED,BLOCK_RED,BLOCK_RED},
  {BLOCK_RED,-1, 4, 4, 4, 4, 4,-1,-1,-1,-1, 4, 4, 4,-1,-1,-1, 3,-1,-1,-1,-1, 4, 4, 4-1,-1,-1,-1,-1, 4, 4, 4, 4,-1,BLOCK_RED,BLOCK_RED,BLOCK_RED},
  {BLOCK_RED, 3, 3, 3, 3, 3, 3, 3,-1,-1, 3, 3, 3, 3, 3,-1,-1, 1,-1,-1,-1, 3, 3, 3, 3, 3,-1,-1, 3, 3, 3, 3, 3, 3,BLOCK_RED,BLOCK_RED,BLOCK_RED},
  {BLOCK_RED,-1, 4, 4, 4, 4, 4,-1,-1,-1,-1, 4, 4, 4,-1,-1,-1, 3,-1,-1,-1,-1, 4, 4, 4,-1,-1,-1,-1, 4, 4, 4, 4,-1,BLOCK_RED,BLOCK_RED,BLOCK_RED},
  {BLOCK_RED,-1,-1, 1, 1, 1,-1,-1,-1,-1,-1,-1, 3,-1,-1,-1, 4, 4, 4,-1,-1,-1,-1, 3,-1,-1,-1,-1,-1,-1, 1, 1,-1,-1,BLOCK_RED,BLOCK_RED,BLOCK_RED},
  {BLOCK_RED,-1,-1,-1, 4,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 3, 3, 3, 3, 3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,BLOCK_RED,BLOCK_RED,BLOCK_RED},
  {BLOCK_RED,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 4, 4, 4, 4, 4, 4, 4,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,BLOCK_RED,BLOCK_RED,BLOCK_RED},
  {BLOCK_RED, 4,-1,-1,-1, 4, 4, 4, 4, 4,-1,-1,-1, 4, 3, 3, 3, 4, 3, 3, 3, 4,-1,-1,-1, 4, 4, 4, 4, 4,-1,-1,-1, 4,BLOCK_RED,BLOCK_RED,BLOCK_RED},
  {BLOCK_RED, 4, 3, 3,-1, 3, 3, 3, 3, 3,-1, 4,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 4,-1, 3, 3, 3, 3, 3,-1, 3, 3, 4,BLOCK_RED,BLOCK_RED,BLOCK_RED},
  {BLOCK_RED, 4, 3, 3,-1, 1, 1, 1, 1, 1, 3, 3, 3,-1,-1,-1, 3, 3, 3,-1,-1,-1, 3, 3, 3, 1, 1, 1, 1, 1,-1, 3, 3, 4,BLOCK_RED,BLOCK_RED,BLOCK_RED},
  {BLOCK_RED, 4, 3, 3,-1, 1, 1, 1, 1, 1, 3, 3, 3,-1,-1,-1, 3, SPECIAL_BLOCK, 3,-1,-1,-1, 3, 3, 3, 1, 1, 1, 1, 1,-1, 3, 3, 4,BLOCK_RED,BLOCK_RED,BLOCK_RED},
  {BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED}
  };
  
  int map5 [MAP_HEIGHT ][MAP_WIDTH] = {
    // Borde superior
    {BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED},
    {BLOCK_RED,1,-1,-1,-1,-1,-1, 3,-1,-1, 3,-1,-1,-1,-1,-1,-1,-1, 4, 4,-1,-1,-1, 3,-1,-1, 4, 4, 4, 4,-1, -1, -1, -1,BLOCK_RED,BLOCK_RED,BLOCK_RED},
    {BLOCK_RED,-1,-1,-1,-1,-1,-1, 3,-1,-1, 3,-1,-1,-1,-1,-1,-1,-1, 4, 4,-1,-1,-1, 3,-1,-1, 4, 4, 4, 4,-1, 3, -1, -1,BLOCK_RED,BLOCK_RED,BLOCK_RED},
    {BLOCK_RED,-1,-1,-1,-1,-1,-1, 3,-1,-1, 3,-1,-1,-1,-1,-1,-1,-1, 4, 4,-1,-1,-1, 3,-1,-1, 4, 4, 4, 4,-1, -1, 4, -1,BLOCK_RED,BLOCK_RED,BLOCK_RED},
    {BLOCK_RED,-1,-1,-1,-1,-1, 2, 3, 3, 3, 3,-1, 3,-1, 4, 3, 3, 3, 3, 3, 4,-1, 3,-1, 1, 2, 2, 2, 2,-1,-1,-1,-1,-1,BLOCK_RED,BLOCK_RED,BLOCK_RED},
    {BLOCK_RED,-1,-1,-1,-1,-1, 2, 3,-1,-1,-1,-1, 3,-1, 4, 4, 4, 4, 4, 4, 4,-1, 3,-1, 1, 2,-1,-1,-1,-1,-1,-1,-1,-1,BLOCK_RED,BLOCK_RED,BLOCK_RED},
    {BLOCK_RED,-1,-1,-1,-1,-1, 2, 3, 3, 3, 3,-1, 3,-1, 4, 3, 3, 3, 3, 3, 4,-1, 3,-1, 1, 2, 2, 2, 2,-1,-1,-1,-1,-1,BLOCK_RED,BLOCK_RED,BLOCK_RED},
    {BLOCK_RED,-1, 3,-1, 3,-1, 2, 3,-1,-1,-1,-1, 3,-1, 4,-1, 2, 2, 2,-1, 4,-1, 3,-1, 1, 2,-1,-1,-1,-1, 3,-1, 3,-1,BLOCK_RED,BLOCK_RED,BLOCK_RED},
    {BLOCK_RED,-1, 3,-1, 3,-1, 2, 3, 3, 3, 3,-1, 3,-1,-1,-1,-1, 4,-1,-1,-1,-1, 3,-1, 1, 2, 2, 2, 2,-1, 3,-1, 3,-1,BLOCK_RED,BLOCK_RED,BLOCK_RED},
    {BLOCK_RED, 4, 4, 4, 4,-1, 2, 2, 2, 2, 2,-1, 3,-1,-1,-1,-1,-1,-1,-1,-1,-1, 3,-1, 1, 1, 1, 1, 1,-1, 4, 4, 4, 4,BLOCK_RED,BLOCK_RED,BLOCK_RED},
    {BLOCK_RED,-1,-1,-1,-1,-1, 1, 1, 1, 1, 1,-1,-1,-1,-1,-1,-1, 4,-1,-1,-1,-1,-1,-1,-1,-1, 3,-1,-1,-1,-1,-1,-1,-1,BLOCK_RED,BLOCK_RED,BLOCK_RED},
    {BLOCK_RED,-1, 4, 4,-1,-1,-1,-1, 3,-1,-1,-1,-1,-1,-1,-1, 2, 2, 2,-1,-1, 3, 4, 3,-1, 3, 3, 3,-1, 4, 4,-1,-1,-1,BLOCK_RED,BLOCK_RED,BLOCK_RED},
    {BLOCK_RED, 4,-1,-1,-1,-1,-1, 3, 3, 3,-1, 3, 4, 3,-1, 3, 3, 3, 3, 3,-1,-1,-1,-1,-1,-1, 3,-1,-1,-1,-1,-1,-1, 4,BLOCK_RED,BLOCK_RED,BLOCK_RED},
    {BLOCK_RED, 3, 4,-1,-1,-1, 4,-1, 3,-1,-1,-1,-1,-1, 4, 4, 4, 4, 4, 4, 4,-1,-1,-1,-1,-1,-1,-1, 4,-1,-1,-1, 4, 3,BLOCK_RED,BLOCK_RED,BLOCK_RED},
    {BLOCK_RED, 3, 3, 3,-1, 4, 3, 4,-1,-1, 3, 3, 4,-1, 4,-1,-1,-1,-1,-1, 4,-1, 4, 3, 3,-1,-1, 4, 3, 4,-1, 3, 3, 3,BLOCK_RED,BLOCK_RED,BLOCK_RED},
    {BLOCK_RED, 3, 4, 1, 4, 3, 4, 3, 4,-1, 3, 3, 4,-1, 4,-1, 3, 3, 3,-1, 4,-1, 4, 3, 3,-1, 4, 3, 4, 3, 4, 1, 4, 3,BLOCK_RED,BLOCK_RED,BLOCK_RED},
    {BLOCK_RED, 4, 1, 1, 1, 3, 4, 3,-1,-1, 3, 3, 4,-1,-1,-1, 3, SPECIAL_BLOCK, 3,-1,-1,-1, 4, 3, 3,-1,-1, 3, 4, 3, 1, 1, 1, 4,BLOCK_RED,BLOCK_RED,BLOCK_RED},
    {BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED, BLOCK_RED}
    };

//definmos un puntero para el mapa actual
int current_map[MAP_HEIGHT][MAP_WIDTH];
int current_level = 1;
//int original_map[MAP_HEIGHT][MAP_WIDTH];


int num_tanques = 10; // Número inicial de tanques



typedef struct block_t {
  int x;
  int y;
  int block_type;
  int h;
  int w;
  int hit_count;
  int last_hit_direction;
} block_t;

// estructura para el proyectil
typedef struct projectile_t {
  int x;
  int y;
  int h;
  int w;
  int speedX;
  int speedY;
  int active; // 0 no bullet 1
  uint32_t StartTime;
} projectile_t;




typedef struct {
  int x, y, w, h;
  int active;          // 0 inactivo, 1 activo
} enemy_t;

typedef struct bullet_t {
  int x;
  int y;
  int w;
  int h;
  int speed;
  int active; // 0 no bullet, 1 active bullet
} bullet_t;


// Proyectil del enemy_t
typedef struct enemy_projectile_t {
  int x;
  int y;
  int h;
  int w;
  int speedX;
  int speedY;
  int active; // 0 no bullet, 1 active bullet
} enemy_projectile_t;

#define MAX_BULLETS 10
bullet_t bullets[MAX_BULLETS];

//  Definición de los estados del enemigo
typedef enum { ENEMY_MOVING, ENEMY_WAITING } EnemyState;


typedef struct spawn_animation_t {
    int x;  // Posición de la animación
    int y; // Posición de la animación
    int active; // 0 inactivo, 1 activo
    Uint32 StartTime;
  } spawn_animation_t;
  
  
  
// nuevo: Extender la estructura del bloque en movimiento para el enemigo
typedef struct moving_block_t {
    int x;
    int y;
    int w;
    int h;
    int speedX;
    int speedY;
    EnemyState state;
    Uint32 waitStart;
    int block_type;
    int lastDirectionX;
    int lastDirectionY;
    int active;
    SDL_Texture *texture;
    Uint32 lastShotTime;
    enemy_projectile_t projectile;
    int hitCount;
    int type;
    int spawning;
    Uint32 spawnStartTime;
    int exploding;
    spawn_animation_t spawn_animation; // Agregar este campo
} moving_block_t;





typedef  struct game_elemen_t {
  int x;
  int y;
  int h;
  int w;
  int life;
} game_elemen_t;

typedef struct spawn_point_t {
  int x;
  int y;
} spawn_point_t;


//definimos una estructura para el sewguimiento de la animacion de spawn


block_t map_blocks[] = {

    // limites del mapa se usa una barra de bloques rojos
    {-50, 0, 0, BLOCK_SIZE * 15, BLOCK_SIZE}, // bloque rojo
    {0, -50, 0, BLOCK_SIZE, BLOCK_SIZE * 40},
    {0, 900, 0, BLOCK_SIZE, BLOCK_SIZE * 40},
    {1900, 0, 0, BLOCK_SIZE * 15, BLOCK_SIZE},

};


int num_blocks = sizeof(map_blocks) / sizeof(map_blocks[0]);
// cada int ocupa 4bites para el sizeof se divide por 4 para saber cuantos
// elementos hay en el array

void draw_block_like_type_surface(SDL_Surface *surface, int x, int y,
                                  int block_type, int block_width,
                                  int block_height, block_t *blocks, int num_blocks) {
  // Elegir color según el tipo
  if (block_type == SPECIAL_BLOCK && special_block_image != NULL) {
    SDL_Rect dest = {x, y, block_width, block_height};
    SDL_BlitScaled(special_block_image, NULL, surface, &dest);
    return;
  }
  if (block_type == BOMB_BLOCK && bomb_texture != NULL) {
    SDL_Rect dest = {x, y, block_width, block_height};
    SDL_BlitScaled(bomb_texture, NULL, surface, &dest);
    return;
  }

  if (block_type == HELMET_BLOCK && helmet_texture != NULL) {
    SDL_Rect dest = {x, y, block_width, block_height};
    SDL_BlitScaled(helmet_texture, NULL, surface, &dest);
    return;
   }

   if (block_type == TANQUE_PODER_BLOCK && tanquePoder_texture != NULL) {
    SDL_Rect dest = {x, y, block_width, block_height};
    SDL_BlitScaled(tanquePoder_texture, NULL, surface, &dest);
    return;
   }

   if (block_type == TEMPORIZADOR_PODER_BLOCK && temporizadorPoder_texture != NULL) {
    SDL_Rect dest = {x, y, block_width, block_height};
    SDL_BlitScaled(temporizadorPoder_texture, NULL, surface, &dest);
    return;
   }
   
    if (block_type == PALA_BLOCK && pala_texture != NULL) {
    SDL_Rect dest = {x, y, block_width, block_height};
    SDL_BlitScaled(pala_texture, NULL, surface, &dest);
    return;
   }
   if (block_type == STAR_BLOCK && star_texture != NULL) {
    SDL_Rect dest = {x, y, block_width, block_height};
    SDL_BlitScaled(star_texture, NULL, surface, &dest);
    return;
   }
   

  if (block_type == BLOCK_YELLOW && brick_texture != NULL) {
    SDL_Rect dest = {x, y, block_width, block_height};
    SDL_BlitScaled(brick_texture, NULL, surface, &dest);
    return;
}
  if (block_type == BLOCK_GREEN && Grass_texture != NULL) {
    SDL_Rect dest = {x, y, block_width, block_height};
    SDL_BlitScaled(Grass_texture, NULL, surface, &dest);
    return;
  }
  if (block_type == BLOCK_BLUE && Water_texture != NULL) {
    SDL_Rect dest = {x, y, block_width, block_height};
    SDL_BlitScaled(Water_texture, NULL, surface, &dest);
    return;
  }
  if (block_type == BLOCK_WHITE && Hierro_texture != NULL) {
    SDL_Rect dest = {x, y, block_width, block_height};
    SDL_BlitScaled(Hierro_texture, NULL, surface, &dest);
    return;
  }
  if (block_type == BLOCK_ENEMY && tank_texture != NULL) {
    SDL_Rect dest = {x, y, block_width, block_height};
    SDL_BlitScaled(tank_texture, NULL, surface, &dest);
    return;
  }
  if (block_type == vidas_texture_BLOCK && vidas_texture != NULL) {
    SDL_Rect dest = {x, y, block_width, block_height};
    SDL_BlitScaled(vidas_texture, NULL, surface, &dest);
    return;
}
if (block_type == tanques_texture_BLOCK && tanques_texture != NULL) {
    SDL_Rect dest = {x, y, block_width, block_height};
    SDL_BlitScaled(tanques_texture, NULL, surface, &dest);
    return;
}

if (block_type == brick_texture_X_plus_block && brick_texture_X_plus != NULL) {
    SDL_Rect dest = {x, y, block_width, block_height};
    SDL_BlitScaled(brick_texture_X_plus, NULL, surface, &dest);
    return;

}   
if (block_type == brick_texture_X_minus_block && brick_texture_X_minus != NULL) {
    SDL_Rect dest = {x, y, block_width, block_height};
    SDL_BlitScaled(brick_texture_X_minus, NULL, surface, &dest);
    return;

}
if (block_type == brick_texture_Y_minus_block && brick_texture_Y_minus != NULL) {
    SDL_Rect dest = {x, y, block_width, block_height};
    SDL_BlitScaled(brick_texture_Y_minus, NULL, surface, &dest);
    return;

}
if (block_type == brick_texture_Y_plus_block && brick_texture_Y_plus != NULL) {
    SDL_Rect dest = {x, y, block_width, block_height};
    SDL_BlitScaled(brick_texture_Y_plus, NULL, surface, &dest);
    return;
}

if(block_type == SPAWN0_animation_block && spawn0_animation != NULL) {
    SDL_Rect dest = {x, y, block_width, block_height};
    SDL_BlitScaled(spawn0_animation, NULL, surface, &dest);
    return;
}
if(block_type == SPAWN1_animation_block && spawn1_animation != NULL) {
    SDL_Rect dest = {x, y, block_width, block_height};
    SDL_BlitScaled(spawn1_animation, NULL, surface, &dest);
    return;
}
if(block_type == SPAWN2_animation_block && spawn2_animation != NULL) {
    SDL_Rect dest = {x, y, block_width, block_height};
    SDL_BlitScaled(spawn2_animation, NULL, surface, &dest);
    return;
}
if(block_type == SPAWN3_animation_block && spawn3_animation != NULL) {
    SDL_Rect dest = {x, y, block_width, block_height};
    SDL_BlitScaled(spawn3_animation, NULL, surface, &dest);
    return;
}



  Uint32 color = 0xffffffff; // blanco por defecto
  switch (block_type) {
  case 0: // gris
    color = SDL_MapRGB(surface->format, 128, 128, 128);
    break;
  case 1: // verde
    color = SDL_MapRGB(surface->format, 0, 255, 0);
    break;
  case 2: // azul
    color = SDL_MapRGB(surface->format, 0, 0, 255);
    break;
  case 3: // amarillo
    color = SDL_MapRGB(surface->format, 255, 255, 0);
    break;
  case 4: // blanco
    color = SDL_MapRGB(surface->format, 255, 255, 255);
    break;
  case 5: // verde oscuro
    color = SDL_MapRGB(surface->format, 0, 128, 0);
    break;
  default:
    break;
  }

  // Crear rectángulo y rellenarlo
  SDL_Rect block = {x, y, block_width, block_height};
  SDL_FillRect(surface, &block,
               color); // Dibujar el bloque en la superficie dada
}

void draw_map_blocks(SDL_Surface *surface, block_t *blocks, int count) {
  for (int i = 0; i < count; i++) {
    draw_block_like_type_surface(surface, blocks[i].x, blocks[i].y,
                                 blocks[i].block_type, blocks[i].w,
                                 blocks[i].h, blocks, num_blocks);
    }
}

// Dibuja cuatro bloques en la superficie, uno de cada color
void draw_four_blocks_surface(SDL_Surface *surface) {
  int pos = 1000;

  // 1850 extremo del derecho del
  // 0 extremo izquierdo del mapa
  // 925 la mitad de la pantalla
  int x_positions[4] = {pos, pos, pos, pos};
  int y_position = 1000;
  // int y_position = 670; extemo abajo de la pantalla
  // int y_position = 0; extemo arriba de la pantalla
  // int y_position = 350; mitad de la pantalla

  for (int i = 0; i < 4; i++) {
    draw_block_like_type_surface(surface, x_positions[i], y_position, i,
                                 BLOCK_SIZE, BLOCK_SIZE, map_blocks, num_blocks);
  }
} //// despues ver esto no confio

/////////////////////////////////////
/////////////////////////////////////
/////////////////////////////////////

typedef struct player_t {

  int x;
  int y;
  int w;
  int h;

} player_t;

typedef struct game_element_t {
  int x;
  int y;
  int w;
  int h;
  int lives;
  SDL_Texture *texture; // Add texture member
  SDL_Texture *shieldTexture; // Textura del escudo

  double angle; // Add angle member

  int helmetActive; // Estado del casco (0 = no activo, 1 = activo)
    projectile_t projectile; // Proyectil del jugador



} game_element_t;

// This is one of the few cases where it makes sense to use magic numbers
// Avoid the use of global variables at maximum
int g_score[] = {0, 0};
// Avoid the use of global variables, modify the code to avoid its use.
int g_width, g_height; // used if fullscreen

SDL_Window *window = NULL; // The window we'll be rendering to
SDL_Renderer *renderer;    // The renderer SDL will use to draw to the screen

moving_block_t enemies[MAX_ENEMIES];
SDL_Texture* enemyTextures[6];
SDL_Texture* shieldTextures[2]; // Declare shieldTextures array
SDL_Texture* playerTextures[3];
spawn_point_t spawn_points[NUM_SPAW_POINTS] ={
  {100, 50},   // Punto 1
  {500, 50},   // Punto 2
  {300, 150},   // Punto 3
  {700, 50},    // Punto 4
  {1600,50},

  {700, 300}    // Punto 4


};


// surfaces
static SDL_Surface *screen;
static SDL_Surface *title;
static SDL_Surface *numbermap;
static SDL_Surface *end;

// textures
SDL_Texture *screen_texture;

// Always make a header for each one of the use created functions

/* Function: init_game
 * ---------------------------------
 * This function initialises the position of the player in the screen
 * (the block that can be moved with the WASD keys), and the block that
 * is part of the map, which is a test for collisions. Please note that
 * in this functions we are passing pointers, not values.
 *
 * Arguments:
 *	player:	Pointer to the player object
 *	map_element: Pointer to the map element object.
 *
 * Return:
 * 	void.
 */
static void init_game(game_element_t *player, game_element_t *map_element) {
  // Here the function is receiving the pointer to the player object
  // it modifies the player object directly
  player->x = PLAYER_START_X;
  player->y = PLAYER_START_Y;
  player->w = BLOCK_SIZE;
  player->h = BLOCK_SIZE;
  player->texture = playerTextures[0]; // Assign the texture to the player

  map_element->x = 1000;
  map_element->y = 1000;
  map_element->w = 2 * BLOCK_SIZE;
  map_element->h = 2 * BLOCK_SIZE;
}

/* Function: check_collision
 * --------------------------
 * This function verifies if theare is collision between two game
 * elements.
 *
 * Arguments:
 * 	a: game element to be checked
 *	b: game element to be checked
 *
 * Return:
 *	TRUE if there is collision
 * 	FALSE if there isn't collision
 */
int check_collision(game_element_t a, game_element_t b) {

  int left_a = a.x;
  int right_a = a.x + a.w;
  int top_a = a.y;
  int bottom_a = a.y + a.h;

  int left_b = b.x;
  int right_b = b.x + b.w;
  int top_b = b.y;
  int bottom_b = b.y + b.h;

  if (bottom_a <= top_b)
    return FALSE;

  if (top_a >= bottom_b)
    return FALSE;

  if (right_a <= left_b)
    return FALSE;

  if (left_a >= right_b)
    return FALSE;

  // If none of the conditions worked, return TRUE

  return TRUE;
}

/* Function: move_player
 * ---------------------
 * This function is in charge of relocating the player position
 * across the screen
 *
 * Arguments:
 *	d: direction on which the player is going to be moved.
 *
 * Return:
 *	void.
 */

////////////////////////////////////////////////////////////////////
int check_collision_with_special_blocks(game_element_t *player, block_t *blocks, int num_blocks) {
  for (int i = 0; i < num_blocks; i++) {
      int block_type = blocks[i].block_type;
      if (block_type == BLOCK_RED || block_type == BLOCK_BLUE || block_type == SPECIAL_BLOCK ||block_type == BLOCK_YELLOW || block_type == brick_texture_X_minus_block || block_type == brick_texture_X_plus_block || block_type == brick_texture_Y_minus_block || block_type == brick_texture_Y_plus_block ) {
          game_element_t block_element = {blocks[i].x, blocks[i].y, blocks[i].w, blocks[i].h};
          if (check_collision(*player, block_element)) {
              return TRUE; // Si colisiona con al menos uno, retorna TRUE
          }
      }
  }
  return FALSE; // Si no colisionó con ninguno, retorna FALSE
}


void BLOCK_HELMET(game_element_t *player, int map[MAP_HEIGHT][MAP_WIDTH], Uint32 *helmetSpawnTime, Uint32 *shieldStartTime, int *shieldActive, SDL_Texture* shieldTextures[]) {
    Uint32 currentTime = SDL_GetTicks(); //Obtiene  el tiempo actual en milisegundos desde uue se inicio el programa
  
    // Si el casco no está activo, aparece en una celda vacía cada 30s
    if (!helmetActive && (currentTime - *helmetSpawnTime >= 30000)) {
        int emptyCells[MAP_HEIGHT * MAP_WIDTH][2];
        int emptyCount = 0;
  
        // Buscar espacios vacíos en el mapa
        for (int y = 0; y < MAP_HEIGHT; y++) {
            for (int x = 0; x < MAP_WIDTH; x++) {
                // Verificar si la celda está vacía
                if (map[y][x] == -1) { // Espacio vacío
                    emptyCells[emptyCount][0] = x;
                    emptyCells[emptyCount][1] = y;
                    emptyCount++;
                }
            }
        }
  
        // Si hay espacios vacíos, elegir uno aleatorio
        if (emptyCount > 0) {
            int randomIndex = rand() % emptyCount;
            helmetX = emptyCells[randomIndex][0]; //Coordenada  X del casco
            helmetY = emptyCells[randomIndex][1]; // Coordenada Y del casco
            map[helmetY][helmetX] = HELMET_BLOCK; // Marca la celda ocupada por un casco
            *helmetSpawnTime = currentTime; // Actualiza el tiempi en que apareció el casco
            helmetActive = 1; //Marca el casco como activo
            printf("Casco apareció en (%d, %d)\n", helmetX * BLOCK_SIZE, helmetY * BLOCK_SIZE);
        }
    }
  
    // Si no se recoge en 10 segundos, desaparece
    if (helmetActive && (currentTime - *helmetSpawnTime >= 10000)) {
        if (helmetX != -1 && helmetY != -1 && map[helmetY][helmetX] == HELMET_BLOCK) {
            map[helmetY][helmetX] = -1;
            printf(" El casco desapareció\n");
            helmetActive = 0;
            helmetX = -1;
            helmetY = -1;
        }
    }
  
    // Si el jugador lo toca, activa el escudo
    if (helmetActive && helmetX != -1 && helmetY != -1) {
        game_element_t helmet_block = {helmetX * BLOCK_SIZE, helmetY * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE};
        if (check_collision(*player, helmet_block)) {
            printf(" ¡El jugador recogió el casco! Escudo activado por 10s.\n");
            *shieldStartTime = currentTime; // Guarda el momento de activación del escudo
            *shieldActive = 1; //activa el escdo
  
            // Eliminar el casco del mapa
            map[helmetY][helmetX] = -1;
            helmetActive = 0; // Desactiva el casco
            helmetX = -1; // reinicia coordenadas
            helmetY = -1;
        }
    }
  
    // Alternar texturas del escudo mientras está activo
    if (*shieldActive) {
        int frame = (currentTime / 100) % 2; // Cambiar cada 100 ms o sea alterna entre 0 y 1
        player->shieldTexture = shieldTextures[frame];
    }
  
    // El escudo desaparece después de 10s
    if (*shieldActive && (currentTime - *shieldStartTime >= 10000)) {
        printf(" El escudo ha expirado.\n");
        *shieldActive = 0; //Desactiva el escudo
        player->shieldTexture = NULL; // Eliminar la textura del escudo
    }
}


///////////////////////////////////////////////////////////////////////////
void move_player(int d, game_element_t *player, block_t *blocks, int num_blocks, int map[MAP_HEIGHT][MAP_WIDTH], moving_block_t *enemies, Uint32 *helmetSpawnTime, Uint32 *shieldStartTime, int *shieldActive, SDL_Texture* shieldTextures[]) {
    // Guarda la posición previa
    int prev_x = player->x;
    int prev_y = player->y;

    // Movimiento en función de la dirección
    if (d == LEFT) {
        player->x -= MOVEMENT_DELTA;
        player->angle = 180; // Cambiar el ángulo del jugador
    } 
    if (d == RIGHT) {
        player->x += MOVEMENT_DELTA;
        player->angle = 0; // Cambiar el ángulo del jugador
    }
    if (d == UP) {
        player->y -= MOVEMENT_DELTA;
        player->angle = -90; // Cambiar el ángulo del jugador
    }
    if (d == DOWN) {
        player->y += MOVEMENT_DELTA;
        player->angle = 90; // Cambiar el ángulo del jugador
    }

    // Verificar colisiones con bloques de la matriz
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            int block_type = map[y][x];
            if (block_type == BLOCK_GREEN) {
                continue; // Ignorar bloques verdes
            }
            if (block_type >= 0 && block_type <= 5 || block_type == brick_texture_X_plus_block || block_type == brick_texture_X_minus_block || block_type == brick_texture_Y_plus_block || block_type == brick_texture_Y_minus_block) {
                game_element_t block_element = {x * BLOCK_SIZE, y * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE};
                if (check_collision(*player, block_element)) {
                    // Si hay colisión, se restaura la posición anterior completa
                    player->x = prev_x;
                    player->y = prev_y;
                   // 

                    //Uint32 currentTime = SDL_GetTicks();
                   helmetActive = 1;
                    
                   //     game_element_t helmet_block = {helmetX * BLOCK_SIZE, helmetY * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE};
                       
                           
                        
                    

                    return;
                }
            }
        }
    }

    // Verificar colisiones con bloques
    for (int i = 0; i < num_blocks; i++) {
        if (blocks[i].block_type == BLOCK_GREEN) {
            continue; // Ignorar bloques verdes
        }
        game_element_t block_element = {blocks[i].x, blocks[i].y, blocks[i].w, blocks[i].h};
        if (check_collision(*player, block_element)) {
            // Si hay colisión, se restaura la posición anterior completa
            player->x = prev_x;
            player->y = prev_y;
            // Activa poder escudo automáticamente
          //  BLOCK_HELMET(player, map, helmetSpawnTime, shieldStartTime, shieldActive, shieldTextures);
            return;
        }
    }

    // Verificar colisiones con los enemigos
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (enemies[i].active) {
            game_element_t enemy_element = {enemies[i].x, enemies[i].y, enemies[i].w, enemies[i].h};
            if (check_collision(*player, enemy_element)) {
                // Si hay colisión, se restaura la posición anterior completa
                player->x = prev_x;
                player->y = prev_y;
                return;
            }
        }
    }

    // Luego de mover en cualquier dirección, chequea colisión con bloques especiales
    if (check_collision_with_special_blocks(player, blocks, num_blocks) == TRUE) {
        // Si hay colisión, se restaura la posición anterior completa
        player->x = prev_x;
        player->y = prev_y;
    }
}


static void draw_game_over() {


  SDL_Rect dest;

  dest.x = 0; // Colocar en la esquina superior izquierda
  dest.y = 0;
  dest.w = screen->w; // Ajustar al ancho de la pantalla
  dest.h = screen->h; // Ajustar al alto de la pantalla

  SDL_BlitScaled(end, NULL, screen, &dest);
}

/* Function: draw_menu
 * --------------------------------
 * This function is in charge of drawing the first screen that is
 * presented to the player.
 *
 * Arguments:
 *	none
 *
 * Return:
 *	void.
 */
static void draw_menu() {

  SDL_Rect src;
  SDL_Rect dest;

  src.x = 0;
  src.y = 0;
  src.w = title->w;
  src.h = title->h;

  dest.x = (screen->w / 2) - (src.w / 2);
  dest.y = (screen->h / 2) - (src.h / 2);
  dest.w = title->w;
  dest.h = title->h;

  SDL_BlitSurface(title, &src, screen, &dest);
}

/* Function: draw_game_element
 * -------------------------------
 * This functions draws a game element on the screen according to its
 * properties and coordinates. Please note that the element to be
 * drawn is passed as an reference insted of a value.
 *
 * Arguments:
 *	element: Element to be drawn on the screen.
 *
 * Return:
 *	void.
 */
 static void draw_game_element(game_element_t *element) {
    SDL_Rect dest;
    dest.x = element->x;
    dest.y = element->y;
    dest.w = element->w;
    dest.h = element->h;

    if (element->texture) {
        SDL_RenderCopyEx(renderer, element->texture, NULL, &dest, element->angle, NULL, SDL_FLIP_NONE);
    } else {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Blanco por defecto
        SDL_RenderFillRect(renderer, &dest);
    }

    // Dibujar la textura del escudo si está activa
    if (element->shieldTexture) {
        SDL_RenderCopy(renderer, element->shieldTexture, NULL, &dest);
    }
}

// The header of this two functions are for the student to complete
// Try changing the coordinates to see the effect that has on the game
// Also, are here the magic numbers justified? Or should be declared
// as constants in the beggining of the file?
static void draw_game_element_0_score(int playerLives) {

  SDL_Rect src;
  SDL_Rect dest;

  src.x = 0;
  src.y = 0;
  src.w = 64;
  src.h = 64;

  dest.x = (1750); // 12 is just padding spacing solo es para ubucarlo en pantalla ese numero
  dest.y = 600;
  dest.w = 64;
  dest.h = 64;

  if (playerLives > 0 && playerLives < 10) {

    src.x += src.w * playerLives;
  }

  SDL_BlitSurface(numbermap, &src, screen, &dest);
}

static void draw_game_element_1_score(int playerLives) {

  SDL_Rect src;
  SDL_Rect dest;

  src.x = 0;
  src.y = 0;
  src.w = 64;
  src.h = 64;

  dest.x = (screen->w / 2) + 12;
  dest.y = 0;
  dest.w = 64;
  dest.h = 64;

  if (g_score[1] > 0 && playerLives < 10) {

    src.x += src.w * playerLives;
  }

  SDL_BlitSurface(numbermap, &src, screen, &dest);
}
////////////////////////////////////////////////////////////////////////////



void render_text(SDL_Renderer *renderer, const char *text, int x, int y, TTF_Font *font, SDL_Color color) {
    SDL_Surface *surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect dest = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &dest);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}
//////////////////////////////////////////////////////////////////////




// Función para actualizar el contador de enemigos eliminados


void update_enemy_kill_count() {
    enemies_killed++; //  Incrementa el total de enemigos eliminados

    //  Verificar si quedan tanques restantes antes de disminuir
    if (num_tanques > 0) {
        num_tanques--; // Reduce la cantidad de tanques que quedan
    }

    // Eliminar un bloque de tanque si es necesario, visualmente
    for (int i = 0; i < MAX_TANK_BLOCKS; i++) {
        if (tank_blocks[i].active) { //Busca el primer bloque de tanque activo
            tank_blocks[i].active = 0; // Lo desactiva
            break; // solo elimina un bloque por enemigo eliminado
        }
    }
    // Obtener el índice del nivel actual, verifica que este dentro de los límites válidos
    int current_level_index = current_level - 1;
    if (current_level_index < 0 || current_level_index >= MAX_LEVELS) {
        return; // Evitar accesos fuera de rango
    }

    // Buscar el enemigo eliminado más recientemente en la lista de enemigos
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (!enemies[i].active) { // Si el enemigo ya está inactivo, significa que fue eliminado
            int enemy_type = enemies[i].type; // Obtener su tipo

            // Validar si es un tipo de enemigo válido
            if (enemy_type < 0 || enemy_type >= 6) {
                return;
            }

            //  Definir los puntajes por tipo de tanque
            int score_per_enemy[] = {100, 200, 100, 100, 300, 400}; 

            // Incrementar el contador de muertes y puntajes acumulados por nivel
            switch (enemy_type) {
                case 0: tank_1_kill_count[current_level_index]++; total_score_tank1 += score_per_enemy[0]; break;
                case 1: tank_2_kill_count[current_level_index]++; total_score_tank2 += score_per_enemy[1]; break;
                case 2: tank_3_kill_count[current_level_index]++; total_score_tank3 += score_per_enemy[2]; break;
                case 3: tank_4_kill_count[current_level_index]++; total_score_tank4 += score_per_enemy[3]; break;
                case 4: tank_5_kill_count[current_level_index]++; total_score_tank5 += score_per_enemy[4]; break;
                case 5: tank_6_kill_count[current_level_index]++; total_score_tank6 += score_per_enemy[5]; break;
            }

            // Calcular y almacenar el puntaje del tanque actual en el nivel
            tank_scores[current_level_index][enemy_type] =                   ///forma abreviada de escirbir multiples if-else condicion ? valor_si_verdadero: valor_si_falso:
                (enemy_type == 0 ? tank_1_kill_count[current_level_index] : // si el tipo de tanque es 0, toma el contador de muertes del tanque 1 en este nivel
                enemy_type == 1 ? tank_2_kill_count[current_level_index] :
                enemy_type == 2 ? tank_3_kill_count[current_level_index] :
                enemy_type == 3 ? tank_4_kill_count[current_level_index] :
                enemy_type == 4 ? tank_5_kill_count[current_level_index] :
                tank_6_kill_count[current_level_index]) * score_per_enemy[enemy_type];

            break; // Salir del bucle después de registrar un enemigo eliminado
        }
    }

    // Calcular el puntaje total del nivel sumando los puntajes de cada tanque
    int total_score = 0;
    for (int i = 0; i < 6; i++) {
        total_score += tank_scores[current_level_index][i];
    }

    //Actualizar el puntaje total del nivel actual
    level_scores[current_level_index] = total_score;

    // Calcular el puntaje total acumulado de todos los niveles
    grand_total_score = 0;
    for (int i = 0; i < MAX_LEVELS; i++) {
        grand_total_score += level_scores[i];
    }
}

////////////////////////////////////////////////////////////////
void draw_enemy_kill_count() {
    SDL_Rect src;
    SDL_Rect dest;
    
    int total_score = 0;

    //  Definir los puntajes por tipo de enemigo
    //int score_per_enemy[] = {100, 200, 100, 100, 700, 1000}; 

    // Calcular el puntaje total acumulado de enemigos eliminados
    for (int i = 0; i < 6; i++) {
        total_score += tank_scores[current_level - 1][i]; // Usar los puntajes almacenados
    }

    int digit, x_offset = 0;
    dest.y = 64; // Ubicar debajo del puntaje
    dest.w = 64;
    dest.h = 64;
    
    do {
        digit = total_score % 10; // Obtener el último dígito del puntaje
        total_score /= 10; // Reducir el puntaje
        
        src.x = digit * 64; // Posición en el mapa de números
        src.y = 0;
        src.w = 64;
        src.h = 64;
        
        dest.x = (screen->w / 2) + 12 - x_offset;
        x_offset += 64; // Desplazar cada número hacia la izquierda
        
        SDL_BlitSurface(numbermap, &src, screen, &dest);
    } while (total_score > 0);
}


/////////////////////////////////////////////////////////////
void draw_score_screen() {
    SDL_Rect dest; // Rectangulo usado para posicionar elementos usados de texto

    // Establece el color de fondo (negro) y limpia la pantalla
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Verifica si SDL_ttf no esta incializado e intenta inicializarlo
    if (TTF_WasInit() == 0 && TTF_Init() == -1) {
        printf("Error al inicializar SDL_ttf: %s\n", TTF_GetError());
        return;
    }

    // Carga la fuente desde el archivo con tamaño 24
    TTF_Font *font = TTF_OpenFont("/home/steven/Documents/BATLE CITY(12)/BATLE CITY/fonds/fond.ttf", 12);
    if (!font) {
        printf("Error al cargar la fuente: %s\n", TTF_GetError());
        return;
    }

    // Define el color del texxto blanco
    SDL_Color textColor = {255, 255, 255, 255}; // Color blanco

    int column_width = 300; // Ancho de cada columna
    int start_x = 100; // Posición X inicial
    int start_y = 50; // Posición Y inicial


        //  Mostrar título
        render_text(renderer, "PUNTAJES OBTENIDOS ", start_x, start_y, font, textColor);
        start_y += 150; // Ajustar posición después del título
    
//Recorre todos los niveles disponibles
    for (int level = 0; level < MAX_LEVELS; level++) {
        if (level_scores[level] == 0) continue; // Saltar niveles sin puntaje

        int total_score = level_scores[level]; // Puntaje total del nivel actual
        dest.y = start_y; //Posición vertical base para este nivel
        dest.x = start_x + (level * column_width); // Posición horizontal de esta columna

        // Crear y renderizar el tecyp que indica el número de nivel
        char level_text[20];
        snprintf(level_text, sizeof(level_text), "NIVEL %d", level + 1);
        render_text(renderer, level_text, dest.x, dest.y, font, textColor);

        //Crear y renderizar el puntaje total del nivel
        char score_text[20];
        snprintf(score_text, sizeof(score_text), "PUNTAJE %d", total_score);
        render_text(renderer, score_text, dest.x, dest.y + 30, font, textColor);

        //SDL_Rect texture_dest = {dest.x, dest.y + 60, 100, 100};

     
        int basic_kills = tank_1_kill_count[level] + tank_3_kill_count[level] + tank_4_kill_count[level];
        int basic_score = tank_scores[level][0] + tank_scores[level][2] + tank_scores[level][3];
        
        int blink_kills = tank_2_kill_count[level];
        int blink_score = tank_scores[level][1];
        
        int pink_kills = tank_5_kill_count[level];
        int pink_score = tank_scores[level][4];
        
        int fast_kills = tank_6_kill_count[level];
        int fast_score = tank_scores[level][5];
        // Mostrar puntajes totales por tipo de tanque
        char total_tank_text[50];

        // Puntaje combinado de los tanques"BÄSICOS": tipos 1,3 y 4

        snprintf(total_tank_text, sizeof(total_tank_text), "BASIC TANK%d PTS %d", basic_kills, basic_score);
        render_text(renderer, total_tank_text, dest.x, dest.y + 60, font, textColor);
        
        snprintf(total_tank_text, sizeof(total_tank_text), "BLINK TANK%d PTS %d", blink_kills, blink_score);
        render_text(renderer, total_tank_text, dest.x , dest.y + 100, font, textColor);
        
        snprintf(total_tank_text, sizeof(total_tank_text), "PINK TANK %d PTS %d", pink_kills, pink_score);
        render_text(renderer, total_tank_text, dest.x, dest.y + 140, font, textColor);
        
        snprintf(total_tank_text, sizeof(total_tank_text), "FAST TANK %d PTS %d ", fast_kills, fast_score);
        render_text(renderer, total_tank_text, dest.x, dest.y + 180, font, textColor);
        
    }

    //Muestra el puntaje de todos los niveles
    char total_score_text[30];
    snprintf(total_score_text, sizeof(total_score_text), "PUNTAJE TOTAL %d", grand_total_score);
    render_text(renderer, total_score_text, start_x + column_width * 2, start_y + 300, font, textColor);
    //presenta todo lo que se dibujó en la pantalla
    SDL_RenderPresent(renderer);
    //Libera la memoria de la fuente cargada
    TTF_CloseFont(font);
}
























////////////////////////////////////////////////////////////////////////////////
void updateEnemy(moving_block_t *enemy, block_t *map_blocks, int num_blocks,
    SDL_Surface *screen, game_element_t *player, int *state,
    Uint32 *gameOverStartTime, int *playerLives, int map[MAP_HEIGHT][MAP_WIDTH], SDL_Texture* enemyTextures[], int enemigosCongelados, Uint32 *helmetSpawnTime, Uint32 *shieldStartTime, int *shieldActive, SDL_Texture* shieldTextures[]) {
    int prevX, prevY;
    int originalSpeedX = enemy->speedX;
    int originalSpeedY = enemy->speedY;

    if (enemigosCongelados) {
        enemy->speedX = 0;
        enemy->speedY = 0;
        enemy->state = ENEMY_WAITING;
    }

    if (enemy->state == ENEMY_MOVING) {
        prevX = enemy->x;
        prevY = enemy->y;

        enemy->x += enemy->speedX;
        enemy->y += enemy->speedY;

        // Actualizar última dirección de movimiento
        if (enemy->speedX != 0) {
            enemy->lastDirectionX = (enemy->speedX > 0) ? 1 : -1;
            enemy->lastDirectionY = 0;
        } else if (enemy->speedY != 0) {
            enemy->lastDirectionX = 0;
            enemy->lastDirectionY = (enemy->speedY > 0) ? 1 : -1;
        }
    }

    // NUEVO: Asegurarse de que no se muevan en diagonal
    if (enemy->speedX != 0 && enemy->speedY != 0) {
        if (abs(enemy->speedX) > abs(enemy->speedY)) {
            enemy->speedY = 0;
        } else {
            enemy->speedX = 0;
        }
    }

    // Verificar límites de pantalla
    if (enemy->x < 0 || enemy->x > screen->w - enemy->w || enemy->y < 0 || enemy->y > screen->h - enemy->h) {
        enemy->x = prevX;
        enemy->y = prevY;
        enemy->state = ENEMY_WAITING;
        enemy->waitStart = SDL_GetTicks();
    } else {
        // Verificar colisiones con bloques del mapa (recorrer la matriz)
        for (int y = 0; y < MAP_HEIGHT; y++) {
            for (int x = 0; x < MAP_WIDTH; x++) {
                int block_type = map[y][x];
                if (block_type == BLOCK_GREEN)
                    continue;
                if (block_type >= 0 && block_type <= 5 || block_type == brick_texture_X_plus_block || block_type == brick_texture_X_minus_block || block_type == brick_texture_Y_minus_block || block_type == brick_texture_Y_plus_block) {
                    game_element_t block_element = {x * BLOCK_SIZE, y * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE};
                    if (check_collision((game_element_t){enemy->x, enemy->y, enemy->w, enemy->h}, block_element)) {
                        enemy->x = prevX;
                        enemy->y = prevY;
                        enemy->state = ENEMY_WAITING;
                        enemy->waitStart = SDL_GetTicks();
                        break;
                    }
                }
            }
        }

        // Verificar colisiones con bloques definidos en map_blocks
        for (int i = 0; i < num_blocks; i++) {
            if (map_blocks[i].block_type == BLOCK_GREEN)
                continue;
            if (check_collision((game_element_t){enemy->x, enemy->y, enemy->w, enemy->h},
                                (game_element_t){map_blocks[i].x, map_blocks[i].y, BLOCK_SIZE, BLOCK_SIZE})) {
                enemy->x = prevX;
                enemy->y = prevY;
                enemy->state = ENEMY_WAITING;
                enemy->waitStart = SDL_GetTicks();
                break;
            }
        }

        // Verificar colisiones con el jugador
        SDL_Rect rect1 = {enemy->x, enemy->y, enemy->w, enemy->h};
        SDL_Rect rect2 = {player->x, player->y, player->w, player->h};
        SDL_Rect result;
        if (SDL_IntersectRect(&rect1, &rect2, &result)) {
            enemy->x = prevX;
            enemy->y = prevY;
            enemy->state = ENEMY_WAITING;
            enemy->waitStart = SDL_GetTicks();
        }

        // Verificar colisiones con otros enemigos
        for (int i = 0; i < MAX_ENEMIES; i++) {
            if (&enemies[i] != enemy && enemies[i].active) { // Evitar la colisión consigo mismo
                SDL_Rect rect3 = {enemies[i].x, enemies[i].y, enemies[i].w, enemies[i].h};
                if (SDL_IntersectRect(&rect1, &rect3, &result)) {
                    enemy->x = prevX;
                    enemy->y = prevY;
                    enemy->state = ENEMY_WAITING;
                    enemy->waitStart = SDL_GetTicks();
                }
            }
        }

        // Restaurar la velocidad original después de la colisión
        enemy->speedX = originalSpeedX;
        enemy->speedY = originalSpeedY;
        // --- Lógica de disparo individual por enemigo ---
        Uint32 currentTime = SDL_GetTicks();
        if (!enemigosCongelados && currentTime - enemy->lastShotTime >= ENEMY_BULLET_COOLDOWN) {
            // Cada enemigo verifica su propio proyectil
            if (!enemy->projectile.active) {
                enemy->projectile.active = 1;
                // Posicionar el proyectil en el centro del enemigo
                enemy->projectile.x = enemy->x + enemy->w / 2 - enemy->projectile.w / 2;
                enemy->projectile.y = enemy->y + enemy->h / 2 - enemy->projectile.h / 2;

                // Ajustar la velocidad del proyectil según el tipo de enemigo
                int projectileSpeed;
                switch (enemy->type) {
                    case 0: // tank1.bmp
                    case 2: // tank3.bmp
                    case 3: // tank4.bmp
                        projectileSpeed = PROJECTILE_SPEED;
                        break;
                    case 1: // tank2.bmp (blind tank)
                        projectileSpeed = PROJECTILE_SPEED;
                        break;
                    case 4: // tank5.bmp (power tank)
                        projectileSpeed = PROJECTILE_SPEED * 2;
                        break;
                    case 5: // tank6.bmp (fast tank)
                        projectileSpeed = PROJECTILE_SPEED * 3;
                        break;
                    default:
                        projectileSpeed = PROJECTILE_SPEED;
                        break;
                }

                // Asignar velocidad al proyectil basada en la última dirección
                enemy->projectile.speedX = enemy->lastDirectionX * projectileSpeed;
                enemy->projectile.speedY = enemy->lastDirectionY * projectileSpeed;
                enemy->lastShotTime = currentTime; // Actualiza el tiempo del último disparo para este enemigo
                
                //VERIFICAR QUE EL PROJECTILE SE MUEVA SI NO SE ELIMNA DE PANTALLA
                if (enemy->projectile.speedX == 0 && enemy->projectile.speedY == 0) {
                    enemy->projectile.active = 0;
                    return;

                }

    // Verificar colisión entre el proyectil del enemigo y el proyectil del jugador
    if (enemy->projectile.active && player->projectile.active) {
        game_element_t enemy_proj = {enemy->projectile.x, enemy->projectile.y, enemy->projectile.w, enemy->projectile.h};
        game_element_t player_proj = {player->projectile.x, player->projectile.y, player->projectile.w, player->projectile.h};
        if (check_collision(enemy_proj, player_proj)) {
            enemy->projectile.active = 0;
            player->projectile.active = 0;
        }
    }



            }
        }

        // Actualizar la posición del proyectil
        if (enemy->projectile.active) {
            enemy->projectile.x += enemy->projectile.speedX;
            enemy->projectile.y += enemy->projectile.speedY;
            if (enemy->projectile.x < 0 || enemy->projectile.x > screen->w || enemy->projectile.y > screen->h) {
                enemy->projectile.active = 0;
            }
            // Verificar la colisión con el jugador
            if (check_collision((game_element_t){enemy->projectile.x, enemy->projectile.y, enemy->projectile.w, enemy->projectile.h}, *player)) {
                if (!*shieldActive) { // Verificar si el escudo está activo
                    printf("La bala mató al jugador. Vidas restantes: %d\n", *playerLives - 1);
                    (*playerLives)--;

                    // Que el jugador vuelva al inicio
                    player->x = PLAYER_START_X;
                    player->y = PLAYER_START_Y;

                    *shieldActive = 1;
                    *shieldStartTime = SDL_GetTicks();
                    *helmetSpawnTime = SDL_GetTicks();
                    player->helmetActive = 1;
                    BLOCK_HELMET(player, current_map, helmetSpawnTime, shieldStartTime, shieldActive, shieldTextures);

                    enemy->projectile.active = 0;
                    if (*playerLives <= 0) {
                     //   printf("GAME OVER\n");
                        *state = GAME_OVER;
                        *gameOverStartTime = SDL_GetTicks();
                    }
                } else {
                    // Si el escudo está activo, desactivar el proyectil sin hacer daño
                    enemy->projectile.active = 0;
                }
            }
            // Verificar colisiones con bloques de la matriz
            for (int y = 0; y < MAP_HEIGHT; y++) {
                for (int x = 0; x < MAP_WIDTH; x++) {
                    int block_type = map[y][x];
                    if (block_type == BLOCK_GREEN || block_type == BLOCK_BLUE) {
                        continue; // Ignorar bloques verdes y azules
                    }
                    if (block_type >= 0 && block_type <= 5 || block_type == brick_texture_X_plus_block || block_type == brick_texture_X_minus_block || block_type == brick_texture_Y_plus_block || block_type == brick_texture_Y_minus_block) {
                        game_element_t block_element = {x * BLOCK_SIZE, y * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE};
                        if (check_collision((game_element_t){enemy->projectile.x, enemy->projectile.y, enemy->projectile.w, enemy->projectile.h}, block_element)) {
                            enemy->projectile.active = 0;
                            if (block_type == SPECIAL_BLOCK) {
                                printf("¡La bala tocó el bloque especial! GAME OVER\n");
                                *state = GAME_OVER;
                                *gameOverStartTime = SDL_GetTicks();
                            }
                            if (block_type == BLOCK_YELLOW && enemy->projectile.speedX > 0) {
                                map[y][x] = brick_texture_X_minus_block; // Eliminar el bloque amarillo
                                enemy->projectile.active = 0; // Desactivar el proyectil
                                return;
                            }
                            if (block_type == BLOCK_YELLOW && enemy->projectile.speedX < 0) {
                                map[y][x] = brick_texture_X_plus_block; // Eliminar el bloque amarillo
                                enemy->projectile.active = 0; // Desactivar el proyectil
                                return;
                            }
                            if (block_type == BLOCK_YELLOW && enemy->projectile.speedY > 0) {
                                map[y][x] = brick_texture_Y_plus_block; // Eliminar el bloque amarillo
                                enemy->projectile.active = 0; // Desactivar el proyectil
                                return;
                            }
                            if (block_type == BLOCK_YELLOW && enemy->projectile.speedY < 0) {
                                map[y][x] = brick_texture_Y_minus_block; // Eliminar el bloque amarillo
                                enemy->projectile.active = 0; // Desactivar el proyectil
                                return;
                            }
                            if (block_type == brick_texture_X_minus_block || block_type == brick_texture_Y_minus_block  || block_type == brick_texture_X_plus_block || block_type == brick_texture_Y_plus_block )
                            {
                                map[y][x] = -1; // Eliminar el bloque amarillo
                                enemy->projectile.active = 0; // Desactivar el proyectil si choca con un bloque de textura de ladrillo
                                return;
                            } 
                            break;
                        }
                    }
                }
            }
        }
    }

    // Actualizar estado de espera: si el enemigo está esperando, cambiar de dirección
    if (enemy->state == ENEMY_WAITING && !enemigosCongelados) {
        if (SDL_GetTicks() - enemy->waitStart >= 500) {
            int direction = rand() % 4;
            int baseSpeed;

            // Ajustar la velocidad base según el tipo de enemigo
            switch (enemy->type) {
                case 0: // tank1.bmp
                case 2: // tank3.bmp
                case 3: // tank4.bmp
                    baseSpeed = 1;
                    break;
                case 1: // tank2.bmp (blind tank)
                    baseSpeed = 1;
                    break;
                case 4: // tank5.bmp (power tank)
                    baseSpeed = 2;
                    break;
                case 5: // tank6.bmp (fast tank)
                    baseSpeed = 3;
                    break;
                default:
                    baseSpeed = 10;
                    break;
            }

            switch (direction) {
                case 0:
                    enemy->speedX = 0;
                    enemy->speedY = -baseSpeed;
                    break;
                case 1:
                    enemy->speedX = 0;
                    enemy->speedY = baseSpeed;
                    break;
                case 2:
                    enemy->speedX = -baseSpeed;
                    enemy->speedY = 0;
                    break;
                case 3:
                    enemy->speedX = baseSpeed;
                    enemy->speedY = 0;
                    break;
            }
            enemy->state = ENEMY_MOVING;

            // Verificar colisiones con el jugador
            SDL_Rect rect1 = {enemy->x, enemy->y, enemy->w, enemy->h};
            SDL_Rect rect2 = {player->x, player->y, player->w, player->h};
            SDL_Rect result;
            if (SDL_IntersectRect(&rect1, &rect2, &result)) {
                enemy->x = prevX;
                enemy->y = prevY;
                enemy->state = ENEMY_WAITING;
                enemy->waitStart = SDL_GetTicks();
            }

            // Verificar colisiones con otros enemigos
            for (int i = 0; i < MAX_ENEMIES; i++) {
                if (&enemies[i] != enemy && enemies[i].active) { // Evitar la colisión consigo mismo
                    SDL_Rect rect3 = {enemies[i].x, enemies[i].y, enemies[i].w, enemies[i].h};
                    if (SDL_IntersectRect(&rect1, &rect3, &result)) {
                        enemy->x = prevX;
                        enemy->y = prevY;
                        enemy->state = ENEMY_WAITING;
                        enemy->waitStart = SDL_GetTicks();
                    }
                }
            }
        }
    }

    // Alternar texturas para el tanque de tipo 4
    if (enemy->type == 4) {
        Uint32 currentTime = SDL_GetTicks();
        if ((currentTime / 500) % 2 == 0) {
            enemy->texture = enemyTextures[4]; // tank5.bmp
        } else {
            enemy->texture = enemyTextures[6]; // tank5v2.bmp
        }
    }
}



void draw_enemies(SDL_Renderer* renderer, int balasCongeladas, int enemigosCongelados) {
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (enemies[i].active && !enemies[i].spawning) {
            SDL_Rect dest = { enemies[i].x, enemies[i].y, enemies[i].w, enemies[i].h };
            double angle = 0.0;

            // Determinar el ángulo de rotación basado en la velocidad
            if (!enemigosCongelados) {
                if (enemies[i].speedX > 0) {
                    angle = 0.0; // Derecha
                } else if (enemies[i].speedX < 0) {
                    angle = 180.0; // Izquierda
                } else if (enemies[i].speedY > 0) {
                    angle = 90.0; // Abajo
                } else if (enemies[i].speedY < 0) {
                    angle = -90.0; // Arriba
                }
            }

            if (enemies[i].texture) {
                SDL_RenderCopyEx(renderer, enemies[i].texture, NULL, &dest, angle, NULL, SDL_FLIP_NONE);
            } else {
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                SDL_RenderFillRect(renderer, &dest);
            }

            // No dibujar proyectiles si están congelados
            if (!balasCongeladas && enemies[i].projectile.active) {
                SDL_Rect projRect = { enemies[i].projectile.x, enemies[i].projectile.y, enemies[i].projectile.w, enemies[i].projectile.h };
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderFillRect(renderer, &projRect);
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////PODERES///////////////PODERES/////////////////PODERES////////////////PODERES////////////////PODERES/////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BLOCK_BOMB(game_element_t *player, moving_block_t *enemies, int num_enemies, int map[MAP_HEIGHT][MAP_WIDTH], Uint32 *bombSpawnTime, Uint32 *enemyRespawnTime) {
    Uint32 currentTime = SDL_GetTicks();
    static int bombActive = 0; // 1 si la bomba está activa, 0 si no
    static int bombX = -1, bombY = -1; // Coordenadas de la bomba
    static int enemiesEliminated = 0; // 1 si los enemigos fueron eliminados
  
    //  Si la bomba no está activa, aparecer en un espacio vacío cada 40s
    if (!bombActive && (currentTime - *bombSpawnTime >= 40000)) {
        int emptyCells[MAP_HEIGHT * MAP_WIDTH][2]; 
        int emptyCount = 0;
  
        // Buscar todos los espacios vacíos (-1)
        for (int y = 0; y < MAP_HEIGHT; y++) {
            for (int x = 0; x < MAP_WIDTH; x++) {
                if (map[y][x] == -1) { // Espacio vacío
                    emptyCells[emptyCount][0] = x;
                    emptyCells[emptyCount][1] = y;
                    emptyCount++;
                }
            }
        }
  
        // Si hay espacios vacíos disponibles, elegir uno al azar
        if (emptyCount > 0) {
            int randomIndex = rand() % emptyCount;
            bombX = emptyCells[randomIndex][0];
            bombY = emptyCells[randomIndex][1];
            map[bombY][bombX] = BOMB_BLOCK;
            *bombSpawnTime = currentTime;
            bombActive = 1;
            printf("Bomba apareció en (%d, %d)\n", bombX * BLOCK_SIZE, bombY * BLOCK_SIZE);
        }
    }
  
    // La bomba desaparece si no es recogida en 10 segundos
    if (bombActive && (currentTime - *bombSpawnTime >= 10000)) {
        if (bombX != -1 && bombY != -1 && map[bombY][bombX] == BOMB_BLOCK) {
            map[bombY][bombX] = -1;
            printf("La bomba desapareció\n");
            bombActive = 0;
            bombX = -1;
            bombY = -1;
        }
    }
  
    // Si el jugador toca la bomba, eliminar enemigos
    if (bombActive && bombX != -1 && bombY != -1) {
        game_element_t bomb_block = {bombX * BLOCK_SIZE, bombY * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE};
        if (check_collision(*player, bomb_block)) {
            printf(" ¡El jugador recogió la bomba! Enemigos eliminados.\n");
  
            // Eliminar enemigos
            for (int i = 0; i < num_enemies; i++) {
                if (enemies[i].active) {
                    enemies[i].active = 0;
                    enemies_killed++; // Incrementar el contador de enemigos eliminados
                    draw_enemy_kill_count();

                  
                }
            }
  
            *enemyRespawnTime = currentTime; // Guardar tiempo de eliminación
            enemiesEliminated = 1; // Marcar enemigos eliminados
            
            //actualizar proyectil
            for (int i = 0; i < num_enemies; i++) {
                if (enemies[i].projectile.active) {
                    


                }
            }

            // Eliminar la bomba
            map[bombY][bombX] = -1;
            bombActive = 0;
            bombX = -1;
            bombY = -1;
        }
    }
  
    // Después de 30s, reaparecen enemigos en posiciones aleatorias
    if (enemiesEliminated && (currentTime - *enemyRespawnTime >= 2)) {
        //printf("Enemigos reaparecen en posiciones aleatorias\n");
  
        



    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void tanque_poder(game_element_t *player, int map[MAP_HEIGHT][MAP_WIDTH], Uint32 *tanquePoderSpawnTime, int *playerLives) {
    Uint32 currentTime = SDL_GetTicks();
  
    //Si el TANQUE PODER no está activo, aparece en una celda vacía cada 25s
    if (!tanquePoderActive && (currentTime - *tanquePoderSpawnTime >= 25000)) {
        int emptyCells[MAP_HEIGHT * MAP_WIDTH][2];
        int emptyCount = 0;
  
        // Buscar espacios vacíos en el mapa
        for (int y = 0; y < MAP_HEIGHT; y++) {
            for (int x = 0; x < MAP_WIDTH; x++) {
                if (map[y][x] == -1) { // Espacio vacío
                    emptyCells[emptyCount][0] = x;
                    emptyCells[emptyCount][1] = y;
                    emptyCount++;
                }
            }
        }
  
        // Si hay espacios vacíos, elegir uno aleatorio
        if (emptyCount > 0) {
            int randomIndex = rand() % emptyCount;
            tanquePoderX = emptyCells[randomIndex][0];
            tanquePoderY = emptyCells[randomIndex][1];
            map[tanquePoderY][tanquePoderX] = TANQUE_PODER_BLOCK;
            *tanquePoderSpawnTime = currentTime;
            tanquePoderActive = 1;
            printf(" ¡Tanque Poder apareció en (%d, %d)!\n", tanquePoderX * BLOCK_SIZE, tanquePoderY * BLOCK_SIZE);
        }
    }
  
    // Si no se recoge en 15 segundos, desaparece
    if (tanquePoderActive && (currentTime - *tanquePoderSpawnTime >= 15000)) {
        if (tanquePoderX != -1 && tanquePoderY != -1 && map[tanquePoderY][tanquePoderX] == TANQUE_PODER_BLOCK) {
            map[tanquePoderY][tanquePoderX] = -1;
            printf(" El Tanque Poder desapareció\n");
            tanquePoderActive = 0;
            tanquePoderX = -1;
            tanquePoderY = -1;
        }
    }
  
    //  Si el jugador lo toca, gana una vida
    if (tanquePoderActive && tanquePoderX != -1 && tanquePoderY != -1) {
        game_element_t tanque_block = {tanquePoderX * BLOCK_SIZE, tanquePoderY * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE};
        if (check_collision(*player, tanque_block)) {
            (*playerLives)++;
            printf("¡El jugador recogió el Tanque Poder! Vidas extra: %d\n", *playerLives);
  
            // Eliminar el TANQUE PODER del mapa
            map[tanquePoderY][tanquePoderX] = -1;
            tanquePoderActive = 0;
            tanquePoderX = -1;
            tanquePoderY = -1;
        }
    }
  }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void bloque_temporizador(game_element_t *player, moving_block_t *enemies, int num_enemies,
    bullet_t *bullets, int num_bullets, int map[MAP_HEIGHT][MAP_WIDTH], 
    Uint32 *temporizadorSpawnTime, Uint32 *tiempoCongelacion, 
    int *enemigosCongelados, int *balasCongeladas, int *disparoBloqueado) {

    Uint32 currentTime = SDL_GetTicks();
    static int temporizadorActive = 0;
    static int temporizadorX = -1, temporizadorY = -1;
    // Aparece el TEMPORIZADOR cada 15s en un lugar aleatorio del mapa
    if (!temporizadorActive && (currentTime - *temporizadorSpawnTime >= 15000)) {
        int emptyCells[MAP_HEIGHT * MAP_WIDTH][2];
        int emptyCount = 0;

        for (int y = 0; y < MAP_HEIGHT; y++) {
            for (int x = 0; x < MAP_WIDTH; x++) {
                if (map[y][x] == -1) {
                    emptyCells[emptyCount][0] = x;
                    emptyCells[emptyCount][1] = y;
                    emptyCount++;
                }
            }
        }

        if (emptyCount > 0) {
            int randomIndex = rand() % emptyCount;
            temporizadorX = emptyCells[randomIndex][0];
            temporizadorY = emptyCells[randomIndex][1];
            map[temporizadorY][temporizadorX] = TEMPORIZADOR_PODER_BLOCK;
            *temporizadorSpawnTime = currentTime;
            temporizadorActive = 1;
        }
    }

    if (temporizadorActive && (currentTime - *temporizadorSpawnTime >= 10000)) {
        if (temporizadorX != -1 && temporizadorY != -1 && map[temporizadorY][temporizadorX] == TEMPORIZADOR_PODER_BLOCK) {
            map[temporizadorY][temporizadorX] = -1;
            temporizadorActive = 0;
            temporizadorX = -1;
            temporizadorY = -1;
        }
    }

    if (temporizadorActive && temporizadorX != -1 && temporizadorY != -1) {
        game_element_t temporizador_block = {temporizadorX * BLOCK_SIZE, temporizadorY * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE};
        if (check_collision(*player, temporizador_block)) {
            *tiempoCongelacion = currentTime;
            *enemigosCongelados = 1;
            *balasCongeladas = 1;
            *disparoBloqueado = 1;

            map[temporizadorY][temporizadorX] = -1;
            temporizadorActive = 0;
            temporizadorX = -1;
            temporizadorY = -1;
        }
    }

    if (*enemigosCongelados) {
        if (currentTime - *tiempoCongelacion >= 10000) {
            *enemigosCongelados = 0;
            *balasCongeladas = 0;
            *disparoBloqueado = 0;
        } else {
            for (int i = 0; i < num_enemies; i++) {
                enemies[i].speedX = 0;
                enemies[i].speedY = 0;
                enemies[i].state = ENEMY_WAITING;
            }
            for (int i = 0; i < num_bullets; i++) {
                bullets[i].active = 0;
            }
        }
    }
}
  
  /////////////////////////////////////////////////////////////////////////////////

  void BLOCK_PALA(game_element_t *player, int map[MAP_HEIGHT][MAP_WIDTH]) {
    Uint32 currentTime = SDL_GetTicks();
    static int transformedBlocks[8][2]; // Para almacenar las posiciones de los bloques convertidos
    static int numTransformed = 0;

    // Si la Pala no está activa, generarla en una celda vacía cada 30s
    if (!palaActive && (currentTime - palaSpawnTime >= 10000)) {
        int emptyCells[MAP_HEIGHT * MAP_WIDTH][2];
        int emptyCount = 0;

        // Buscar espacios vacíos
        for (int y = 0; y < MAP_HEIGHT; y++) {
            for (int x = 0; x < MAP_WIDTH; x++) {
                if (map[y][x] == -1) { // Celda vacía
                    emptyCells[emptyCount][0] = x;
                    emptyCells[emptyCount][1] = y;
                    emptyCount++;
                }
            }
        }

        // Si hay espacios vacíos, elegir uno aleatorio
        if (emptyCount > 0) {
            int randomIndex = rand() % emptyCount;
            palaX = emptyCells[randomIndex][0];
            palaY = emptyCells[randomIndex][1];
            map[palaY][palaX] = PALA_BLOCK;
            palaSpawnTime = currentTime;
            palaActive = 1;
            printf("Pala apareció en (%d, %d)\n", palaX, palaY);
        }
    }

    // Si la Pala no se recoge en 10 segundos, desaparece
    if (palaActive && (currentTime - palaSpawnTime >= 10000)) {
        if (palaX != -1 && palaY != -1 && map[palaY][palaX] == PALA_BLOCK) {
            map[palaY][palaX] = -1;
            printf("La Pala desapareció\n");
            palaActive = 0;
            palaX = -1;
            palaY = -1;
        }
    }

    // Si el jugador toca la Pala, activa la transformación de bloques
    if (palaActive && palaX != -1 && palaY != -1) {
        game_element_t pala_block = {palaX * BLOCK_SIZE, palaY * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE};
        if (check_collision(*player, pala_block)) {
            printf("¡El jugador recogió la Pala! Transformando bloques...\n");

            // Buscar la posición del SPECIAL_BLOCK
            int specialX = -1, specialY = -1;
            for (int y = 0; y < MAP_HEIGHT; y++) {
                for (int x = 0; x < MAP_WIDTH; x++) {
                    if (map[y][x] == SPECIAL_BLOCK) {
                        specialX = x;
                        specialY = y;
                        break;
                    }
                }
                if (specialX != -1) break;
            }

            if (specialX != -1 && specialY != -1) {
                // Definir los bloques alrededor del SPECIAL_BLOCK a convertir en metal
                int blocksToConvert[][2] = {
                    {specialX - 1, specialY}, {specialX + 1, specialY}, 
                    {specialX, specialY - 1}, {specialX, specialY + 1}, 
                    {specialX - 1, specialY - 1}, {specialX + 1, specialY - 1}, 
                    {specialX - 1, specialY + 1}, {specialX + 1, specialY + 1} 
                };
                numTransformed = sizeof(blocksToConvert) / sizeof(blocksToConvert[0]);

                // Convertir ladrillos en bloques de metal y almacenar sus posiciones
                for (int i = 0; i < numTransformed; i++) {
                    int bx = blocksToConvert[i][0];
                    int by = blocksToConvert[i][1];

                    if (bx >= 0 && bx < MAP_WIDTH && by >= 0 && by < MAP_HEIGHT && 
                        (map[by][bx] == BLOCK_YELLOW || map[by][bx] == brick_texture_X_plus_block || 
                         map[by][bx] == brick_texture_X_minus_block || map[by][bx] == brick_texture_Y_plus_block || 
                         map[by][bx] == brick_texture_Y_minus_block)) {
                        map[by][bx] = BLOCK_WHITE;
                        transformedBlocks[i][0] = bx;
                        transformedBlocks[i][1] = by;
                    }
                }

                palaEffectStartTime = currentTime;
                palaActive = 2;
            }

            // Eliminar la Pala del mapa
            map[palaY][palaX] = -1;
            palaX = -1;
            palaY = -1;
        }
    }

    // Si el efecto está activo, después de 10 segundos, revierte los bloques
    if (palaActive == 2 && (currentTime - palaEffectStartTime >= 10000)) {
        printf(" El efecto de la Pala terminó. Restaurando bloques...\n");

        // Restaurar bloques a ladrillo
        for (int i = 0; i < numTransformed; i++) {
            int bx = transformedBlocks[i][0];
            int by = transformedBlocks[i][1];
            if (bx >= 0 && bx < MAP_WIDTH && by >= 0 && by < MAP_HEIGHT) {
                map[by][bx] = BLOCK_YELLOW; // Restaurar a ladrillo
            }
        }

        palaActive = 0;
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BLOCK_STAR(game_element_t *player, int map[MAP_HEIGHT][MAP_WIDTH]) {
    Uint32 currentTime = SDL_GetTicks();

    // Generar la estrella cada 10 segundos si no está activa
    if (!starActive && (currentTime - starSpawnTime >= 10000)) {
        int emptyCells[MAP_HEIGHT * MAP_WIDTH][2];
        int emptyCount = 0;

        // Buscar celdas vacías en el mapa
        for (int y = 0; y < MAP_HEIGHT; y++) {
            for (int x = 0; x < MAP_WIDTH; x++) {
                if (map[y][x] == -1) { // Celda vacía
                    emptyCells[emptyCount][0] = x;
                    emptyCells[emptyCount][1] = y;
                    emptyCount++;
                }
            }
        }

        // Si hay celdas vacías, colocar la estrella en una aleatoria
        if (emptyCount > 0) {
            int randomIndex = rand() % emptyCount;
            starX = emptyCells[randomIndex][0];
            starY = emptyCells[randomIndex][1];
            map[starY][starX] = STAR_BLOCK;
            starSpawnTime = currentTime;
            starActive = 1;
            printf(" Estrella apareció en (%d, %d)\n", starX, starY);
        }
    }

    // Desaparecer la estrella después de 10 segundos si no se recoge
    if (starActive == 1 && (currentTime - starSpawnTime >= 10000)) {
        if (starX != -1 && starY != -1 && map[starY][starX] == STAR_BLOCK) {
            map[starY][starX] = -1;
            printf(" La estrella desapareció\n");
            starActive = 0;
            starX = -1;
            starY = -1;
        }
    }

    // Si el jugador recoge la estrella, activar efectos
    if (starActive && starX != -1 && starY != -1) {
        game_element_t star_block = {starX * BLOCK_SIZE, starY * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE};
        if (check_collision(*player, star_block)) {
            printf("¡El jugador recogió la estrella! Aumentando el poder ofensivo...\n");

            // Incrementar el poder acumulativamente
            if (powerLevel < MAX_POWER_LEVEL) {
                powerLevel++;
            }

            // Aplicar efectos acumulativos según el nivel de poder
            if (powerLevel >= 1) {
                bulletSpeedPlayer =  bulletSpeed; // Aumenta la velocidad del proyectil
                printf("⚡ Nivel 1: Balas ahora tienen velocidad %d\n", bulletSpeedPlayer);
            }
            if (powerLevel >= 2) {
                maxBullets = 2; // Puede disparar dos balas a la vez
                printf(" Nivel 2: Ahora puede disparar 2 balas al mismo tiempo\n");
            }
            if (powerLevel >= 3) {
                bulletDestroySteel = 1; // Puede destruir acero
                bulletDamageBrick = 2;  // Doble daño contra ladrillos
                printf("Nivel 3: Balas destruyen acero y hacen más daño a ladrillos\n");
            }

            starEffectStartTime = currentTime;
            starActive = 0; // Desaparece al ser recogida

            // Eliminar la estrella del mapa
            map[starY][starX] = -1;
            starX = -1;
            starY = -1;
        }
    }

    // Si el jugador pierde una vida, restablecer el poder ofensivo
   // Si el jugador pierde una vida, restablecer el poder ofensivo
    static int lastLives = 0; // Almacena el número de vidas anterior
    if (player->lives < lastLives) {
        printf("El jugador perdió una vida. Restableciendo poder ofensivo...\n");
        powerLevel = 0;
        bulletSpeed = PROJECTILE_SPEED;
        maxBullets = 1;
        bulletDestroySteel = 0;
        bulletDamageBrick = 1;
    }
    lastLives = player->lives; // Actualizar la cantidad de vidas
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void draw_maping_blocks(SDL_Surface *surface, int map[MAP_HEIGHT][MAP_WIDTH], int block_width, int block_height) {
  for (int y = 0; y < MAP_HEIGHT; y++) {
      for (int x = 0; x < MAP_WIDTH; x++) {
          int block_type = map[y][x];
          if (block_type >= 0 && block_type <= 5) { // Incluir bloques de tipo 0 (rojo), 1 (verde), 2 (azul), 3 (amarillo), 4 (blanco), 5 (especial)
              draw_block_like_type_surface(surface, x * block_width, y * block_height, block_type, block_width, block_height, map_blocks, num_blocks);
          }
         ///DIBUJA PODER BOMBA  
          if (block_type == BOMB_BLOCK) {
            draw_block_like_type_surface(surface, x * block_width, y * block_height, BOMB_BLOCK, block_width, block_height, map_blocks, num_blocks);
        
        }
          // DIBUJA PODER CASCO
         if (block_type == HELMET_BLOCK) {
         draw_block_like_type_surface(surface, x * block_width, y * block_height, HELMET_BLOCK, block_width, block_height, map_blocks, num_blocks);
             }

        // DIBUJA PODER TANQUE
         if (block_type == TANQUE_PODER_BLOCK) {
            draw_block_like_type_surface(surface, x * block_width, y * block_height, TANQUE_PODER_BLOCK, block_width, block_height, map_blocks, num_blocks);  
         }

        // DIBUJA PODER TEMPORIZADIR
           if (block_type == TEMPORIZADOR_PODER_BLOCK) {
            draw_block_like_type_surface(surface, x * block_width, y * block_height, TEMPORIZADOR_PODER_BLOCK, block_width, block_height, map_blocks, num_blocks);  
                 }
      
                  // DIBUJA PODER PALA
          if (block_type == PALA_BLOCK) {
              draw_block_like_type_surface(surface, x * block_width, y * block_height, PALA_BLOCK, block_width, block_height, map_blocks, num_blocks);
          }
        // DIBUJA PODER ESTRELLITA
                if (block_type == STAR_BLOCK) {
                    draw_block_like_type_surface(surface, x * block_width, y * block_height, STAR_BLOCK, block_width, block_height, map_blocks, num_blocks);
                }
        
                if (block_type == vidas_texture_BLOCK) {
                    draw_block_like_type_surface(surface, x * block_width, y * block_height, vidas_texture_BLOCK, block_width, block_height, map_blocks, num_blocks);
                
                }
                if (block_type == tanques_texture_BLOCK) {
                    draw_block_like_type_surface(surface, x * block_width, y * block_height, tanques_texture_BLOCK, block_width, block_height, map_blocks, num_blocks);
                
                }

            if (block_type == brick_texture_X_plus_block) {
                draw_block_like_type_surface(surface, x * block_width, y * block_height, brick_texture_X_plus_block, block_width, block_height, map_blocks, num_blocks);
            
            }
            if (block_type == brick_texture_Y_plus_block) {
                draw_block_like_type_surface(surface, x * block_width, y * block_height, brick_texture_Y_plus_block, block_width, block_height, map_blocks, num_blocks);
            
            }
            if (block_type == brick_texture_X_minus_block) {
                draw_block_like_type_surface(surface, x * block_width, y * block_height, brick_texture_X_minus_block, block_width, block_height, map_blocks, num_blocks);
            
            }
            if (block_type == brick_texture_Y_minus_block) {
                draw_block_like_type_surface(surface, x * block_width, y * block_height, brick_texture_Y_minus_block, block_width, block_height, map_blocks, num_blocks);
            
            }
            if (block_type == SPAWN0_animation_block) {
                draw_block_like_type_surface(surface, x * block_width, y * block_height, SPAWN0_animation_block, block_width, block_height, map_blocks, num_blocks);
            
            }
            if (block_type == SPAWN1_animation_block) {
                draw_block_like_type_surface(surface, x * block_width, y * block_height, SPAWN1_animation_block, block_width, block_height, map_blocks, num_blocks);
            
            }
            if (block_type == SPAWN2_animation_block) {
                draw_block_like_type_surface(surface, x * block_width, y * block_height, SPAWN2_animation_block, block_width, block_height, map_blocks, num_blocks);
            
            }
            if (block_type == SPAWN3_animation_block) {
                draw_block_like_type_surface(surface, x * block_width, y * block_height, SPAWN3_animation_block, block_width, block_height, map_blocks, num_blocks);
            
            }
        
      }

  }
}




// Función para dibujar la pantalla de pausa
static void draw_pause() {
  // Definir el rectángulo completo para la pantalla
  SDL_Rect dest;
  dest.x = 0;
  dest.y = 0;
  dest.w = screen->w;
  dest.h = screen->h;

  // Rellenar la pantalla con color negro (0,0,0)
  // Cargar la imagen de pausa
  SDL_Surface *pauseMessage = SDL_LoadBMP("pause.bmp");
  if (pauseMessage == NULL) {
      printf("Error al cargar pause.bmp: %s\n", SDL_GetError());
      return;
  }

  // Centramos la imagen de pausa
  SDL_Rect destMsg;
  destMsg.x = (screen->w - pauseMessage->w) / 2;
  destMsg.y = (screen->h - pauseMessage->h) / 2;
  destMsg.w = pauseMessage->w;
  destMsg.h = pauseMessage->h;

  // Dibujar la imagen de pausa sobre el fondo negro
  SDL_BlitSurface(pauseMessage, NULL, screen, &destMsg);
  SDL_FreeSurface(pauseMessage);
}

static void draw_level_image(SDL_Surface *level_image) {
    if (!level_image) {
        printf("Error: Imagen de nivel no cargada.\n");
        return;
    }

    // Crear una textura desde la imagen para usar con SDL_Renderer
    SDL_Texture *level_texture = SDL_CreateTextureFromSurface(renderer, level_image);
    if (!level_texture) {
        printf("Error al crear textura: %s\n", SDL_GetError());
        return;
    }

    // Limpiar la pantalla
    SDL_RenderClear(renderer);

    // Dibujar la imagen
    SDL_RenderCopy(renderer, level_texture, NULL, NULL);

    // Actualizar la pantalla
    SDL_RenderPresent(renderer);

    // Esperar 2 segundos para que el jugador vea la imagen
    //SDL_Delay(200);

    // Liberar la textura
    SDL_DestroyTexture(level_texture);
}








void reset_position(game_element_t *player, moving_block_t *enemy,Uint32 *helmetSpawnTime, Uint32 *shieldStartTime, int *shieldActive, SDL_Texture* shieldTextures[]) {
    player->x = PLAYER_START_X;
    player->y = PLAYER_START_Y;
    player->w = BLOCK_SIZE;
    player->h = BLOCK_SIZE;

    // Inicializar la posición del enemigo
    enemy->x = 1600;
    enemy->y = 50;
    enemy->w = BLOCK_SIZE;
    enemy->h = BLOCK_SIZE;
    enemy->speedX = 1;
    enemy->speedY = 0;
    enemy->state = ENEMY_MOVING;
    enemy->waitStart = 0;
    enemy->block_type = BLOCK_ENEMY;

    // Activar el poder del casco
    *shieldActive = 1;
        *shieldStartTime = SDL_GetTicks();
        *helmetSpawnTime = SDL_GetTicks();
        player->helmetActive = 1;
   BLOCK_HELMET(player, current_map, helmetSpawnTime, shieldStartTime, shieldActive, shieldTextures);
}

///////////////////////
void init_enemies() {
  for (int i = 0; i < MAX_ENEMIES; i++) {
      enemies[i].active = 0;
      enemies[i].x = 0;
      enemies[i].y = 0;
      enemies[i].w = 49;
      enemies[i].h = 49;
      enemies[i].lastDirectionX = 0;
      enemies[i].lastDirectionY = 0;
      enemies[i].lastShotTime = 0;
      enemies[i].projectile.active = 0;
      enemies[i].projectile.w = 10;
      enemies[i].projectile.h = 10;
      enemies[i].speedX = 1;  // velocidad horizontal baja
      enemies[i].speedY = 0;  // velocidad vertical baja
      enemies[i]. hitCount =0;
  }
}


void iniciar_spawn_enemigo(int x, int y) {
    spawn_animation_t spawn;
    spawn.x = x;
    spawn.y = y;
    spawn.active = 1;
    spawn.StartTime = SDL_GetTicks();
}

void update_spawn_animation(spawn_animation_t *spawn, SDL_Texture* spawnTextures[]) {
    if (spawn->active) {
        Uint32 elapsed = SDL_GetTicks() - spawn->StartTime;
        int frame = (elapsed / SPAWN_FRAME_DELAY) % NUM_SPAWN_FRAMES;
        if (elapsed >= SPAWN_ANIMATION_DURATION) {
            spawn->active = 0; // Terminar la animación
        } else {
            SDL_Rect dest = {spawn->x, spawn->y, BLOCK_SIZE, BLOCK_SIZE};
            SDL_RenderCopy(renderer, spawnTextures[frame], NULL, &dest);
        }
    }
}


void draw_spawn_animation(spawn_animation_t *spawn, SDL_Texture* spawnTextures[]) {
    if (spawn->active) {
        Uint32 elapsed = SDL_GetTicks() - spawn->StartTime;
        int frame = (elapsed / SPAWN_FRAME_DELAY) % NUM_SPAWN_FRAMES;
        SDL_Rect dest = {spawn->x, spawn->y, BLOCK_SIZE, BLOCK_SIZE};
        SDL_RenderCopy(renderer, spawnTextures[frame], NULL, &dest);
    }
}
void update_enemies(Uint32 currentTime, SDL_Texture* enemyTextures[], block_t* map_blocks, int num_blocks, SDL_Surface* screen, game_element_t* player, int* state, Uint32* gameOverStartTime, int* playerLives, int map[MAP_HEIGHT][MAP_WIDTH]) {
    static Uint32 lastSpawnTime = 0;
    static int spawnIndex = 0;
    int activeEnemies = 0;
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (enemies[i].active) {
            activeEnemies++;
        }
    }

    if (activeEnemies < 4 && currentTime - lastSpawnTime >= ENEMY_SPAWN_INTERVAL) {
        for (int i = 0; i < MAX_ENEMIES; i++) {
            if (!enemies[i].active) {
                enemies[i].active = 1;
                enemies[i].spawning = 1;
                enemies[i].spawnStartTime = SDL_GetTicks();
                enemies[i].spawn_animation.x = spawn_points[spawnIndex].x;
                enemies[i].spawn_animation.y = spawn_points[spawnIndex].y;
                enemies[i].spawn_animation.active = 1;
                enemies[i].spawn_animation.StartTime = SDL_GetTicks();

                enemies[i].x = spawn_points[spawnIndex].x;
                enemies[i].y = spawn_points[spawnIndex].y;
                enemies[i].w = BLOCK_SIZE;
                enemies[i].h = BLOCK_SIZE;
                int randomIndex = rand() % 6;
                enemies[i].texture = enemyTextures[randomIndex];
                enemies[i].type = randomIndex;

                enemies[i].lastDirectionX = 0;
                enemies[i].lastDirectionY = 0;
                enemies[i].lastShotTime = 0;
                enemies[i].projectile.active = 0;
                enemies[i].projectile.w = 10;
                enemies[i].projectile.h = 10;
                enemies[i].hitCount = 0;

                switch (enemies[i].type) {
                    case 0:
                    case 2:
                    case 3:
                        enemies[i].speedX = 1;
                        enemies[i].speedY = 0;
                        break;
                    case 1:
                        enemies[i].speedX = 0;
                        enemies[i].speedY = 1;
                        break;
                    case 4:
                        enemies[i].speedX = 2;
                        enemies[i].speedY = 0;
                        break;
                    case 5:
                        enemies[i].speedX = 0;
                        enemies[i].speedY = 3;
                        enemies[i].projectile.speedX = PROJECTILE_SPEED * 5;
                        enemies[i].projectile.speedY = PROJECTILE_SPEED * 5;
                        break;
                    default:
                        enemies[i].speedX = 1;
                        enemies[i].speedY = 0;
                        break;
                }

                lastSpawnTime = currentTime;
                spawnIndex = (spawnIndex + 1) % NUM_SPAW_POINTS;
                break;
            }
        }
    }

    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (enemies[i].active) {
            if (enemies[i].spawning) {
                Uint32 elapsed = SDL_GetTicks() - enemies[i].spawnStartTime;
                int currentFrame = elapsed / SPAWN_FRAME_DELAY;
                if (currentFrame >= NUM_SPAWN_FRAMES) {
                    enemies[i].spawning = 0;
                }
            } else {
                updateEnemy(&enemies[i], map_blocks, num_blocks, screen, player, state, gameOverStartTime, playerLives, map, enemyTextures, enemigosCongelados, &helmetSpawnTime, &shieldStartTime, &shieldActive, shieldTextures);
            }
        }
    }
}


//hacemos una extrctura para manejar las explciones  (TODAVIA NO FUNCIONA)
typedef struct explosion_t {
    int x, y;
    int active;
    Uint32 startTime;
    int currentFrame;
} explosion_t;

#define MAX_EXPLOSIONS 10
explosion_t explosions[MAX_EXPLOSIONS];












 /*El anglo del enemigo se determina segun la velocidad osea la funcion de velocidad con  SDL_RenderCopyEx*/


// creamos una funcion para dibujar los enemigos 



/// reasemos el projectile del enemigo


// Función para dibujar un número en la pantalla
void draw_number(SDL_Surface *surface, int number, int x, int y) {
    SDL_Rect src;
    SDL_Rect dest;

    // Asumiendo que cada número en numbermap.bmp tiene un tamaño de 64x64 píxeles
    int digit_width = 64; 
    int digit_height = 64;

    //esto se usa asi si quisieramos dibujar el numero 3 se guarda eb digit el numero y se multiplica por
    //64 para que se dibuje el numero 3. Por que 64 es el tamaño de cada numero en el archivo numbermap.bmp
    //src.y = 0;: Esta línea establece la coordenada y del rectángulo de origen en 0. Esto asume que todos los dígitos están en una sola fila en la parte superior de la imagen numbermap.bmp.
//src.h = digit_height;: Esta línea establece la altura del rectángulo de origen a la altura de un dígito (64 píxeles). Esto asegura que solo se seleccione el dígito deseado de la imagen.

    // Convertir el número a una cadena para dibujar cada dígito por separado
    char num_str[10];
    snprintf(num_str, sizeof(num_str), "%d", number);

    for (int i = 0; num_str[i] != '\0'; i++) {
        int digit = num_str[i] - '0'; // Convertir el carácter a un número

        src.x = digit * digit_width;
        src.y = 0;
        src.w = digit_width;
        src.h = digit_height;

        dest.x = x + i * digit_width;
        dest.y = y;
        dest.w = digit_width;
        dest.h = digit_height;

        SDL_BlitSurface(numbermap, &src, surface, &dest);
    }
}



////////////////////////////////////////////////////////////////////////
// Dibuja proyectil con SDL_Surface que trabaja por pixeles en lugar de texturas
void draw_projectile(SDL_Renderer *renderer, projectile_t *proj) {
    if (proj->active) {
        SDL_Rect rect = {proj->x, proj->y, proj->w, proj->h};

       
       
       
        // Usar la textura de prueba para el proyectil
       
       
        

        Uint32 currenTime = SDL_GetTicks();
        SDL_Surface *current_surface = NULL;
        if ((currenTime/100)%2==0) {
            SDL_Surface *spawn3_surface = SDL_LoadBMP("SPAWN0.bmp");
        SDL_Texture *spawn3_animation = SDL_CreateTextureFromSurface(renderer, spawn3_surface);
        SDL_FreeSurface(spawn3_surface);
        SDL_RenderCopy(renderer, spawn3_animation, NULL, &rect);
        SDL_DestroyTexture(spawn3_animation);
        } else {
            SDL_Surface *spawn2_surface = SDL_LoadBMP("SPAWN3.bmp");
            SDL_Texture *spawn2_animation = SDL_CreateTextureFromSurface(renderer, spawn2_surface);
            SDL_FreeSurface(spawn2_surface);
            SDL_RenderCopy(renderer, spawn2_animation, NULL, &rect);
            SDL_DestroyTexture(spawn2_animation);
     
        }
       
       
       
       
    }
}



  ///////////////////////////////////////////////////////////////////////////


  void reset_game(game_element_t *player, moving_block_t *enemies, int num_enemies, int map[MAP_HEIGHT][MAP_WIDTH], int *playerLives, Uint32 *gameOverStartTime) {
    // Reiniciar la posición del jugador
    player->x = PLAYER_START_X;
    player->y = PLAYER_START_Y;
    player->w = BLOCK_SIZE;
    player->h = BLOCK_SIZE;
  
    // Reiniciar las vidas del jugador
    *playerLives = 3;
  
    // Reiniciar el tiempo de inicio del game over
    *gameOverStartTime = 0;
  
    // Reiniciar los enemigos
    for (int i = 0; i < num_enemies; i++) {
        enemies[i].active = 0;
        enemies[i].x = 0;
        enemies[i].y = 0;
        enemies[i].w = BLOCK_SIZE;
        enemies[i].h = BLOCK_SIZE;
        enemies[i].lastDirectionX = 0;
        enemies[i].lastDirectionY = 0;
        enemies[i].lastShotTime = 0;
        enemies[i].projectile.active = 0;
        enemies[i].projectile.w = 10;
        enemies[i].projectile.h = 10;
        enemies[i].speedX = 1;  // velocidad horizontal baja
        enemies[i].speedY = 0;  // velocidad vertical baja
    }
  
    // Reiniciar el mapa al nivel 1
    memcpy(current_map, map, sizeof(current_map));
    current_level = 1;

    // Reiniciar los puntajes de los tanques
    for (int i = 0; i < MAX_LEVELS; i++) {
        for (int j = 0; j < 6; j++) {
            tank_scores[i][j] = 0;
        }
    }

    // Reiniciar los contadores de muertes por tipo de tanque
    memset(tank_1_kill_count, 0, sizeof(tank_1_kill_count));
    memset(tank_2_kill_count, 0, sizeof(tank_2_kill_count));
    memset(tank_3_kill_count, 0, sizeof(tank_3_kill_count));
    memset(tank_4_kill_count, 0, sizeof(tank_4_kill_count));
    memset(tank_5_kill_count, 0, sizeof(tank_5_kill_count));
    memset(tank_6_kill_count, 0, sizeof(tank_6_kill_count));

    // Reiniciar el puntaje total acumulado
    grand_total_score = 0;
}










void update_projectile(projectile_t *proj, block_t *map_blocks, int num_blocks, int map[MAP_HEIGHT][MAP_WIDTH], int *state, Uint32 *gameOverStartTime, moving_block_t *enemies, int num_enemies, SDL_Texture* enemyTextures[8]) {
    if (proj->active) {
        

        if (powerLevel >= 1) {
            proj->x += proj->speedX * bulletSpeedPlayer/2;
            proj->y += proj->speedY * bulletSpeedPlayer/2 ;
        } else {
            proj->x += proj->speedX * bulletSpeedPlayer;
            proj->y += proj->speedY * bulletSpeedPlayer;
        }
        

        //si no se mueve el projectile eliminar el projectile 
        if (proj->speedX == 0 && proj->speedY == 0) {
            proj->active = 0;
            return;
        }



    
        // Desactivar el proyectil si sale de la pantalla
        if (proj->x < 0 || proj->x > SCREEN_WIDTH || proj->y < 0 || proj->y > SCREEN_HEIGHT) {
            proj->active = 0;
            return;
        }
        

        for (int i = 0; i < num_enemies; i++) {
            if (enemies[i].active && check_collision((game_element_t){proj->x, proj->y, proj->w, proj->h}, (game_element_t){enemies[i].projectile.x, enemies[i].projectile.y, enemies[i].projectile.w, enemies[i].projectile.h})) {
                proj->active = 0;
                enemies[i].projectile.active = 0;
                return;
            }
        }







        // Verificar colisiones con bloques de la matriz
        for (int y = 0; y < MAP_HEIGHT; y++) {
            for (int x = 0; x < MAP_WIDTH; x++) {
                int block_type = map[y][x];
                if (block_type == BLOCK_GREEN || block_type == BLOCK_BLUE) {
                    continue; // Ignorar bloques verdes y azules
                }
                if (block_type >= 0 && block_type <= 5 || block_type == brick_texture_X_plus_block || block_type == brick_texture_X_minus_block || block_type == brick_texture_Y_plus_block || block_type == brick_texture_Y_minus_block) {
                    game_element_t block_element = {x * BLOCK_SIZE, y * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE};
                    if (check_collision((game_element_t){proj->x, proj->y, proj->w, proj->h}, block_element)) {
                        proj->active = 0; // Desactivar el proyectil si choca con un bloque







                        if (block_type == BLOCK_YELLOW && proj->speedX > 0) {
                            map[y][x] = brick_texture_X_minus_block; // Eliminar el bloque amarillo
                            proj->active = 0; // Desactivar el proyectil
                            return;
                        }
                        if (block_type == BLOCK_YELLOW && proj->speedX < 0) {
                            map[y][x] = brick_texture_X_plus_block; // Eliminar el bloque amarillo
                            proj->active = 0; // Desactivar el proyectil
                            return;
                        }
                        if (block_type == BLOCK_YELLOW && proj->speedY > 0) {
                            map[y][x] = brick_texture_Y_plus_block; // Eliminar el bloque amarillo
                            proj->active = 0; // Desactivar el proyectil
                            return;
                        }
                        if (block_type == BLOCK_YELLOW && proj->speedY < 0) {
                            map[y][x] = brick_texture_Y_minus_block; // Eliminar el bloque amarillo
                            proj->active = 0; // Desactivar el proyectil
                            return;
                        }
                        if (block_type == brick_texture_X_minus_block || block_type == brick_texture_Y_minus_block  || block_type == brick_texture_X_plus_block || block_type == brick_texture_Y_plus_block )
                        {
                            map[y][x] = -1; // Eliminar el bloque amarillo
                            proj->active = 0; // Desactivar el proyectil si choca con un bloque de textura de ladrillo
                            return;
                        } 
                         
                        

                // BLOQUE DE METAL (solo destruible con powerLevel 3+)
                if (block_type == BLOCK_WHITE) {
                    if (powerLevel >= 3) {
                        map[y][x] = -1;
                        printf(" Bloque metal destruido por balas de nivel 3\n");
                    }
                    return;
                }

                // BLOQUE ROJO (nunca se destruye) margenes grises
                if (block_type == BLOCK_RED) {
                    return;
                            
                     if (powerLevel >= 3) {
                        map[y][x] = -1;
                        printf(" Bloque de ladrillo destruido por balas mejoradas\n");
                            } else {
                                proj->active = 0;
                            }
                        
                        
            
                        } else if (block_type == SPECIAL_BLOCK) {
                            printf("¡El proyectil tocó el bloque especial! GAME OVER\n");
                            *state = GAME_OVER;
                            *gameOverStartTime = SDL_GetTicks();
                            proj->active = 0;
                            return;
                        }
                    }
                }
            }
        }


        // Verificar colisión con los enemigos
        for (int i = 0; i < num_enemies; i++) {
            if (enemies[i].active && check_collision((game_element_t){proj->x, proj->y, proj->w, proj->h}, (game_element_t){enemies[i].x, enemies[i].y, enemies[i].w, enemies[i].h})) {
                printf("¡El proyectil tocó al enemigo!\n");
                proj->active = 0;
                if (enemies[i].texture == enemyTextures[1]) { // Verificar si es tank2.bmp
                    enemies[i].hitCount++;
                    if (enemies[i].hitCount >= 3) {
                        enemies[i].texture = enemyTextures[7]; // Cambiar la textura a tank7.bmp 
                    }
                    if (enemies[i].hitCount >= 4) {
                        enemies[i].active = 0; // Desactivar el enemigo después de 4 impactos
                        enemies_killed++; // Incrementar el contador de enemigos eliminados
                        draw_enemy_kill_count();
                        update_enemy_kill_count();
                         

                      
                    }
                } else {
                    enemies[i].active = 0; // Desactivar el enemigo
                    enemies_killed++; // Incrementar el contador de enemigos eliminados
                    draw_enemy_kill_count();
                    update_enemy_kill_count(); // Actualizar el contador de enemigos eliminados

                }
                break;
            }
        }
            //verificar colision entre projectiles 
            
        // Declare and initialize proj_enemy and proj_player
        projectile_t proj_enemy = {0, 0, 0, 0, 0, 0, 0};
        projectile_t proj_player = {proj->x, proj->y, proj->w, proj->h, proj->speedX, proj->speedY, proj->active};

        if(check_collision((game_element_t){proj_enemy.x, proj_enemy.y, proj_enemy.w, proj_enemy.h}, 
                           (game_element_t){proj_player.x, proj_player.y, proj_player.w, proj_player.h})){
            proj->active = 0;
            proj_player.active = 0;
        }





    }
}
///////////////////////////////////////////////////////////////////////////






void reset_tank_blocks() {
    for (int i = 0; i < MAX_TANK_BLOCKS; i++) {
        tank_blocks[i].active = 1; // Activar todos los bloques de tanques
        tank_blocks[i].x;
        tank_blocks[i].y;
    }
}









int main(int argc, char *args[]) {
    Uint32 enemystoptime = 0;
    Uint32 enemyRespawnTime = 0;
    Uint32 bombSpawnTime = 0;
    Uint32 gameOverStartTime = 0;
    Uint32 lastSpawnTime = 0; // Declarar lastSpawnTime
    int spawnIndex = 0; // Declarar spawnIndex
    int activeEnemies = 0; // Declarar activeEnemies


    int enemytime = 0;

    // Define the player and the maps
    game_element_t player = {200, 200};



    // For the project the elements of the map should be created
    // dinamically (using malloc) and using linked lists.
    game_element_t map_element;
 //   init_enemies();
    block_t blocks[NumBlocks]; // block_t es una estructura que guarda la posicion de los bloques

    // Inicialización del enemigo
    //moving_block_t enemy = {1600, 50, BLOCK_SIZE, BLOCK_SIZE, 2, 0, ENEMY_MOVING, 0, BLOCK_ENEMY};
   // moving_block_t enemy2 = {500, 50, BLOCK_SIZE, BLOCK_SIZE, 2, 0, ENEMY_MOVING, 0, BLOCK_ENEMY};
    // Inicialmente inactivo
    projectile_t projectile = {0, 0, 40, 40, 1, 1, 0};
   int original_map[MAP_HEIGHT][MAP_WIDTH];
    memcpy(original_map, map, sizeof(map));

    // Inicializar el mapa actual
    memcpy(current_map, map, sizeof(map));


    // SDL Window setup
  if (init_SDL(SCREEN_WIDTH, SCREEN_HEIGHT, argc, args) == FAILURE) {
      return FAILURE;
  }

  init_enemies();
  
  // Cargar texturas para enemigos: tank1.bmp, tank2.bmp, tank3.bmp
SDL_Texture* enemyTextures[8];
    init_enemies();


enemyTextures[0] = load_texture(renderer, "tank1.bmp");
enemyTextures[1] = load_texture(renderer, "tank2.bmp");
enemyTextures[2] = load_texture(renderer, "tank3.bmp");
enemyTextures[3] = load_texture(renderer, "tank4.bmp");
enemyTextures[4] = load_texture(renderer, "tank5.bmp");
enemyTextures[5] = load_texture(renderer, "tank6.bmp");
enemyTextures[6] = load_texture(renderer, "tank5v2.bmp");
enemyTextures[7] = load_texture(renderer, "tank2v2.bmp");

playerTextures[2] = load_texture(renderer, "tankPLAYER.bmp");


playerTextures[2] = load_texture(renderer, "tankPLAYER.bmp");
enemyTextures[7] = load_texture(renderer, "tank2v2.bmp");





SDL_Texture* spawnTextures[4];
spawnTextures[0] = load_texture(renderer, "SPAWN0.bmp");
spawnTextures[1] = load_texture(renderer, "SPAWN1.bmp");
spawnTextures[2] = load_texture(renderer, "SPAWN2.bmp");
spawnTextures[3] = load_texture(renderer, "SPAWN3.bmp");


SDL_Texture* shieldTextures[2];
shieldTextures[0] = load_texture(renderer, "escudo1.bmp");
shieldTextures[1] = load_texture(renderer, "escudo2.bmp");

// Cargar texturas de explosión
/*SDL_Texture* explosionTextures[4];
/*explosionTextures[0] = load_texture(renderer, "explosion0.bmp");
explosionTextures[1] = load_texture(renderer, "explosion1.bmp");
explosionTextures[2] = load_texture(renderer, "explosion2.bmp");
explosionTextures[3] = load_texture(renderer, "explosion3.bmp");
*/




    SDL_GetWindowSize(window, &g_width, &g_height);



    int sleep = 0;
    int quit = FALSE;
    int state = START_SCREEN;
    Uint32 next_game_tick = SDL_GetTicks();

    // Initialize the ball position data.
    init_game(&player, &map_element); // The & means "Address of"
    memcpy(current_map, map, sizeof(map)); // Inicialmente apuntamos a map

    // Inicializar el primer nivel
   // current_map = map; // Inicialmente apuntamos a map

    // constantes para poder guardar la posicion del jugador
    int Ultima_posicion_x = 10;
    int Ultima_posicion_y = 0;
    //draw_vidas(screen, 10, 10);

    // Estado del juego
   // Uint32 gameOverStartTime = 0; // Tiempo cuando ocurre pierde
    int playerLives = 3; // EL jugador posee tres vidas al iniciar





//iniciar animacion
spawn_animation_t spawn;
    spawn.x = 200;  // Posición X donde aparecerá el enemigo
    spawn.y = 200;  // Posición Y donde aparecerá el enemigo
    spawn.active = 1;
    spawn.StartTime = SDL_GetTicks();




    Uint32 scoreScreenStartTime = 0; // Para medir cuánto tiempo se muestra SCORE_SCREEN



    // render loop
    while (quit == FALSE) {
        // check for new events every frame
        SDL_Event event;


        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = TRUE;
            }
        }

        SDL_RenderClear(renderer);         // Clear the screen
        SDL_FillRect(screen, NULL, BLACK); // Fill the screen with black

        const Uint8 *keystate = SDL_GetKeyboardState(NULL);
        










        // Si estamos en LEVEL_1, podemos pausar con 'P'
        if (state == LEVEL_1 && keystate[SDL_SCANCODE_P]) {
            state = Pause_screen;
            next_game_tick = SDL_GetTicks();
            SDL_Delay(100); // Pequeño retardo para evitar múltiples cambios de estado
        }

        // Si estamos en PAUSE_SCREEN, revisamos si se quiere reanudar (por ejemplo, con 'R')
        if (state == Pause_screen) {
            if (keystate[SDL_SCANCODE_R]) {
                state = LEVEL_1;
                next_game_tick = SDL_GetTicks();
                SDL_Delay(200);
                continue;
            }
            draw_pause();
            SDL_UpdateTexture(screen_texture, NULL, screen->pixels, screen->w * sizeof(Uint32));
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, screen_texture, NULL, NULL);
            SDL_RenderPresent(renderer);
            SDL_Delay(200); // Reducir el uso de CPU en pausa
            continue; // Saltar el resto del loop
        }

        if (state == Pause_screen) {
            draw_pause();
            SDL_RenderPresent(renderer);
            SDL_Delay(200); // Reducir el uso de CPU mientras está en pausa
            continue;
        }

        

        if (keystate[SDL_SCANCODE_ESCAPE]) {
            quit = TRUE;
        }
        //agregamos condiciones para que no se mueva en horizintal el jugador
        if (keystate[SDL_SCANCODE_S] && !keystate[SDL_SCANCODE_A] && !keystate[SDL_SCANCODE_D]) {
            move_player(DOWN, &player, map_blocks, num_blocks, current_map, enemies, &helmetSpawnTime, &shieldStartTime, &shieldActive, shieldTextures);
            Ultima_posicion_x = 0;
            Ultima_posicion_y = 10;
        } else if (keystate[SDL_SCANCODE_W] && !keystate[SDL_SCANCODE_A] && !keystate[SDL_SCANCODE_D]) {
            move_player(UP, &player, map_blocks, num_blocks, current_map, enemies, &helmetSpawnTime, &shieldStartTime, &shieldActive, shieldTextures);
            Ultima_posicion_x = 0;
            Ultima_posicion_y = -10;
        } else if (keystate[SDL_SCANCODE_A] && !keystate[SDL_SCANCODE_W] && !keystate[SDL_SCANCODE_S]) {
            move_player(LEFT, &player, map_blocks, num_blocks, current_map, enemies, &helmetSpawnTime, &shieldStartTime, &shieldActive, shieldTextures);
            Ultima_posicion_x = -10;
            Ultima_posicion_y = 0;
        } else if (keystate[SDL_SCANCODE_D] && !keystate[SDL_SCANCODE_W] && !keystate[SDL_SCANCODE_S]) {
            move_player(RIGHT, &player, map_blocks, num_blocks, current_map, enemies, &helmetSpawnTime, &shieldStartTime, &shieldActive, shieldTextures);
            Ultima_posicion_x = 10;
            Ultima_posicion_y = 0;
        }





if (powerLevel >= 2){


   

    if (keystate[SDL_SCANCODE_SPACE]) {
            Uint32 currentTime = SDL_GetTicks(); // Obtener el tiempo actual
    
            if (projectile.active == 0) {
                projectile.active = 1;
                projectile.x = player.x + player.w / 2 - projectile.w / 2;
                projectile.y = player.y + player.h / 2 - projectile.h / 2;
                if (keystate[SDL_SCANCODE_W]) {
                    projectile.speedX = 0;
                    projectile.speedY = -10;
                } else if (keystate[SDL_SCANCODE_S]) {
                    projectile.speedX = 0;
                    projectile.speedY = 10;
                } else if (keystate[SDL_SCANCODE_A]) {
                    projectile.speedX = -10;
                    projectile.speedY = 0;
                } else if (keystate[SDL_SCANCODE_D]) {
                    projectile.speedX = 10;
                    projectile.speedY = 0;
                } else {
                    projectile.speedX = Ultima_posicion_x;
                    projectile.speedY = Ultima_posicion_y;
                }
                lastplayershoottime = currentTime; // Actualizar el tiempo del último disparo
            }
        
    } 
}


// Declarar la variable fuera del loop o como estática dentro de la función

else {


static int espacio_presionado = 0;  //la gracia fue el stac

if (keystate[SDL_SCANCODE_SPACE]) {
    if (!espacio_presionado) {  // Solo dispara si anteriormente no estaba presionada
        Uint32 currentTime = SDL_GetTicks(); // Obtener el tiempo actual

        if (projectile.active == 0) {
            projectile.active = 1;
            projectile.x = player.x + player.w / 2 - projectile.w / 2;
            projectile.y = player.y + player.h / 2 - projectile.h / 2;
            if (keystate[SDL_SCANCODE_W]) {
                projectile.speedX = 0;
                projectile.speedY = -10;
            } else if (keystate[SDL_SCANCODE_S]) {
                projectile.speedX = 0;
                projectile.speedY = 10;
            } else if (keystate[SDL_SCANCODE_A]) {
                projectile.speedX = -10;
                projectile.speedY = 0;
            } else if (keystate[SDL_SCANCODE_D]) {
                projectile.speedX = 10;
                projectile.speedY = 0;
            } else {
                projectile.speedX = Ultima_posicion_x;
                projectile.speedY = Ultima_posicion_y;
            }
            lastplayershoottime = currentTime; // Actualizar el tiempo del último disparo
        }
        espacio_presionado = 1; // Marcar que ya se presionó la tecla
    }
} else {
    espacio_presionado = 0; // Reiniciar el flag cuando la tecla se suelta
}


}


















if (keystate[SDL_SCANCODE_N] || enemies_killed / 2 >= 20) {
    // Cambiar de mapa
    if (current_level == 1) {
        enemies_killed = 0;
        for (int i = 0; i < MAX_ENEMIES; i++) {
            enemies[i].active = 0;
        }
        draw_score_screen();
       SDL_Delay(1000);
        draw_level_image(Nivel_2);
       SDL_Delay(200);

        memcpy(current_map, map2, sizeof(map2));
        current_level = 2;

    } else if (current_level == 2) {
        enemies_killed = 0;
        for (int i = 0; i < MAX_ENEMIES; i++) {
            enemies[i].active = 0;
        }
        draw_score_screen();
        SDL_Delay(1000);
        draw_level_image(Nivel_3);
        SDL_Delay(200);

        memcpy(current_map, map3, sizeof(map3));
        current_level = 3;
    } else if (current_level == 3) {
        enemies_killed = 0;
        for (int i = 0; i < MAX_ENEMIES; i++) {
            enemies[i].active = 0;
        }
        draw_score_screen();
        SDL_Delay(1000);
        draw_level_image(Nivel_4);
        SDL_Delay(200);

        memcpy(current_map, map4, sizeof(map4));
        current_level = 4;
    } else if (current_level == 4) {
        enemies_killed = 0;
        for (int i = 0; i < MAX_ENEMIES; i++) {
            enemies[i].active = 0;
        }
        draw_score_screen();
        SDL_Delay(1000);
        draw_level_image(Nivel_5);
        SDL_Delay(200);

        memcpy(current_map, map5, sizeof(map5));
        current_level = 5;
    } else {
        enemies_killed = 0;
        for (int i = 0; i < MAX_ENEMIES; i++) {
            enemies[i].active = 0;
        }
        draw_score_screen();
        SDL_Delay(2000);
        draw_menu();
        memcpy(current_map, map, sizeof(map));
        current_level = 1;
    }

    // Reiniciar powerLevel y sus efectos
    powerLevel = 0;
    bulletSpeedPlayer = PROJECTILE_SPEED_PLAYER;
    maxBullets = 1;
    bulletDestroySteel = 0;
    bulletDamageBrick = 1;

    reset_position(&player, enemies, &helmetSpawnTime, &shieldStartTime, &shieldActive, shieldTextures);
    reset_tank_blocks();
    // SDL_Delay(200); // Pequeño retardo para evitar múltiples cambios de nivel
}



      if (projectile.active == 1) {
        update_projectile(&projectile, map_blocks, num_blocks, current_map, &state, &gameOverStartTime, enemies, MAX_ENEMIES, enemyTextures);


    }


        if (projectile.active == 1) {
            projectile.x += projectile.speedX;
            projectile.y += projectile.speedY;
            if (projectile.x < 0 || projectile.x > screen->w || projectile.y < 0 || projectile.y > screen->h) {
                projectile.active = 0;
            }

            // Verificar colisiones con bloques de la matriz
            for (int y = 0; y < MAP_HEIGHT; y++) {
                for (int x = 0; x < MAP_WIDTH; x++) {
                    int block_type = current_map[y][x];
                    if (block_type == BLOCK_GREEN||block_type ==  BLOCK_BLUE) {
                        continue; // Ignorar bloques verdes
                    }
                 
                }
            }
            
        }


        // draw background
        SDL_RenderClear(renderer);
        SDL_FillRect(screen, NULL, BLACK);

        // Get the current time

    // display main menu
    if (state == START_SCREEN) {
        if (keystate[SDL_SCANCODE_RETURN]) {
          reset_game(&player, enemies, MAX_ENEMIES, current_map, &playerLives, &gameOverStartTime);
            state = LEVEL_1;
        }
        draw_menu();
        powerLevel = 0;
        bulletSpeedPlayer = PROJECTILE_SPEED_PLAYER;
        maxBullets = 1;
        bulletDestroySteel = 0;
        bulletDamageBrick = 1;
    
        reset_position(&player, enemies, &helmetSpawnTime, &shieldStartTime, &shieldActive, shieldTextures);
       // SDL_Delay(200); // Pequeño retardo para evitar múltiples cambios de nivel
        } 
        
        
 
    // Procesar según el estado del juego
    if (state == GAME_OVER) {
        draw_game_over();
        if (keystate[SDL_SCANCODE_RETURN]) {
            state = SCORE_SCREEN;
            scoreScreenStartTime = SDL_GetTicks(); // Inicializa el temporizador al cambiar de estado
            SDL_Delay(200); // Retardo para evitar múltiples entradas
        }
    } 
    else if (state == SCORE_SCREEN) {
        draw_score_screen();
        SDL_Delay(2000); // Retardo para evitar múltiples entradas

        if (SDL_GetTicks() - scoreScreenStartTime >= 2000) {
            memcpy(current_map, map, sizeof(map));
            reset_game(&player, enemies, MAX_ENEMIES, current_map, &playerLives, &gameOverStartTime);
            state = START_SCREEN;
            SDL_Delay(200); // Retardo para evitar múltiples cambios
        }
    }
    

        else if (state == LEVEL_1) {
         
            
        

            SDL_Rect testRect = {100, 100, BLOCK_SIZE, BLOCK_SIZE};
            SDL_RenderFillRect(renderer, &testRect);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
                    SDL_RenderClear(renderer);
            
            
            // Actualizar la posición del proyectil enemy
     
    

            // Dibujar bloques del mapa
            draw_game_element(&player);


            draw_maping_blocks(screen, current_map, BLOCK_SIZE, BLOCK_SIZE);
          
            // Dibujar el jugador
            // Dibujar otros elementos del juego
            draw_game_element(&map_element);
            //draw_block_like_type_surface(screen, enemy.x, enemy.y, BLOCK_ENEMY, enemy.w, enemy.h);
            draw_game_element_0_score(playerLives);
            draw_game_element_1_score(playerLives);



            draw_map_blocks(screen, map_blocks, num_blocks);
            //draw_projectile(renderer, &projectile);
            // Dibujar bloques de tipo vida y tanque
            
       
    // Dibujar bloques del mapa
    draw_game_element(&player);

draw_maping_blocks(screen, current_map, BLOCK_SIZE, BLOCK_SIZE);
// Dibujar el jugador
// Dibujar otros elementos del juego
draw_game_element(&map_element);
//draw_block_like_type_surface(screen, enemy.x, enemy.y, BLOCK_ENEMY, enemy.w, enemy.h);
draw_game_element_0_score(playerLives);
draw_game_element_1_score(playerLives);
draw_map_blocks(screen, map_blocks, num_blocks);
draw_projectile(renderer, &projectile);

draw_number(screen, enemies_killed/2, screen->w - 1800, 0);
draw_block_like_type_surface(screen, 1800, 600, vidas_texture_BLOCK, BLOCK_SIZE, BLOCK_SIZE, map_blocks, num_blocks);

  ///SI CUENTA LOS PUNTOS
  //draw_enemy_kill_count(screen, enemies_killed, 4);

  for (int i = 0; i < MAX_TANK_BLOCKS; i++) {
    if (tank_blocks[i].active) {
        draw_block_like_type_surface(screen, tank_blocks[i].x, tank_blocks[i].y, tanques_texture_BLOCK, BLOCK_SIZE, BLOCK_SIZE, map_blocks, num_blocks);
    }
}

        }

        Uint32 currentTime = SDL_GetTicks();
      


if (activeEnemies < 4 && currentTime - lastSpawnTime >= ENEMY_SPAWN_INTERVAL) {
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (!enemies[i].active) {
            int spawnX = spawn_points[spawnIndex].x;
            int spawnY = spawn_points[spawnIndex].y;
          //  activate_spawn_animation(spawnX, spawnY);

            // Incrementar el índice de spawn y volver a 0 si alcanza NUM_SPAW_POINTS
            spawnIndex = (spawnIndex + 1) % NUM_SPAW_POINTS;
            lastSpawnTime = currentTime;
            break;
        }
    }
}

         draw_enemies(renderer, balasCongeladas, enemigosCongelados);

      
      
///////////PODERES///////PODERES////////////////PODERES//////////////PODERES///////////////////////
      BLOCK_BOMB(&player, enemies, MAX_ENEMIES, current_map, &bombSpawnTime, &enemyRespawnTime);
      BLOCK_HELMET(&player, current_map, &helmetSpawnTime, &shieldStartTime, &shieldActive, shieldTextures);
      tanque_poder(&player, current_map, &tanquePoderSpawnTime, &playerLives);
      bloque_temporizador(&player, enemies, MAX_ENEMIES, bullets, MAX_BULLETS, current_map, 
        &temporizadorSpawnTime, &tiempoCongelacion, &enemigosCongelados, &balasCongeladas, &disparoBloqueado);    
      BLOCK_PALA(&player, current_map);
      BLOCK_STAR(&player, current_map); 

      update_enemies(currentTime, enemyTextures, map_blocks, num_blocks, screen, &player, &state, &gameOverStartTime, &playerLives, current_map);
// En el bucle principal del juego
for (int i = 0; i < MAX_ENEMIES; i++) {
    if (enemies[i].spawning) {
        draw_spawn_animation(&enemies[i].spawn_animation, spawnTextures);
      //  SDL_Delay(100);
    }
}



      SDL_UpdateTexture(screen_texture, NULL, screen->pixels, screen->w * sizeof(Uint32));
      SDL_RenderCopy(renderer, screen_texture, NULL, NULL);

      // draw to the display
      SDL_RenderPresent(renderer);

      // time it takes to render frame in milliseconds
      next_game_tick += FRAME_TIME_MS;
      sleep = next_game_tick - SDL_GetTicks();

      if (sleep >= 0) {
          SDL_Delay(sleep);
      }
  }

    // free loaded images
    SDL_FreeSurface(screen);
    SDL_FreeSurface(title);
    SDL_FreeSurface(numbermap);
    SDL_FreeSurface(end);
    SDL_FreeSurface(special_block_image);
    SDL_FreeSurface(brick_texture);
    SDL_FreeSurface(Hierro_texture);
    SDL_FreeSurface(Grass_texture);
    SDL_FreeSurface(Water_texture);
    SDL_FreeSurface(tank_texture);
    SDL_FreeSurface(bomb_texture);
    SDL_FreeSurface(helmet_texture);
    SDL_FreeSurface(tanquePoder_texture);
    SDL_FreeSurface(temporizadorPoder_texture);
    
    SDL_FreeSurface(pala_texture);
    SDL_FreeSurface(star_texture);

    SDL_FreeSurface(vidas_texture);
    SDL_FreeSurface(tanques_texture);
    SDL_FreeSurface(brick_texture_Y_plus);
    SDL_FreeSurface(brick_texture_X_minus);
    SDL_FreeSurface(brick_texture_Y_minus);
    SDL_FreeSurface(brick_texture_X_plus);
   SDL_FreeSurface(spawn0_animation);
    SDL_FreeSurface(spawn1_animation);
    SDL_FreeSurface(spawn2_animation);
    SDL_FreeSurface(spawn3_animation);
    SDL_FreeSurface(Nivel_2);
    SDL_FreeSurface(Nivel_3);
    SDL_FreeSurface(Nivel_4);
    SDL_FreeSurface(Nivel_5);

    // free renderer and all textures used with it
    SDL_DestroyRenderer(renderer);

    // Destroy window
    SDL_DestroyWindow(window);

    // Quit SDL subsystems
    SDL_Quit();

    return SUCCESS;
}

/* Function: init_SDL
 * ----------------------------
 * This function initialises the required environment for SDL
 * to work.
 *
 * Arguments:
 *	width: The width of the screen.
 * 	height: The height of the screen.
 *	argc: The same parameter from the main function.
 *	args: The same parameter from the main function.
 *
 * Return:
 *	SUCCESS if no problem reported.
 *	FAILURE if any initialization failed
 */






 SDL_Texture* load_texture(SDL_Renderer* renderer, const char* filename) {
  SDL_Surface* tempSurface = SDL_LoadBMP(filename);
  if (tempSurface == NULL) {
      printf("Error al cargar %s: %s\n", filename, SDL_GetError());
      return NULL;
  }
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
  SDL_FreeSurface(tempSurface);
  return texture;
}
int init_SDL(int width, int height, int argc, char *args[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return FAILURE;
    }

    // Create window
    window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return FAILURE;
    }

    // Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return FAILURE;
    }

    // Create the screen surface where all the elements will be drawn
    screen = SDL_CreateRGBSurfaceWithFormat(0, width, height, 32, SDL_PIXELFORMAT_RGBA32);
    if (screen == NULL) {
        printf("Could not create the screen surface! SDL_Error: %s\n", SDL_GetError());
        return FAILURE;
    }

    // Create the screen texture to render the screen surface to the actual display
    screen_texture = SDL_CreateTextureFromSurface(renderer, screen);
    if (screen_texture == NULL) {
        printf("Could not create the screen texture! SDL_Error: %s\n", SDL_GetError());
        return FAILURE;
    }

    // Load the title image
    title = SDL_LoadBMP("title.bmp");
    if (title == NULL) {
        printf("Could not load title image! SDL_Error: %s\n", SDL_GetError());
        return FAILURE;
    }

    // Load the numbermap image
    numbermap = SDL_LoadBMP("numbermap.bmp");
    if (numbermap == NULL) {
        printf("Could not load numbermap image! SDL_Error: %s\n", SDL_GetError());
        return FAILURE;
    }

    // Load the gameover image
    end = SDL_LoadBMP("gameover.bmp");
    if (end == NULL) {
        printf("Could not load gameover image! SDL_Error: %s\n", SDL_GetError());
        return FAILURE;
    }

    // Load other textures
    special_block_image = SDL_LoadBMP("special_block.bmp");
    if (special_block_image == NULL) {
        printf("Error al cargar special_block.bmp: %s\n", SDL_GetError());
        return FAILURE;
    }

    brick_texture = SDL_LoadBMP("brickTx.bmp");
    if (brick_texture == NULL) {
        printf("Error al cargar brickTx.bmp: %s\n", SDL_GetError());
        return FAILURE;
    }

    Hierro_texture = SDL_LoadBMP("hierro.bmp");
    if (Hierro_texture == NULL) {
        printf("Error al cargar Hierro.bmp: %s\n", SDL_GetError());
        return FAILURE;
    }

    Grass_texture = SDL_LoadBMP("pasto.bmp");
    if (Grass_texture == NULL) {
        printf("Error al cargar Grass.bmp: %s\n", SDL_GetError());
        return FAILURE;
    }

    Water_texture = SDL_LoadBMP("Agua.bmp");
    if (Water_texture == NULL) {
        printf("Error al cargar agua.bmp: %s\n", SDL_GetError());
        return FAILURE;
    }

    tank_texture = SDL_LoadBMP("tank1.bmp");
    if (tank_texture == NULL) {
        printf("Error al cargar tank1.bmp: %s\n", SDL_GetError());
        return FAILURE;
    }

    Nivel_2 = SDL_LoadBMP("Nivel-2.bmp");
    if (Nivel_2 == NULL) {
        printf("Error al cargar Nivel-2.bmp: %s\n", SDL_GetError());
        return FAILURE;
    }

    Nivel_3 = SDL_LoadBMP("Nivel-3.bmp");
    if (Nivel_3 == NULL) {
        printf("Error al cargar Nivel-3.bmp: %s\n", SDL_GetError());
        return FAILURE;
    }

    Nivel_4 = SDL_LoadBMP("Nivel-4.bmp");
    if (Nivel_4 == NULL) {
        printf("Error al cargar Nivel-4.bmp: %s\n", SDL_GetError());
        return FAILURE;
    }

    Nivel_5 = SDL_LoadBMP("Nivel-5.bmp");
    if (Nivel_5 == NULL) {
        printf("Error al cargar Nivel-5.bmp: %s\n", SDL_GetError());
        return FAILURE;
    }
    bomb_texture = SDL_LoadBMP("bomb_texture.bmp"); // Cargar la imagen de la bomba 
    if ( bomb_texture == NULL) {
        printf("Error al cargar bomb_texture: %s\n", SDL_GetError());
            return FAILURE;
        } else {
            printf("✅ Imagen bomb_texture.bmp cargada correctamente.\n");
        }

    helmet_texture = SDL_LoadBMP("helmet_texture.bmp"); // Cargar la imagen de la bomba 
        if ( helmet_texture == NULL) {
            printf("Error al cargar helmet_texture: %s\n", SDL_GetError());
                return FAILURE;
            } else {
                printf("✅ Imagen helmet_texture.bmp cargada correctamente.\n");
         }

    tanquePoder_texture = SDL_LoadBMP("tanquePoder_texture.bmp"); // Cargar la imagen de la bomba 
         if ( tanquePoder_texture == NULL) {
             printf("Error al cargar tanquePoder_texture: %s\n", SDL_GetError());
                 return FAILURE;
             } else {
                 printf("✅ Imagen tanquePoder_texture.bmp cargada correctamente.\n");
             }

    temporizadorPoder_texture = SDL_LoadBMP("temporizadorPoder_texture.bmp"); // Cargar la imagen de la bomba 
        if ( temporizadorPoder_texture == NULL) {
           printf("Error al cargar temporizadorPoder_texture: %s\n", SDL_GetError());
                     return FAILURE;
                   } else {
                       printf("✅ Imagen temporizadorPoder_texture.bmp cargada correctamente.\n");
                   } 

       
    pala_texture = SDL_LoadBMP("pala_texture.bmp"); // Cargar la imagen de la pala 
    if ( pala_texture == NULL) {
       printf("Error al cargar pala_texture: %s\n", SDL_GetError());
                   return FAILURE;
     } else {
         printf("✅ Imagen pala_texture.bmp cargada correctamente.\n");
             }

     star_texture = SDL_LoadBMP("star_texture.bmp"); // Cargar la imagen de la estrella
    if ( star_texture == NULL) {
         printf("Error al cargar star_texture: %s\n", SDL_GetError());
                return FAILURE;
     } else {
         printf("✅ Imagen star_texture.bmp cargada correctamente.\n");
                }









                vidas_texture = SDL_LoadBMP("Vidas.bmp");
                if (vidas_texture == NULL) {
                    printf("Error al cargar Vidas.bmp: %s\n", SDL_GetError());
                    return FAILURE;
                } else {
                    printf("✅ Imagen Vidas.bmp cargada correctamente.\n");
                }
                
                tanques_texture = SDL_LoadBMP("tanques.bmp");
                if (tanques_texture == NULL) {
                    printf("Error al cargar tanques.bmp: %s\n", SDL_GetError());
                    return FAILURE;
                } else {
                    printf("✅ Imagen tanques.bmp cargada correctamente.\n");
                }


                playerTextures[0] = load_texture(renderer, "tankPLAYER.bmp");
                if (playerTextures[0] == NULL) {
                    printf("Error al cargar tankPLAYER.bmp: %s\n", SDL_GetError());
                    return FAILURE;
                } else {
                    printf("✅ Imagen tankPLAYER.bmp cargada correctamente.\n");
                }
            
                // Load the shield textures
                playerTextures[1] = load_texture(renderer, "escudo1.bmp");
                if (playerTextures[1] == NULL) {
                    printf("Error al cargar escudo1.bmp: %s\n", SDL_GetError());
                    return FAILURE;
                }
                playerTextures[2] = load_texture(renderer, "escudo2.bmp");
                if (playerTextures[2] == NULL) {
                    printf("Error al cargar escudo2.bmp: %s\n", SDL_GetError());
                   

                }




brick_texture_X_plus = SDL_LoadBMP("brickTx2X+aaa.bmp");
if (brick_texture_X_plus == NULL) {
    printf("Error al cargar brickTx2X+.bmp: %s\n", SDL_GetError());
    return FAILURE;
}

brick_texture_X_minus = SDL_LoadBMP("brickTx2X-.bmp");
if (brick_texture_X_minus == NULL) {
    printf("Error al cargar brickTx2X-.bmp: %s\n", SDL_GetError());
    return FAILURE;
}

brick_texture_Y_plus = SDL_LoadBMP("brickTx2y+.bmp");
if (brick_texture_Y_plus == NULL) {
    printf("Error al cargar brickTx2y+.bmp: %s\n", SDL_GetError());
    return FAILURE;
}

brick_texture_Y_minus = SDL_LoadBMP("brickTx2y-.bmp");
if (brick_texture_Y_minus == NULL) {
    printf("Error al cargar brickTx2y-.bmp: %s\n", SDL_GetError());
    return FAILURE;
}

spawn0_animation = SDL_LoadBMP("SPAWN0.bmp");
if (spawn0_animation == NULL) {
    printf("Error al cargar SPAWN0.bmp: %s\n", SDL_GetError());
    return FAILURE;
}   
spawn1_animation = SDL_LoadBMP("SPAWN1.bmp");
if (spawn1_animation == NULL) {
    printf("Error al cargar SPAWN1.bmp: %s\n", SDL_GetError());
    return FAILURE;
}
spawn2_animation = SDL_LoadBMP("SPAWN2.bmp");
if (spawn2_animation == NULL) {
    printf("Error al cargar SPAWN2.bmp: %s\n", SDL_GetError());
    return FAILURE;
}
spawn3_animation = SDL_LoadBMP("SPAWN3.bmp");
if (spawn3_animation == NULL) {
    printf("Error al cargar SPAWN3.bmp: %s\n", SDL_GetError());
    return FAILURE;
}

    // Set the title colourkey
    Uint32 colorkey = SDL_MapRGB(title->format, 255, 0, 255);
    SDL_SetColorKey(title, SDL_TRUE, colorkey);
    SDL_SetColorKey(numbermap, SDL_TRUE, colorkey);

    return SUCCESS;
}
