

#ifndef _CONSTANTS
#define _CONSTANTS
// chosen project-specific prefix for constants: SINV

// constants present somewhere in TGI: getxres, getyres functions
// screen_width = 160
// screen_height = 102

// general graphic constants:
#define NUMSHIPSX 10
#define NUMSHIPSY 6

#define SINV_NUMSHIPSX 10
#define SINV_NUMSHIPSY 6
#define SINV_SHIPGAPX 3
#define SINV_SHIPGAPY 2
#define SHIPWIDTH 8
#define SHIPHEIGHT 6

// player constants
#define PLAYER_YPOS 85
#define PLAYER_HSPEED 2
#define PLAYER_SPRITE_WIDTH 16
#define PLAYER_SPRITE_HEIGHT 6

// ship movement - constants
#define SHIP_MOVE_MARGIN 5 	// how close to the screen border will ships switch direction
#define SHIP_MOVE_XSTEP 4		// ship move horizontally - pixels
#define SHIP_MOVE_YSTEP 2		// ship move vertically - pixels

// shot constants 
#define SHOT_VERT_SPEED 5
#define SHOT_SPRITE_HEIGHT 4

// bunker constants
#define BUNKER_CNT 4
#define BUNKER_DATA_LEN 31
#define BUNKER_YPOS 75
#define BUNKER_LEFT_OFFSET 15
#define BUNKER_GAP 36

// bomb constants
#define BOMB_SPRITE_HEIGHT 3
#define BOMB_VERT_SPEED 5


#endif
