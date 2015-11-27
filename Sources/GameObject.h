
#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include <stdio.h>
class Level;
class Images;

typedef float Coord;
typedef float Speed;

enum Direction {
	LEFT,RIGHT
};

struct Moves {
	float x, y;
};

class Game_Object {

protected:
	Coord x,y;
	Speed xSpeed, ySpeed;
	boolean hits_walls, hits_other_objects;
	Images * imgs;
	ALLEGRO_BITMAP* current_image;
	Level* level;
	Moves* moves;

	Game_Object(Coord xx, Coord yy, boolean hw, boolean hoo, Images *images, Level* l):
					x(xx), y(yy), hits_walls(hw), hits_other_objects(hoo), imgs(images), level(l) {
		current_image = NULL;
		moves = new Moves();
				};

public:

	~Game_Object(){};
	virtual void move(void)=0;
	virtual void draw(void)=0;
	Speed get_xSpeed() {return xSpeed;}
	Speed get_ySpeed() {return ySpeed;}
	Coord get_x() {return x;};
	Coord get_y() {return y;};
	void set_xSpeed(Speed a){xSpeed = a;};
	void set_ySpeed(Speed a){ySpeed = a;};
	void set_x(Coord a) {x=a;};
	void set_y(Coord a) {y=a;};
	void set_moves(Moves* a) {moves = a;};
	Moves* get_moves() {return moves;};

};

#endif /* GAMEOBJECT_H_ */
