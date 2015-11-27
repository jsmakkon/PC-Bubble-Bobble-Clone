#ifndef PLAYER_H_
#define PLAYER_H_

const int PLAYER_SIZE = 32;
const float PLAYER_XSPEED = 2.1f;
const float PLAYER_YSPEED = 3.7f;
const int JUMP_TIME = 500;

#include "GameObject.h"
#include "Collision.h"

using namespace coll;

class Images;
class Level;

class Player:public Game_Object {
protected:
	Direction facing; // -1 for left, 1 for right. TODO: enum
	boolean falling;
	clock_t jumping_started;
public:
	Player(Coord, Coord, Images*, Level*);
	~Player(){};
	void move(void);
	void draw(void);
	void set_facing(Direction);

	Direction get_facing(){return facing;};

	boolean is_falling(){return falling;};

	void set_falling(boolean a) {falling=a;};

	void start_jumping(){jumping_started = clock();};

	boolean continueJumping(){
		if ((clock() - jumping_started) >= JUMP_TIME)
			return false;
		else
			return true;
	};
};

#endif /* PLAYER_H_ */
