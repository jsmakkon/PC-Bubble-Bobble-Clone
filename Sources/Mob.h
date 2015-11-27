#ifndef MOB_H_
#define MOB_H_

#include "GameObject.h"

const float MOB_WALK_SPEED = 2.0;
const float MOB_FALL_SPEED = 1.5;
const float MOB_JUMP_SPEED = 5.0;

class Mob: public Game_Object {
protected:
	Direction facing; // -1 for left, 1 for right. TODO: enum
	boolean is_in_bubble;

public:
	Mob(Coord xx, Coord yy, boolean hw, boolean hoo, Images *images, Level* l):Game_Object(xx,yy,hw,hoo,images,l){is_in_bubble = false;};
	~Mob(){};
	virtual void move(void)=0;
	virtual void draw(void)=0;
	boolean isInBubble() {return is_in_bubble;};
	void setInBubble() {is_in_bubble=true;};
};

#endif
