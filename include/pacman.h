#ifndef PACMAN_H
#define PACMAN_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h> 
#include "rank.h"

#define WINDOW_WIDTH 464
#define WINDOW_HEIGHT 600

#define MAP_ROWS 31
#define MAP_COLS 29
#define TILE_WIN_SIZE 16 
#define TILE_SPR_SIZE 8

#define MAP_OFFSET_Y 52

#define TOTAL_DOTS 244
#define HUNTER_MODE_DURATION_MS 10000
#define HUNTER_WARNING_TIME_MS 3000
#define HUNTER_SCORE_MULTIPLIER 200

#define TARGET_FPS 60
#define DELTA_TICK_MS (1000 / TARGET_FPS)

const char pacman_map[MAP_ROWS][MAP_COLS] = {
"############################",
"#............##............#",
"#.####.#####.##.#####.####.#",
"#o#  #.#   #.##.#   #.#  #o#",
"#.####.#####.##.#####.####.#",
"#..........................#",
"#.####.##.########.##.####.#",
"#.####.##.########.##.####.#",
"#......##....##....##......#",
"######.##### ## #####.######",
"######.##### ## #####.######",
"######.##          ##.######",
"######.## ###  ### ##.######",
"######.## ##    ## ##.######",
"      .   ########   .      ",
"######.## ######## ##.######",
"######.## ######## ##.######",
"######.##          ##.######",
"######.## ######## ##.######",
"######.## ######## ##.######",
"#............##............#",
"#.####.#####.##.#####.####.#",
"#.####.#####.##.#####.####.#",
"#o..##.......  .......##..o#",
"###.##.##.########.##.##.###",
"###.##.##.########.##.##.###",
"#......##....##....##......#",
"#.##########.##.##########.#",
"#.##########.##.##########.#",
"#..........................#",
"############################"
};

typedef enum {
  // Pacman animado
  SPR_PACMAN_UP_1,
  SPR_PACMAN_UP_2,
  SPR_PACMAN_LEFT_1,
  SPR_PACMAN_LEFT_2,
  SPR_PACMAN_DOWN_1,
  SPR_PACMAN_DOWN_2,
  SPR_PACMAN_RIGHT_1,
  SPR_PACMAN_RIGHT_2,
  
  SPR_PACMAN_LOST_1,

  // Fantasmas animados
  SPR_GHOST_BLINKY_1,
  SPR_GHOST_BLINKY_2,
  SPR_GHOST_PINKY_1,
  SPR_GHOST_PINKY_2,
  SPR_GHOST_INKY_1,
  SPR_GHOST_INKY_2,
  SPR_GHOST_CLYDE_1,
  SPR_GHOST_CLYDE_2,

  // Ojos de fantasmas por dirección
  SPR_GHOST_EYES_RIGHT,
  SPR_GHOST_EYES_LEFT,
  SPR_GHOST_EYES_DOWN,
  SPR_GHOST_EYES_UP,

  //ghosts turn white when the "blue" vulnerable state is about to expire
  SPR_GHOST_SCARY_BLUE_1,
  SPR_GHOST_SCARY_BLUE_2,
  SPR_GHOST_SCARY_WHITE_1,
  SPR_GHOST_SCARY_WHITE_2,

  //Rewards
  SPR_REWARD_1,
  SPR_REWARD_2,
  SPR_REWARD_3,
  SPR_REWARD_4,
  SPR_REWARD_5,
  SPR_REWARD_6,
  SPR_REWARD_7,
  SPR_REWARD_8,

  // Tiles del mapa
  SPR_DOT,                // .
  SPR_ORB,                // o

  SPR_EMPTY,
  SPR_NULL
} SpriteID;

const SDL_Rect spriteClips[37] = {
  // Pacman
  {456, 32, 16, 16},  {472, 32, 16, 16},    // up
  {456, 16, 16, 16}, {472, 16, 16, 16},   // left
  {456, 48, 16, 16},  {472, 48, 16, 16},    // down
  {456, 0, 16, 16}, {472, 0, 16, 16},   // right
  {504,0,16,16}, // Pacman lose start

  // Ghosts
  {456, 64, 16, 16},   {472, 64, 16, 16},   // Red
  {456, 80, 16, 16}, {472, 80, 16, 16},   // Pink
  {456, 96, 16, 16}, {472, 96, 16, 16},   // Light Blue
  {456, 112, 16, 16}, {472, 112, 16, 16},   // Orange

  // eyes , these are render alone 
   {584, 80, 16, 16},
   {600, 80, 16, 16},
  {632, 80, 16, 16},
   {616, 80, 16, 16},

  // Scary pacmans.
{584, 64, 16, 16},
{600, 64, 16, 16},
{616, 64, 16, 16},
{632, 64, 16, 16},

    //Rewards
{504,48,16,16},
{520,48,16,16},
{536,48,16,16},
{552,48,16,16},
{568,48,16,16},
{584,48,16,16},
{600,48,16,16},
{616,48,16,16},

  // Points
  {8, 8, 8, 8},     // '.'
  {8, 24, 8, 8},    // 'o'

{0,88, 8, 8},   // Empty ' '
{0,0,0,0}   // NULL
};

