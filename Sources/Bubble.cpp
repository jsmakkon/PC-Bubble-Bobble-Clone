#include "Bubble.h"
#include "Images.h"
#include "Collision.h"

Bubble::Bubble(Direction i, Coord xx, Coord yy, Images* img, Level* l) :
		Game_Object(xx, yy, true, true, img, l) {
	spawn = clock();
	kill_active = true;
	current_image = img->get_bitmap(2);
	moving_direction = i;
	if (i == RIGHT) {
		xSpeed = BUBBLE_XSPEED;
	} else if (i == LEFT) {
		xSpeed = -BUBBLE_XSPEED;
	}
	ySpeed = 0;
}

void Bubble::draw(void) {
	al_draw_bitmap(current_image, x, y, 0);
}

void Bubble::move(void) {
	if (kill_active) {
		if (moves->x == -1)
			x += xSpeed;
		else
			x += moves->x;
		if (moves->x == 0) {
			kill_active = false;
			ySpeed = BUBBLE_YSPEED;
		}
	}
	else {
		y-=ySpeed;
	}
	if (x > (TILE_SIZE*LEVEL_X)) x-=(TILE_SIZE*LEVEL_X);
	if (x < -BUBBLE_SIZE) x += TILE_SIZE*LEVEL_X;
	if (y > TILE_SIZE*LEVEL_Y) y-=TILE_SIZE*LEVEL_Y;
	if (y < -BUBBLE_SIZE) y += TILE_SIZE*LEVEL_Y;
}

boolean Bubble::isAlive() {
	if ((clock() - spawn) >= ALIVE_TIME)
		return false;
	else
		return true;
}

boolean Bubble::isProtected() {
	if ((clock() - spawn) >= PROTECTED_TIME)
		return false;
	else
		return true;
}

boolean Bubble::isPushing() {
	if ((clock() - spawn) >= PUSH_TIME)
			return false;
		else
			return true;
}

void Bubble::set_push_hit() {
	push_hit = clock();
}


