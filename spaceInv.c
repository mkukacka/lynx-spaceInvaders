#include <stdlib.h>
#include <6502.h>
#include <lynx.h>
#include <tgi.h>
#include <conio.h>
#include <peekpoke.h>
#include <joystick.h>

#include <consts.h>
#include <sprites.h>

extern char lynxtgi[];
extern char lynxjoy[];

int xpos = 10, ypos = 10;

char SINV_NUMSHIPSX = 10;
char SINV_NUMSHIPSY = 6;
char SINV_SHIPGAPX = 3;
char SINV_SHIPGAPY = 2;
char SHIPWIDTH = 6;
char SHIPHEIGHT = 6;

sprite_t enemies[60];

void show_screen()
{
	char i;
	// Clear current screen
	tgi_clear();
	
	for(i=0; i<SINV_NUMSHIPSY * SINV_NUMSHIPSX; ++i){
		enemies[i].sprite.hpos = enemies[i].initx + xpos;
		enemies[i].sprite.vpos = enemies[i].inity + ypos;
	}
	//tgi_sprite(&ship1.sprite);
	tgi_sprite(&(enemies[SINV_NUMSHIPSY * SINV_NUMSHIPSX - 1].sprite));
	
	// draw score and live counter
	tgi_setcolor(COLOR_WHITE);
	tgi_outtextxy(0, 94, "Score:");
	tgi_outtextxy(90, 94, "Lives: 2");

	// last, draw the screen to buffer
	tgi_updatedisplay();
}

void setup_sprites(){
	char i,j;
	void *next = 0x00;
	sprite_t *sprite;

	for(i=0; i < SINV_NUMSHIPSY; ++i){
		for(j=0; j<SINV_NUMSHIPSX; ++j){
			
			sprite = &enemies[j + i*SINV_NUMSHIPSX];
			sprite->sprite.sprctl0 = BPP_1 | TYPE_NORMAL,
    		sprite->sprite.sprctl1 = REHV,
			sprite->sprite.sprcoll = 1,
			sprite->sprite.data = singlepixel_data; 
			sprite->sprite.next = next;
			sprite->sprite.hsize = 0x0100 * SHIPWIDTH;
			sprite->sprite.vsize = 0x0100 * SHIPHEIGHT;
			sprite->initx = j * (SHIPWIDTH + SINV_SHIPGAPX);
			sprite->inity = i * (SHIPHEIGHT + SINV_SHIPGAPY);
			//sprite->palette[1] = (color << 4) + color + 1;
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
			next = &sprite->sprite;
		}
	}
}

void initialize()
{
	tgi_install(&lynxtgi);
	joy_install(&lynxjoy);
	tgi_init();
	CLI();
	
	while (tgi_busy()) 
	{ 
	};

	tgi_setbgcolor(COLOR_BLACK); 
	tgi_setpalette(tgi_getdefpalette());
	
	tgi_setcolor(COLOR_BLACK);
	tgi_clear();

	setup_sprites();
}

void main(void) 
{
	unsigned char joy;
	
	initialize();

	while (1)
	{
		
        // input processing
		joy = joy_read(JOY_1);
		if(JOY_BTN_DOWN(joy)){
			ypos += 1;
		}
		if(JOY_BTN_UP(joy)){
			ypos -= 1;
		}
		if(JOY_BTN_LEFT(joy)){
			xpos -= 1;
		}
		if(JOY_BTN_RIGHT(joy)){
			xpos += 1;
		}
		
        // drawing screen
		show_screen();

        // active wait for screen sync
		while(tgi_busy()){ }
	};
}
