#ifndef LEVEL_H_
#define LEVEL_H_
#include <string>
#include "allegro5/allegro.h"
#include "Wall.h"

const int LEVEL_X = 55; // Level size 55*45 tiles
const int LEVEL_Y = 45;
class Images;

class Level {
	Wall tiles[LEVEL_X][LEVEL_Y]; //x,y
	int level_number;
public:
	Level(int, std::string, Images*);

	Wall* get_wall(int x, int y) {return &tiles[x][y];};

	void drawLevel() {
		for (int y = 0; y < LEVEL_Y; y++) {
				for (int x = 0; x < LEVEL_X; x++) {
					if (!tiles[x][y].isEmptyTile())
						tiles[x][y].draw();
				}
			}
	};
};



#endif /* LEVEL_H_ */
