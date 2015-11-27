#ifndef BUBBLE_H_
#define BUBBLE_H_

#include "GameObject.h"
#include <time.h>

class Images;
class Level;

struct Moves;

const int PUSH_TIME = 300;
const int PROTECTED_TIME = 220;
const int ALIVE_TIME = 20000;//almost milliseconds (clockticks) //TODO: divide with CLOCK_TICKS or something...
const float BUBBLE_XSPEED = 5.5f;
const float BUBBLE_YSPEED = 2.0f;
const float BUBBLE_SIZE = 32;

class Bubble: public Game_Object {
	clock_t spawn, push_hit;
	boolean kill_active; //
	Direction moving_direction; //-1 for left, 1 for right TODO: enum

public:
	Bubble(Direction,Coord,Coord, Images*,Level*);
	~Bubble(){};
	void draw(void);
	void move(void);
	boolean isAlive();
	boolean isProtected();
	boolean isPushing();
	void set_push_hit();
	boolean isKillActive(){return kill_active;};
};

#endif /* BUBBLE_H_ */
