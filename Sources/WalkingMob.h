#ifndef WALKINGMOB_H_
#define WALKINGMOB_H_

#include "Mob.h"
#include "Images.h"

class Walking_mob:public Mob {
	Direction facing;
public:
	Walking_mob(Coord, Coord, boolean, boolean, Images*, Level*);
	~Walking_mob(){};
	void doAction();
	void draw(void);
	void move(void);
};

#endif
