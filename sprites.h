
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

// function declarations:
void createEnemySprite(int i, int j, sprite_t* enemy, void* next);
void createPlayerSprite(sprite_pl* player);
void createShotSprite(sprite_shot* shot);
void createBunkerSprite(sprite_bunker* bunker, unsigned char * data);

unsigned char bunker_template[] = 
    { 
        0x05, 0xA0, 0x1F, 0xE0, 0x00,
        0x05, 0xA0, 0x7F, 0xF8, 0x00,
        0x05, 0xA1, 0xFF, 0xFE, 0x00,
        0x05, 0xA7, 0xFF, 0xFF, 0x80,
        0x05, 0xA7, 0xFF, 0xFF, 0x80,
        0x05, 0xA7, 0xE0, 0x1F, 0x80,
        0x00 
    };

// unsigned char bunker_template[] = 
//     { 
//         0xA0, 0x1F, 0xE0, 0x00,
//         0xA0, 0x7F, 0xF8, 0x00,
//         0xA1, 0xFF, 0xFE, 0x00,
//         0xA7, 0xFF, 0xFF, 0x80,
//         0xA7, 0xFF, 0xFF, 0x80,
//         0xA7, 0xE0, 0x1F, 0x80,
//         0x00 
//     };

// 1 0000 1111 000 0000
// 1 0000 0001 000 0000
// 1 0001 0001 000 0000
// 1 0010 0001 000 0000
unsigned char sprite_test_data[] = 
    { 
        0x03, 0x87, 0x80,
        0x03, 0x80, 0x80, 
        0x03, 0x88, 0x80, 
        0x03, 0x90, 0x80, 
        0x00
    };

//unsigned char singlepixel_data[] = { 0x03, 0x87, 0x80, 0x00 }; // 1 0000 111 1 0000 000

// 1 0001 1111 000 0000
// unsigned char two_pixel_data[] = 
//     { 
//         0x03, 0x8F, 0x80,
//         0x00
//     };

// 1 0011 1111 000 0000
unsigned char sprite_test_data2[] = 
    { 
        0x03, 0x8F, 0x80,
        0x03, 0x9F, 0x80,
        0x00
    };

unsigned char sprite_0_0[] = {
	0x3,   0xf9, 0xff, 
	0x3,   0xff, 0xff, 
  0x00
	};

// 0000 0011 1111 1100 0000
// 0000 1111 1111 1111 0000
// 0011 1111 1111 1111 1100
// 1111 1111 1111 1111 1111
// 1111 1111 1111 1111 1111
// 1111 1100 0000 0011 1111

unsigned char one_more_bunker_test[] = {
	0x04, 0x03, 0xfc, 0x00,
	0x04, 0x0f, 0xff, 0x00,
  0x04, 0x3f, 0xff, 0xc0,
  0x04, 0xff, 0xff, 0xf0,
  0x04, 0xff, 0xff, 0xf0,
  0x04, 0xfc, 0x03, 0xf0,
  0x00
	};

#endif
