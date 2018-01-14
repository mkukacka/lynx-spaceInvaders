#include <lynx.h>
#include <tgi.h>
#include <_suzy.h>

unsigned char singlepixel_data[] = { 0x03, 0x87, 0x80, 0x00 }; // 1 0000 111 1 0000 000 

typedef struct {
  char collindex;   // collision index
  SCB_REHV sprite;  // sprite structure with position and size, without stretch and tilt (from _suzy.h)
  PENPAL_1;         // pallete structure for 1-bit color pallete (1 color and background) (from _suzy.h)
} sprite_t;

sprite_t ship1 = {
  0,
  {
    BPP_1 | TYPE_NORMAL,
    REHV,
    1,  // collision number
    0,
    singlepixel_data,
    50, 
    60, 
    0x0500, 
    0x0500
  },
  {COLOR_GREEN}
};