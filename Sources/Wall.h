#ifndef WALL_H_
#define WALL_H_

#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "GameObject.h"

const int TILE_SIZE = 16;

class Wall {
	Coord x,y;
	ALLEGRO_BITMAP* image;
public:
	Wall();
	~Wall();
	boolean isEmptyTile() {
		if (image!=NULL) return false;
		else return true;
	}
	void set_position(Coord xx,Coord yy) {x=xx; y=yy;};
	void set_image(ALLEGRO_BITMAP*);
	Coord get_x() {return x;};
	Coord get_y() {return y;};

	void draw() {if (image!=NULL) al_draw_bitmap(image, x, y, 0);};
};

#endif /* WALL_H_ */
