
#include "WalkingMob.h"
#include "Images.h"
#include "Wall.h"
#include "Level.h"
#include "Player.h"

Walking_mob::Walking_mob(Coord xx, Coord yy, boolean hw, boolean hoo, Images* i, Level* l):Mob(xx,yy,hw,hoo,i,l) {
	facing = LEFT;
	xSpeed = 0;
	ySpeed = MOB_FALL_SPEED;
	current_image = imgs->get_bitmap(6);
}

void Walking_mob::doAction(){};

void Walking_mob::draw(){
	
	if (is_in_bubble) {
		current_image = imgs->get_bitmap(11);
	} else
	if (xSpeed > 0) {
		current_image = imgs->get_bitmap(7);
	} else if (xSpeed < 0) {
		current_image = imgs->get_bitmap(6);
	}

	al_draw_bitmap(current_image, x, y, 0);
};

void Walking_mob::move(){
	
	//Basic movement part
	if (moves->x == -1)
		x += xSpeed;
	else
		x += moves->x;

	if (moves->y == -1){
		y += ySpeed;
	}
	else{
		y += moves->y;
	}

	//Turn around if we hit wall, or start falling TODO: Move this code block to somewhere else..
	if (moves->y == 0){
		if (facing == LEFT)
		xSpeed = -MOB_WALK_SPEED;
		else 
			xSpeed = MOB_WALK_SPEED;
	}
	else xSpeed = 0;
	
	if (moves->x == 0 && moves->y ==0) {
		if (facing ==LEFT) {
			facing = RIGHT;
			xSpeed = MOB_WALK_SPEED;
		}
		else {
			facing = LEFT;
			xSpeed = -MOB_WALK_SPEED;
		}
	}

	if (x > (TILE_SIZE*LEVEL_X)) x-=(TILE_SIZE*LEVEL_X);
	if (x < -PLAYER_SIZE) x += TILE_SIZE*LEVEL_X;
	if (y > TILE_SIZE*LEVEL_Y) y-=TILE_SIZE*LEVEL_Y;
	if (y < -PLAYER_SIZE) y += TILE_SIZE*LEVEL_Y;

};