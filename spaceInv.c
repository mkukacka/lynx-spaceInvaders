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
char fire1 = 0, fire2 = 0;

char SINV_NUMSHIPSX = 10;
char SINV_NUMSHIPSY = 6;
char SINV_SHIPGAPX = 3;
char SINV_SHIPGAPY = 2;
char SHIPWIDTH = 8;
char SHIPHEIGHT = 6;

char SCREEN_WIDTH;

sprite_pl player;
sprite_t enemies[60];
sprite_shot shot;

// player constants
char playerYPos = 85;
char playerHSpeed = 2;
char playerSpriteWidth = 16;
char playerSpriteHeight = 6;

// player variables
char playerXPos = 10;

// ship movement - constants
char shipMoveMargin = 5; 	// how close to the screen border will ships switch direction
char shipMoveCnt = 0;		// incremented on every tick, till reaches shipMoveSpeed
char shipMoveXStep = 4;		// ship move horizontally - pixels
char shipMoveYStep = 2;		// ship move vertically - pixels

// ship movement - variables
char shipMoveDirection = 2;	// 2 = right, 0 = left
char shipMoveSpeed = 1; 	// per how many ticks will the ships move
char shipXPos = 5, shipYPos = 10;	// position of the ship grid

// shot constants 
char shotVertSpeed = 5;
char shotSpriteHeight;

// shot variables
char shotXPos = 80, shotYPos = 50;	// test values
char shotFired = 1;	// display the sprite or not

// bomb variables - let's do one bomb for now
char bombXPos = 40, bombYPost = 40;	// test values
char bombFired = 1;

// FOR TESTING
char text[10];

void show_screen()
{
	char i, newShipMoveDirection = shipMoveDirection;
	// Clear current screen
	tgi_clear();
	
	// position ships
	for(i=0; i<SINV_NUMSHIPSY * SINV_NUMSHIPSX; ++i){
		enemies[i].sprite.hpos = enemies[i].initx + shipXPos;
		enemies[i].sprite.vpos = enemies[i].inity + shipYPos;

		if(enemies[i].sprite.hpos >= (SCREEN_WIDTH - SHIPWIDTH - shipMoveMargin)){
			// one ship is being drawn too close to right border
			newShipMoveDirection = 0;	// turn the movement direction to left
		}
		if(enemies[i].sprite.hpos <= shipMoveMargin){
			newShipMoveDirection = 2;
		}
	}

	// move ships
	++shipMoveCnt;
	if(shipMoveCnt % shipMoveSpeed == 0){
		if(newShipMoveDirection != shipMoveDirection){
			// lower the ship if the movement direction was reversed
			shipMoveDirection = newShipMoveDirection;
			shipYPos += shipMoveYStep;
		} else {
			// move ships horizontally
			shipXPos += ((int)shipMoveDirection - 1) * shipMoveXStep;
		}
		shipMoveCnt = 0;
	}

	// move shot
	if(shotFired){
		if(shotYPos < shotVertSpeed) shotFired = 0;
		shotYPos -= shotVertSpeed;
	}

	// position and draw shot
	if(shotFired){
		shot.sprite.hpos = shotXPos;
		shot.sprite.vpos = shotYPos;
		tgi_sprite(&(shot.sprite));
	}

	// TODO: position and draw bombs

	// draw ships
	tgi_sprite(&(enemies[SINV_NUMSHIPSY * SINV_NUMSHIPSX - 1].sprite));

	// check if any ship has been hit
	for(i=0; i<SINV_NUMSHIPSY * SINV_NUMSHIPSX; ++i){
		if(enemies[i].collindex > 0){
			// testing output of collision detection:
			// itoa(i, text, 10);
  			// tgi_outtextxy(50, 90, text);

			// kill the ship
			enemies[i].penpal[0] = 0;
			shotFired = 0;
		}
	}

	// player sprite
	player.sprite.hpos = playerXPos;
	player.sprite.vpos = playerYPos;
	tgi_sprite(&(player.sprite));
	
	// draw score and live counter
	tgi_setcolor(COLOR_WHITE);
	tgi_outtextxy(0, 94, "Score:");
	tgi_outtextxy(90, 94, "Lives: 2");

	// last, draw the screen to buffer
	tgi_updatedisplay();
}

void reset_ships(){
	shipMoveDirection = 2;
	shipMoveSpeed = 7;
	shipXPos = 5;
	shipYPos = 10;

	shotFired = 0;
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

	// player sprite
	player.sprite.sprctl0 = BPP_1 | TYPE_NORMAL;
	player.sprite.sprctl1 = REHV;
	player.sprite.sprcoll = 2;
	player.sprite.data = singlepixel_data;
	player.sprite.hsize = 0x0100 * playerSpriteWidth; 
	player.sprite.vsize = 0x0100 * playerSpriteHeight; 
	player.penpal[0] = COLOR_WHITE;

	// shot sprite
	shot.sprite.sprctl0 = BPP_1 | TYPE_NORMAL;
	shot.sprite.sprctl1 = REHV;
	shot.sprite.sprcoll = 3;
	shot.sprite.data = singlepixel_data;
	shot.sprite.hsize = 0x0100;
	shot.sprite.vsize = 0x0400;
	shot.penpal[0] = COLOR_RED;
}

void initialize()
{
	tgi_install(&lynxtgi);
	joy_install(&lynxjoy);
	tgi_init();
	tgi_setcollisiondetection(1);
	CLI();

	SCREEN_WIDTH = tgi_getmaxx();
	
	while (tgi_busy()) 
	{ 
	};

	tgi_setbgcolor(COLOR_BLACK); 
	tgi_setpalette(tgi_getdefpalette());
	
	tgi_setcolor(COLOR_BLACK);
	tgi_clear();

	setup_sprites();
	reset_ships();
}

void movePlayerLeft(){
	if(playerXPos >= playerHSpeed)
		playerXPos -= playerHSpeed;
}

void movePlayerRight(){
	if(playerXPos <= (SCREEN_WIDTH - playerHSpeed)){
		playerXPos += playerHSpeed;
	}
}

void fireShot(){
	if(!shotFired){
		shotFired = 1;
		shotXPos = playerXPos + playerSpriteWidth / 2;
		shotYPos = playerYPos - shotSpriteHeight;
	}
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
			movePlayerLeft();
		}
		if(JOY_BTN_RIGHT(joy)){
			movePlayerRight();
		}

		if(JOY_BTN_FIRE(joy)){
			fireShot();
		} else {
			//fire1 = 0;
		}
		if(JOY_BTN_FIRE2(joy)){
			fireShot();
		} else {
			//fire2 = 0;
		}
		
        // drawing screen
		show_screen();

        // active wait for screen sync
		while(tgi_busy()){ }
	};
}