#include "Wall.h"

Wall::Wall() {
	image = NULL;
}

Wall::~Wall() {
}

void Wall::set_image(ALLEGRO_BITMAP* i) {
	image = i;
	};
