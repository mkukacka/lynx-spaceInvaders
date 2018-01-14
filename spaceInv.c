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

int xpos = 30, ypos = 40;

void show_screen()
{
	// Clear current screen
	tgi_clear();
	

	tgi_setcolor(COLOR_WHITE);
	tgi_outtextxy(xpos, ypos, "Hello world!");

	tgi_sprite(&ship1.sprite);

	// last, draw the screen to buffer
	tgi_updatedisplay();
}

void setup_sprites(){
	// TODO
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
