#include <list>
#include <string>
#include <iostream>
#include <fstream>

#include "Images.h"

#include "Level.h"
using namespace std;

Level::Level(int a, string filename, Images* images) {
	level_number = a;
	ifstream myfile;
	string line;
	ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
	al_append_path_component(path, "levels");
	al_set_path_filename(path,filename.c_str()); 

	fprintf(stderr, "Level path in allegro path: %s\n", al_path_cstr(path,'/'));
	myfile.open (al_path_cstr(path,'/'));
	if (myfile.is_open()) {
		for (int y = 0; y < LEVEL_Y; y++) {
			getline(myfile,line);
			fprintf(stderr, "Read line: %s\n", line.c_str());
			for (int x = 0; x < LEVEL_X;x++) {
				tiles[x][y].set_position(x*16,y*16);
				if (line[x] =='x') {
					tiles[x][y].set_image(images->get_bitmap(5));
				}
			}
		}
	}
	else fprintf(stderr, "Failed to read file!"); //TODO: Shut down
	myfile.close();
	fprintf(stderr, "Level created!\n");
	al_destroy_path(path);

}


