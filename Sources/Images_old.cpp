/*
 * Images.cpp
 *
 *  Created on: Mar 19, 2012
 *      Author: Joni
 */

#include "Images.h"

//TODO: Handle "image not found"
Images::Images() {
	ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
	al_append_path_component(path, "Images");

	al_set_path_filename(path, "Character_left.png");
	fprintf(stderr, "Path: %s\n", al_path_cstr(path, '/'));
	images_.push_back(Image(al_load_bitmap(al_path_cstr(path, '/')),0));
	al_set_path_filename(path, "Character_right.png");
	images_.push_back(Image(al_load_bitmap(al_path_cstr(path, '/')),1));
	al_destroy_path(path);
}

Images::~Images() {

}

ALLEGRO_BITMAP* Images::get_bitmap(int index){
	for(std::vector<Image>::iterator it = images_.begin(); it != images_.end(); ++it) {
	    if ((*it).index_ == index) return (*it).bitmap_;
	}
	return NULL;

}

