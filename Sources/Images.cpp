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

	al_set_path_filename(path, "Bubble.png");
	fprintf(stderr, "Path: %s\n", al_path_cstr(path, '/'));
	walls_.push_back(Image(al_load_bitmap(al_path_cstr(path, '/')),0));
	al_set_path_filename(path, "Bubble_left.png");
	walls_.push_back(Image(al_load_bitmap(al_path_cstr(path, '/')),1));
	al_set_path_filename(path, "Bubble_ammo.png");
	walls_.push_back(Image(al_load_bitmap(al_path_cstr(path, '/')),2));
	al_set_path_filename(path, "mob_sproing.png");
	walls_.push_back(Image(al_load_bitmap(al_path_cstr(path, '/')),3));
	al_set_path_filename(path, "mob_sproing_left.png");
	walls_.push_back(Image(al_load_bitmap(al_path_cstr(path, '/')),4));
	al_set_path_filename(path, "Wall1.png");
	walls_.push_back(Image(al_load_bitmap(al_path_cstr(path, '/')),5));
	al_set_path_filename(path, "mob_walking_left.png");
	walls_.push_back(Image(al_load_bitmap(al_path_cstr(path, '/')),6));
	al_set_path_filename(path, "mob_walking_right.png");
	walls_.push_back(Image(al_load_bitmap(al_path_cstr(path, '/')),7));
	al_set_path_filename(path, "mob_walking_right2.png");
	walls_.push_back(Image(al_load_bitmap(al_path_cstr(path, '/')),8));
	al_set_path_filename(path, "mob_walking_left.png");
	walls_.push_back(Image(al_load_bitmap(al_path_cstr(path, '/')),9));
	al_set_path_filename(path, "mob_walking_left.png");
	walls_.push_back(Image(al_load_bitmap(al_path_cstr(path, '/')),10));
	al_set_path_filename(path, "mob_sproing_bubble.png");
	walls_.push_back(Image(al_load_bitmap(al_path_cstr(path, '/')),11));
	al_destroy_path(path);
}

Images::~Images() {

}

ALLEGRO_BITMAP* Images::get_bitmap(int index){
	for(std::vector<Image>::iterator it = walls_.begin(); it != walls_.end(); ++it) {
	    if ((*it).index_ == index) return (*it).bitmap_;
	}
	return NULL;

}