const SDL_Color colors[3] ={
  {255,255,255,255},
  {0,0,0,255},
  {150, 150, 150, 255},
};

typedef enum {WHITE,BLACK,GREY} FontColor;

typedef enum {STANDARD,SMALL} FontSize;
const uint8_t fontSizes[2] = {24,12}; 

typedef struct {
  SDL_Rect dst;
  char *text;
  SDL_Texture *texture;
  bool needsUpdate;
} TextLabel;

typedef struct {
  SDL_Rect dst;
  SDL_Texture *img;
} SpriteImage;


// ------------ DIRECTIONS -----------
typedef enum { DIR_UP, DIR_LEFT, DIR_DOWN, DIR_RIGHT, DIR_COUNT } Direction;
const int8_t directionOffsets[4][2] = {
  {-1, 0}, {0, -1}, {1, 0}, {0, 1}
};
// ---- GAME ----
typedef enum {
  STATE_MENU,
  STATE_PLAYING,
  STATE_HELP,
  STATE_PAUSED,
  STATE_GAME_OVER,
  STATE_GAME_COMPLETE,
  STATE_START_LEVEL,
  STATE_LIFE_LOST,
  STATE_RANKING,
  STATE_ENTER_NAME
} GameState;

typedef enum {
  TYPE_PACMAN,
  TYPE_BLINKY,
  TYPE_PINKY,
  TYPE_INKY,
  TYPE_CLYDE
} EntityKind;

typedef struct {
  EntityKind kind;
  Direction dir;
  u_int16_t moveTimer;
  int8_t row, col;
  bool scared;
} GameEntity;

#define PACMAN_START_ROW 23
#define PACMAN_START_COL 14
#define BASE_TICKS 100

typedef struct {
  TextLabel playerName;
  GameEntity pacman;
  uint16_t score;
  int16_t hunterTime;  
  int8_t lives;
  uint8_t dotsEaten;
  uint8_t rewardCount;
  uint8_t ghostCombo;
} PlayerData;

#define GHOST_HOME 14 // Row and Col are equals
#define GHOST_FRIGHTENED_TICKS 150 // 150% OF BASE TICKS 

/*Speeds: based in pacman base ticks
Blinky: 75% ; Pinky: 65% ; Inky: 55% ; Clyde : 45%
*/
const uint8_t ghostBaseTicks[4] = {
    (uint8_t)(BASE_TICKS*1.25), 
    (uint8_t)(BASE_TICKS*1.35),
    (uint8_t)(BASE_TICKS*1.45),
    (uint8_t)(BASE_TICKS*1.55)
};

typedef struct {
  char map[MAP_ROWS][MAP_COLS];
  ScoreBoard board;
  PlayerData player;
  GameEntity ghosts[4];
  GameState state, prevState;
} GameLogic;

typedef struct {
  uint32_t lastTicks;
  uint32_t startPauseTicks;
  int32_t accumulator;
} GameClock;

typedef struct {
  Mix_Chunk *eatDot;
  Mix_Chunk *eatGhost;
  Mix_Chunk *death;
  Mix_Chunk *start;
  Mix_Chunk *move;
  Mix_Chunk *win;
  uint16_t dotTimer,moveTimer;
} GameSounds;

typedef struct {
  TextLabel play, help, rank, exit, credit;
  SpriteImage title;
} MenuLayout;

typedef struct {
  SDL_Texture *helpImg;
  int32_t textW,textH;
} HelpLayout;

typedef struct {
  TextLabel score, lives, ready;
  SpriteImage pause;
  SpriteImage gameOver;
  SpriteImage gameWin;
} GameOverlay;

typedef struct {
  TextLabel hint, names, scores;
  SpriteImage rankingImg;
} ScoreboardLayout;

typedef struct {
  MenuLayout menu;
  GameOverlay overlay;
  ScoreboardLayout scoreboard;
  HelpLayout help;
} UILayout;

typedef struct {
  GameLogic game;
  UILayout ui;
  SDL_Event event;
  GameSounds sounds;
  GameClock timer;
  
  SDL_Window *window;
  SDL_Renderer *renderer;
  TTF_Font *font;
  SDL_Texture *spritesheet;

  bool isRunning;
} AppContext;

void init_game_application(AppContext *app);
void quit_game_application(AppContext *app);
void handle_events(AppContext *app);
void render(AppContext *app); 
void update_game(AppContext *app);  // -> move ghosts , pacman and checks colisions


#endif