

#include "sprites.h"

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

// BUNKERS:
// how should the bunker look like, half size: 
// ...XXXX...
// .XXXXXXXX.
// XXXXXXXXXX
// XXX....XXX

// so in bits (20 pixels, 6 rows):
// 0000 0011 1111 1100 0000
// 0000 1111 1111 1111 0000
// 0011 1111 1111 1111 1100
// 1111 1111 1111 1111 1111
// 1111 1111 1111 1111 1111
// 1111 1100 0000 0011 1111


void createBunkerSprite(sprite_bunker* bunker, unsigned char * data){
    char i;

    bunker->sprite.sprctl0 = BPP_1 | TYPE_NORMAL;
    bunker->sprite.sprctl1 = REHV | LITERAL;
    bunker->sprite.sprcoll = 4;
    
    bunker->sprite.hsize = 0x0100;
    bunker->sprite.vsize = 0x0100;
    bunker->penpal[0] = COLOR_GREEN;

    bunker->sprite.data = data;
    for(i = 0; i < BUNKER_DATA_LEN; ++i){
        data[i] = bunker_template[i];
    }
}



void createEnemySprite(int i, int j, sprite_t* sprite, void* next){
    sprite->sprite.sprctl0 = BPP_1 | TYPE_NORMAL;
    sprite->sprite.sprctl1 = REHV;
    sprite->sprite.sprcoll = 1;
    sprite->sprite.data = singlepixel_data; 
    sprite->sprite.next = next;
    sprite->sprite.hsize = 0x0100 * SHIPWIDTH;
    sprite->sprite.vsize = 0x0100 * SHIPHEIGHT;
    sprite->initx = j * (SHIPWIDTH + SINV_SHIPGAPX);
    sprite->inity = i * (SHIPHEIGHT + SINV_SHIPGAPY);
    
    switch(i % 3){
        case 0:
            sprite->penpal[0] = COLOR_GREEN;
            break;
        case 1:
            sprite->penpal[0] = COLOR_RED;
            break;
        case 2:
            sprite->penpal[0] = COLOR_BLUE;
            break;
        default:
            sprite->penpal[0] = COLOR_WHITE;
            break;
    }
}

void createPlayerSprite(sprite_pl* player){
    player->sprite.sprctl0 = BPP_1 | TYPE_NORMAL;
	player->sprite.sprctl1 = REHV;
	player->sprite.sprcoll = 2;
	player->sprite.data = singlepixel_data;
	player->sprite.hsize = 0x0100 * PLAYER_SPRITE_WIDTH; 
	player->sprite.vsize = 0x0100 * PLAYER_SPRITE_HEIGHT; 
	player->penpal[0] = COLOR_WHITE;
}

void createShotSprite(sprite_shot* shot){
    shot->sprite.sprctl0 = BPP_1 | TYPE_NORMAL;
	shot->sprite.sprctl1 = REHV;
	shot->sprite.sprcoll = 3;
	shot->sprite.data = singlepixel_data;
	shot->sprite.hsize = 0x0100;
	shot->sprite.vsize = 0x0100 * SHOT_SPRITE_HEIGHT;
	shot->penpal[0] = COLOR_RED;
}

void createBombSprite(sprite_shot* shot){
    shot->sprite.sprctl0 = BPP_1 | TYPE_NORMAL;
	shot->sprite.sprctl1 = REHV;
	shot->sprite.sprcoll = 3;
	shot->sprite.data = singlepixel_data;
	shot->sprite.hsize = 0x0100;
	shot->sprite.vsize = 0x0100 * SHOT_SPRITE_HEIGHT;
	shot->penpal[0] = COLOR_YELLOW;
}
