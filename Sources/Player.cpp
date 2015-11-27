#include "Player.h"
#include "Images.h"
#include "Collision.h"

class Level;

Player::Player(Coord xx, Coord yy, Images* img, Level* l) :
		Game_Object(xx, yy, true, true, img, l) {
	current_image = img->get_bitmap(0);
	xSpeed = 0;
	falling = false;
	ySpeed = 0;
	facing = RIGHT;
}

//Move player
void Player::move(void) {

	if (moves->x == -1)
		x += xSpeed;
	else
		x += moves->x;

	if (moves->y == -1){
		y += ySpeed;
	}
	else{
		y += moves->y;
		if (moves->y == 0)
			falling = false;
		else falling = true;
	}

	if (x > (TILE_SIZE*LEVEL_X)) x-=(TILE_SIZE*LEVEL_X);
	if (x < -PLAYER_SIZE) x += TILE_SIZE*LEVEL_X;
	if (y > TILE_SIZE*LEVEL_Y) y-=TILE_SIZE*LEVEL_Y;
	if (y < -PLAYER_SIZE) y += TILE_SIZE*LEVEL_Y;
}

//Draw player, TODO: animation
void Player::draw(void) {

	if (xSpeed > 0) {
		current_image = imgs->get_bitmap(0);
	} else if (xSpeed < 0) {
		current_image = imgs->get_bitmap(1);
	}

	al_draw_bitmap(current_image, x, y, 0);
}

void Player::set_facing(Direction i) {
	facing = i;
}

