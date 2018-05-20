#include <lynx.h>
#include <tgi.h>
#include <_suzy.h>

unsigned char singlepixel_data[] = { 0x03, 0x87, 0x80, 0x00 }; // 1 0000 111 1 0000 000 
// this is more like:       1 0000 1111 000 0000
// reorganized into bytes:  1000 0111 1000 0000 plus the ending byte for end-of-sprite
// this means:
// 1. bit - literal=1, packed=0, here: literal sprite
// next 4 bits (0000) - number of pixels + 1 - here: 0 + 1 = 1
// next 1,2,3,4 bits - pixel data - here: 1111 = F = white color in 16-color pallete
// padding to byte length: 000 0000

// the 0x03 is the offset to the next line of sprite - here the line of sprite is the first 
//   three bytes (0x03, 0x87, 0x80), so the offset points to 0x00, which denotes end of sprite
// for explanation: see Handy Specification.tif, page 25

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

