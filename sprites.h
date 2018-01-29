#include <lynx.h>
#include <tgi.h>
#include <_suzy.h>

unsigned char singlepixel_data[] = { 0x03, 0x87, 0x80, 0x00 }; // 1 0000 111 1 0000 000 

typedef struct {
  char collindex;   // collision index
  SCB_REHV sprite;  // sprite structure with position and size, without stretch and tilt (from _suzy.h)
  PENPAL_1;   // pallete structure for 1-bit color pallete (1 color and background) (from _suzy.h)
  int initx, inity; // initial position in the grid of ships
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

