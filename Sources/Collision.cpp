#include "Collision.h"
#include "Player.h"

namespace coll {

//Check for two objects collision. In here we already got both objects movements, so we can move them and check if they collide.
boolean check_objects_collision(Game_Object* a, Game_Object* b) {

	float ay, ax, by, bx; // New positions for objects

	//fprintf(stderr, "Player pos: x:%f, y:%f. Bubble pos: x:%f, y:%f\n",a->get_x(),a->get_y(),b->get_x(),b->get_y());
	//fprintf(stderr, "Player speed: x:%f, y:%f. Bubble speed: x:%f, y:%f\n",a->get_xSpeed(),a->get_ySpeed(),b->get_xSpeed(),b->get_ySpeed());

	//Adding movements here
	if (a->get_moves()->y == -1) ay = a->get_y() + a->get_ySpeed();
	else ay = a->get_y() + a->get_moves()->y;

	if (a->get_moves()->x == -1) ax = a->get_x() + a->get_xSpeed();
	else ax = a->get_x() + a->get_moves()->x;

	if  (b->get_moves()->y == -1) by = b->get_y() + b->get_ySpeed();
	else by = b->get_y() + b->get_moves()->y;

	if (b->get_moves()->x == -1) bx = b->get_x() + b->get_xSpeed();
	else bx = b->get_x() + b->get_moves()->x;
	//fprintf(stderr, "Player after pos: x:%f, y:%f. Bubble after pos: x:%f, y:%f\n",ax, ay, bx, by);
	//Check if they are on top of each other:
	if (by > ay-32 && by < ay+32 && bx < ax+32 && bx > ax-32){
		//fprintf(stderr, "returning true from object collision!\n");
		return true;
	}
	else return false;
}

// Returns true if objects 2 bottoms squares are inside wall.
boolean is_object_insidewall(Game_Object* obj, Level* level) {
	int x = obj->get_x() / TILE_SIZE;
	int y = obj->get_y() / TILE_SIZE;

	int x_divide =  (int)obj->get_x()%TILE_SIZE;
	int y_divide =  (int)obj->get_y()%TILE_SIZE;

	//Object(PLAYER_SIZE*PLAYER_SIZE) fills 4 TILE_SIZE*TILE_SIZE squares, check if both bot squares are empty
	if (x_divide == 0
			&& y_divide == 0) {
		//fprintf(stderr, "Got inside 2x2 square situation\n");
		if (level->get_wall(x, y + 1)->isEmptyTile()
				&& level->get_wall(x + 1, y + 1)->isEmptyTile())
			return false;
		else
			return true;
	} else if (y_divide==0
			&& x_divide!=0) {
		//fprintf(stderr, "Got inside 3x2 square situation\n");
		if (level->get_wall(x, y + 1)->isEmptyTile()
				&& level->get_wall(x + 1, y + 1)->isEmptyTile()
				&& level->get_wall(x + 2, y + 1)->isEmptyTile())
			return false;
		else
			return true;
	} else if (y_divide!= 0
			&& x_divide== 0) {
		//fprintf(stderr, "Got inside 2x3 square situation\n");
		if (level->get_wall(x, y + 2)->isEmptyTile()
				&& level->get_wall(x + 1, y + 2)->isEmptyTile())
			return false;
		else
			return true;
	}
	//Object is now on 9 squares, check if 6 bottom squares are empty
	else {
		//fprintf(stderr, "Got inside 3x3 square situation\n");
		if (level->get_wall(x, y + 1)->isEmptyTile()
				&& level->get_wall(x + 1, y + 1)->isEmptyTile()
				&& level->get_wall(x + 2, y + 1)->isEmptyTile()
				&& level->get_wall(x, y + 2)->isEmptyTile()
				&& level->get_wall(x + 1, y + 2)->isEmptyTile()
				&& level->get_wall(x + 2, y + 2)->isEmptyTile())
			return false;
		else
			return true;
	}

	return false;
}

// This when player isn't inside wall, bubbles does this when kill_active.
// Check if object hits wall. Returns -1 if object can move freely, 0 if no movement can be made, float between 0 - speed if doing short movement.
Moves* check_wall_collision(Game_Object* obj, Level* level) {
	Moves *m = new Moves();
	m->x = -1;
	m->y = -1;

	int xpos = obj->get_x()/TILE_SIZE;
	int ypos = obj->get_y()/TILE_SIZE;

	float oy = obj->get_y();
	float ox = obj->get_x();
	float ySpeed = obj->get_ySpeed();
	float xSpeed = obj->get_xSpeed();

	
	for (int y = 0; y < LEVEL_Y; y++) {
		for (int x = 0; x < LEVEL_X; x++) {
			if (y < ypos-2 || y > ypos+4 || x < xpos -2 || x > xpos+4) continue;

			if (level->get_wall(x, y)->isEmptyTile())
				continue; // Skip non-walls

			int wally = level->get_wall(x, y)->get_y();
			int wallx = level->get_wall(x, y)->get_x();

			if (xSpeed < 0) { // Moving left
				//fprintf(stderr, "Got inside KEY_LEFT:Wall: x:%d, y:%d\n",wallx,wally);
				if (wally < (oy + PLAYER_SIZE) && wally >= (oy + TILE_SIZE)
						&& wallx >= (ox - (TILE_SIZE - xSpeed))
						&& wallx <= ox - TILE_SIZE) {
					m->x = -(ox - (wallx + TILE_SIZE));
				}

			} else if (xSpeed > 0) { // Moving right
				//fprintf(stderr, "Got inside KEY_RIGHT. Wally: %f, Wallx: %f, Playery: %f, Playerx:%f \n", wally,wallx,y,x);
				if (wally < (oy + PLAYER_SIZE) && wally >= (oy + TILE_SIZE)
						&& wallx <= (ox + (PLAYER_SIZE + xSpeed))
						&& wallx >= ox + PLAYER_SIZE) {
					//fprintf(stderr, "Returning blocking movement: %f\n",
							//-(wallx - (ox + PLAYER_SIZE)));
					m->x = (wallx - (ox + PLAYER_SIZE));

				}
			}
			if (ySpeed > 0) { //Moving down
				if (wallx < (ox + PLAYER_SIZE) && wallx > (ox - TILE_SIZE)
						&& wally <= (oy + (PLAYER_SIZE + ySpeed))
						&& wally >= oy + PLAYER_SIZE) {
					m->y = (wally - (oy + PLAYER_SIZE));
				} else if (xSpeed != 0) {
					if (xSpeed < 0) {
						if (wally < (oy + PLAYER_SIZE + ySpeed)
								&& wally >= (oy + PLAYER_SIZE)
								&& wallx > (ox - TILE_SIZE - (-xSpeed))
								&& wallx <= ox - TILE_SIZE && y != 0
								&& level->get_wall(x, y - 1)->isEmptyTile()) {
							m->y = 0;
						}
					}
					if (xSpeed > 0) {
						if (wally < (oy + PLAYER_SIZE + ySpeed)
								&& wally >= (oy + PLAYER_SIZE)
								&& wallx >= (ox + PLAYER_SIZE)
								&& wallx < ox + PLAYER_SIZE + xSpeed && y != 0
								&& level->get_wall(x, y - 1)->isEmptyTile()) {
							m->y = 0;
						}

					}
				}

			}

		}
	}

	//fprintf(stderr, "Returning player movements: x:%f y:%f \n", m->x, m->y);
	return m;
}

Moves* bubble_roof_collision(Game_Object* obj, Level* level) {
	Moves *m = new Moves();
	m->x = -1;
	m->y = -1;
	for (int y = 0; y < LEVEL_Y; y++) {
		for (int x = 0; x < LEVEL_X; x++) {
			if (level->get_wall(x, y)->isEmptyTile())
				continue; // Skip non-walls

			int wally = level->get_wall(x, y)->get_y();
			int wallx = level->get_wall(x, y)->get_x();
			float oy = obj->get_y();
			float ox = obj->get_x();
			float ySpeed = obj->get_ySpeed();

			//Moving up
			if (wallx < (ox + PLAYER_SIZE) && wallx > (ox - TILE_SIZE)
					&& wally <= (oy + (PLAYER_SIZE + ySpeed))
					&& wally >= oy + PLAYER_SIZE) {
				m->y = (wally - (oy + PLAYER_SIZE));
			}

		}
	}
	return m;

}
}

