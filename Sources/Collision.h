#ifndef COLLISION_H_
#define COLLISION_H_

#include <fstream>
#include "Level.h"
#include "GameObject.h"
#include "Wall.h"

struct Moves;
//Check for two objects collision, first object moving first. Handle collision differently if objects are moving to same direction.
namespace coll {

boolean check_objects_collision(Game_Object*, Game_Object*);

// Returns true if objects 2 bottoms squares are inside wall.
boolean is_object_insidewall(Game_Object* , Level* );

// This when player isn't inside wall, bubbles does this when kill_active.
// Check if object hits wall. Returns -1 if object can move freely, 0 if no movement can be made, float between 0 - speed if doing short movement.
Moves* check_wall_collision(Game_Object*, Level*);

Moves* bubble_roof_collision(Game_Object*, Level);
}

#endif /* COLLISION_H_ */
