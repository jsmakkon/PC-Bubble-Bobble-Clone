#ifndef IMAGES_H_
#define IMAGES_H_

#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include <vector>

using namespace std;

struct Image {
	Image(ALLEGRO_BITMAP* a, int b):bitmap_(a),index_(b){};
	ALLEGRO_BITMAP* bitmap_;
	int index_;
};

class Images {
	vector<Image> walls_;

public:
	Images();
	virtual ~Images();
	ALLEGRO_BITMAP* get_bitmap(int);
};

#endif /* IMAGES_H_ */
