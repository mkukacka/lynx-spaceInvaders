
#ifndef _SPRITES
#define _SPRITES

#include <lynx.h>
#include <tgi.h>
#include <_suzy.h>

#include "consts.h"

typedef struct {
  char collindex;   // collision index
  SCB_REHV sprite;  // sprite structure with position and size, without stretch and tilt (from _suzy.h)
  PENPAL_1;   // pallete structure for 1-bit color pallete (1 color and background) (from _suzy.h)
  int initx, inity; // initial position in the grid of ships
  char alive;
} sprite_t;

typedef struct {
  char collindex;   // collision index
  SCB_REHV sprite;  // sprite structure with position and size, without stretch and tilt (from _suzy.h)
  PENPAL_1;   // pallete structure for 1-bit color pallete (1 color and background) (from _suzy.h)
} sprite_pl;

typedef struct {
  char collindex;   // collision index
  SCB_REHV sprite;  // sprite structure with position and size, without stretch and tilt (from _suzy.h)
  PENPAL_1;   // pallete structure for 1-bit color pallete (1 color and background) (from _suzy.h)
} sprite_shot;

typedef struct {
  char collindex;   // collision index
  SCB_REHV sprite;  // sprite structure with position and size, without stretch and tilt (from _suzy.h)
  PENPAL_1;   // pallete structure for 1-bit color pallete (1 color and background) (from _suzy.h)
} sprite_bunker;

typedef struct {
  char collindex;   // collision index
  SCB_REHV sprite;  // sprite structure with position and size, without stretch and tilt (from _suzy.h)
  PENPAL_1;   // pallete structure for 1-bit color pallete (1 color and background) (from _suzy.h)
} sprite_bomb;

// function declarations:
void createEnemySprite(int i, int j, sprite_t* enemy, void* next);
void createPlayerSprite(sprite_pl* player);
void createShotSprite(sprite_shot* shot);
void createBunkerSprite(sprite_bunker* bunker, unsigned char * data);
void createBombSprite(sprite_shot* shot);


// bunker template data:
// 0000 0011 1111 1100 0000
// 0000 1111 1111 1111 0000
// 0011 1111 1111 1111 1100
// 1111 1111 1111 1111 1111
// 1111 1111 1111 1111 1111
// 1111 1100 0000 0011 1111

unsigned char bunker_template[] = {
	0x04, 0x03, 0xfc, 0x00,
	0x04, 0x0f, 0xff, 0x00,
  0x04, 0x3f, 0xff, 0xc0,
  0x04, 0xff, 0xff, 0xf0,
  0x04, 0xff, 0xff, 0xf0,
  0x04, 0xfc, 0x03, 0xf0,
  0x00
	};

#endif
