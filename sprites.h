
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

// function declarations:
void createEnemySprite(int i, int j, sprite_t* enemy, void* next);
void createPlayerSprite(sprite_pl* player);
void createShotSprite(sprite_shot* shot);


#endif
