#include <stdlib.h>
#include <6502.h>
#include <lynx.h>
#include <tgi.h>
#include <conio.h>
#include <peekpoke.h>
#include <joystick.h>

#include "consts.h"
#include "sprites.h"

extern char lynxtgi[];
extern char lynxjoy[];

int xpos = 10, ypos = 10;
char fire1 = 0, fire2 = 0;

char SCREEN_WIDTH;

sprite_pl player;
sprite_t enemies[NUMSHIPSX * NUMSHIPSY];
sprite_shot shot;
sprite_bunker bunkers[BUNKER_CNT];
unsigned char bunkerData[BUNKER_CNT * BUNKER_DATA_LEN];
sprite_bomb *bombs = 0;	// linked list

// player variables
char playerXPos = 10;

// ship movement - variables
char shipMoveDirection = 2;	// 2 = right, 0 = left
char shipMoveSpeed = 1; 	// per how many ticks will the ships move
char shipXPos = 5, shipYPos = 10;	// position of the ship grid
char shipMoveCnt = 0;		// incremented on every tick, till reaches shipMoveSpeed

// shot variables
char shotXPos = 80, shotYPos = 50;	// test values
char shotFired = 1;	// display the sprite or not

// bomb variables - let's do one bomb for now
// char bombXPos = 40, bombYPost = 40;	// test values
// char bombFired = 1;

// bombs - several bombs possible at once, with random probability,
//  can be destroyed with shots
//  only the bottom-most ship in the column can produce a bomb

// FOR TESTING
char text[10];

void processBunkerHit(sprite_bunker* bunker){
	// TODO
}

void createNewBomb(int x, int y){
	sprite_bomb * prev = 0, *current = bombs;
	sprite_bomb * bomb = (sprite_bomb*)malloc(sizeof(sprite_bomb));
	createBombSprite(bomb);
	bomb->sprite.hpos = x;
	bomb->sprite.vpos = y;
	
	if(bombs != 0){
		while(current != 0){
			prev = current;
			current = current->next;
		}
		
		prev->next = bomb;
	} else {
		bombs = bomb;
	}
	bomb->next = 0;
}

void destroyBomb(sprite_bomb *bomb){
	sprite_bomb * prev = 0, *current = bombs;
	while(current != bomb){
		prev = current;
		current = current->next;
	}
	prev->next = current->next;
	free(bomb);
}

void show_screen()
{
	char i, j, newShipMoveDirection = shipMoveDirection;
	char lowestShipInColumnIndex;
	sprite_bomb * bomb = bombs;
	// Clear current screen
	tgi_clear();
	
	// position ships
	for(i=0; i<SINV_NUMSHIPSY * SINV_NUMSHIPSX; ++i){
		enemies[i].sprite.hpos = enemies[i].initx + shipXPos;
		enemies[i].sprite.vpos = enemies[i].inity + shipYPos;

		if(enemies[i].sprite.hpos >= (SCREEN_WIDTH - SHIPWIDTH - SHIP_MOVE_MARGIN)){
			// one ship is being drawn too close to right border
			newShipMoveDirection = 0;	// turn the movement direction to left
		}
		if(enemies[i].sprite.hpos <= SHIP_MOVE_MARGIN){
			newShipMoveDirection = 2;
		}
	}

	// init bombs 
	// - this way there is larger chance to have a bomb when there are more alive columns
	// - possibly this may not be the ideal way, but let's try it, it might be interesting
	for(i=0; i<SINV_NUMSHIPSX; ++i){
		// find if there is any alive ship in this column
		lowestShipInColumnIndex = SINV_NUMSHIPSY;
		for(j=0; j<SINV_NUMSHIPSY; ++j){
			if(enemies[i + j*SINV_NUMSHIPSX].alive){
				lowestShipInColumnIndex = j;
			}
		}

		// find if a bomb should be dropped from this column
		if(lowestShipInColumnIndex < SINV_NUMSHIPSY){	// if there is any alive ship in this column
			// roll the dice
			if( (rand() % 100) < 2){
				// init new bomb
				createNewBomb(
					enemies[i + lowestShipInColumnIndex * SINV_NUMSHIPSX].sprite.hpos,
					enemies[i + lowestShipInColumnIndex * SINV_NUMSHIPSX].sprite.vpos
				);

			}
		}
	}

	// move ships
	++shipMoveCnt;
	if(shipMoveCnt % shipMoveSpeed == 0){
		if(newShipMoveDirection != shipMoveDirection){
			// lower the ship if the movement direction was reversed
			shipMoveDirection = newShipMoveDirection;
			shipYPos += SHIP_MOVE_YSTEP;
		} else {
			// move ships horizontally
			shipXPos += ((int)shipMoveDirection - 1) * SHIP_MOVE_XSTEP;
		}
		shipMoveCnt = 0;
	}

	// position and draw shot
	if(shotFired){
		shot.sprite.hpos = shotXPos;
		shot.sprite.vpos = shotYPos;
		tgi_sprite(&(shot.sprite));
	}

	// move shot
	if(shotFired){
		if(shotYPos < SHOT_VERT_SPEED) shotFired = 0;
		shotYPos -= SHOT_VERT_SPEED;
	}

	// position and draw bombs
	while(bomb != 0){
		tgi_sprite(&(bomb->sprite));
		bomb->sprite.vpos += BOMB_VERT_SPEED;
		bomb = bomb->next;
	}

	// draw ships
	tgi_sprite(&(enemies[SINV_NUMSHIPSY * SINV_NUMSHIPSX - 1].sprite));

	// check if any ship has been hit
	for(i=0; i<SINV_NUMSHIPSY * SINV_NUMSHIPSX; ++i){
		if(enemies[i].collindex == 3){
			// testing output of collision detection:
			// itoa(i, text, 10);
  			// tgi_outtextxy(50, 90, text);

			// kill the ship
			enemies[i].penpal[0] = 0;
			enemies[i].alive = 0;
			shotFired = 0;
		}
	}

	// player sprite
	player.sprite.hpos = playerXPos;
	player.sprite.vpos = PLAYER_YPOS;
	tgi_sprite(&(player.sprite));

	// bunker sprite
	for(i = 0; i < BUNKER_CNT; ++i){
		tgi_sprite(&(bunkers[i].sprite));
		if(bunkers[i].collindex > 0){
			// bunker hit
			processBunkerHit(&(bunkers[i]));
		}
	}
	
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
			createEnemySprite(i, j, sprite, next);
			next = &sprite->sprite;
		}
	}

	// player sprite
	createPlayerSprite(&player);

	// shot sprite
	createShotSprite(&shot);

	for(i = 0; i < BUNKER_CNT; ++i){
		createBunkerSprite(&bunkers[i], &(bunkerData[i*BUNKER_DATA_LEN]));
		bunkers[i].sprite.vpos = BUNKER_YPOS;
		bunkers[i].sprite.hpos = BUNKER_LEFT_OFFSET + i*BUNKER_GAP;
	}
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
	if(playerXPos >= PLAYER_HSPEED)
		playerXPos -= PLAYER_HSPEED;
}

void movePlayerRight(){
	if(playerXPos <= (SCREEN_WIDTH - PLAYER_HSPEED - PLAYER_SPRITE_WIDTH)){
		playerXPos += PLAYER_HSPEED;
	}
}

void fireShot(){
	if(!shotFired){
		shotFired = 1;
		shotXPos = playerXPos + PLAYER_SPRITE_WIDTH / 2;
		shotYPos = PLAYER_YPOS - SHOT_SPRITE_HEIGHT;
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