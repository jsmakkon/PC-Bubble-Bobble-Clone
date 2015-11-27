#include <stdio.h>
#include <iostream>
#include <time.h>
#include <list>

#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"

#include "AllegroInits.h"
#include "Level.h"
#include "Player.h"
#include "Bubble.h"
#include "Wall.h"
#include "Mob.h"
#include "WalkingMob.h"
#include "Collision.h"
#include "GameObject.h"
#include "Levelstart.h"

void do_wall_calculations();
void move_player();
void draw_bubbles();
void move_bubbles();
void draw_mobs();
void move_mobs();
void do_object_collisions();
void do_movements();

//TODO: Do something to these globals...
Images* images;
Level* level;
Player *p;

std::list<Bubble*> bubbles;
std::list<Mob*> mobs;


enum MYKEYS {
	KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};

int runLevel(AllegroInits* inits) {
	fprintf(stderr, "Starting!\n");
	images = new Images();
	p  = new Player((Coord) 500, (Coord) 500, images, level);
	bubbles = std::list<Bubble*>();
	mobs = std::list<Mob*>();
	string mapname =  "map1.txt";
	level = new Level(1, mapname, images);
	mobs.push_back(new Walking_mob((Coord) 300, (Coord) 200,true,true, images, level));
	mobs.push_back(new Walking_mob((Coord) 100, (Coord) 200,true,true, images, level));
	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_flip_display();

	al_start_timer(inits->timer);
	fprintf(stderr, "Starting loop\n");

	bool key[4] = { false, false, false, false };
	boolean doexit = false, redraw = false;
	while (!doexit) {

		ALLEGRO_EVENT ev;
		al_wait_for_event(inits->event_queue, &ev);

		//Timer event, movements done in here
		if (ev.type == ALLEGRO_EVENT_TIMER) {

			if (key[KEY_LEFT]) {
				p->set_xSpeed(-PLAYER_XSPEED);
				p->set_facing(LEFT);

			} else if (key[KEY_RIGHT]) {

				p->set_xSpeed(PLAYER_XSPEED);
				p->set_facing(RIGHT);

			} else
				p->set_xSpeed(0);

			if (key[KEY_UP] && !p->is_falling() &&p->continueJumping()) {
				
					p->set_ySpeed(-PLAYER_YSPEED);
				
			} else {
				p->set_falling(true);
				p->set_ySpeed(PLAYER_YSPEED);
			}
			do_wall_calculations();
			do_object_collisions();
			do_movements();

			redraw = true;
		}
		// Window closed
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
			// Key pressed
		} else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				key[KEY_UP] = true;
				if (!p->is_falling())p->start_jumping();
				break;

			case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = true;
				break;

			case ALLEGRO_KEY_LEFT:
				key[KEY_LEFT] = true;
				break;

			case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = true;
				break;

			case ALLEGRO_KEY_SPACE:
				Bubble *b = new Bubble(p->get_facing(), p->get_x(), p->get_y(), images,
								level);
				bubbles.push_back(b);
				break;
			}
		}
		// Key released
		else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				key[KEY_UP] = false;
				break;

			case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = false;
				break;

			case ALLEGRO_KEY_LEFT:
				key[KEY_LEFT] = false;
				break;

			case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = false;
				break;

			case ALLEGRO_KEY_ESCAPE:
				doexit = true;
				break;
			}
		}
		// Drawing here
		if (redraw && al_is_event_queue_empty(inits->event_queue)) {
			redraw = false;

			al_clear_to_color(al_map_rgb(0, 0, 0));
			level->drawLevel();
			draw_bubbles();
			draw_mobs();
			p->draw();

			al_flip_display();
		}
	}

	delete level;
	delete p;
	delete images;
	delete inits;
	return 0;
}

// Does movement calcs (check if objects hit walls, and sets amount of movements that can be made).
// This is done first when starting objects movement and collision calculations.
void do_wall_calculations() {
	if (coll::is_object_insidewall(p, level)) {
		Moves *m = new Moves();
		m->x = -1;
		m->y = -1;
		p->set_moves(m);
	} else
		p->set_moves(coll::check_wall_collision(p, level));

	for (std::list<Bubble*>::iterator it = bubbles.begin(); it != bubbles.end();
			++it) {
		(*it)->set_moves(coll::check_wall_collision((*it), level));
	}

	for (std::list<Mob*>::iterator it = mobs.begin(); it != mobs.end();
			++it) {
		(*it)->set_moves(coll::check_wall_collision((*it), level));
	}
	//TODO: mob calcs
}

// Check all objects collisions here and do actions needed with collisions.
void do_object_collisions() {
	std::list<Bubble*>::iterator bub_it = bubbles.begin();
	std::list<Mob*>::iterator mob_it = mobs.begin();
	boolean destroyed;
	//Start running through the bubble list
	while (bub_it != bubbles.end()) {
		destroyed = false;
		mob_it = mobs.begin();
		//Check collisions with mobs
		if ((*bub_it)->isKillActive()) { // Skip if bubble is just shot, "kill-active"
			while (mob_it != mobs.end()){
				if (!(*bub_it)->isKillActive()){
					mob_it++;
				}
				else{
					// Check if mob is hit, kill bubble and turn mob into a bubble
					if (coll::check_objects_collision((*mob_it),(*bub_it))) {
						bubbles.erase(bub_it++);
						(*mob_it)->setInBubble();
						(*mob_it)->set_xSpeed(0);
						(*mob_it)->set_ySpeed(-BUBBLE_YSPEED);
						destroyed = true;
						break;
					}
					mob_it++;
				}
			}
		}
		if (destroyed) continue; // Bubble was destroyed while hitting mob, lets take next one

		//Check if bubble hits player
		if ((*bub_it)->isProtected()){
			fprintf(stderr, "Bubble is protected\n");
		} else if (coll::check_objects_collision(p,(*bub_it))) {
			fprintf(stderr, "Destroying bubble\n");
			bubbles.erase(bub_it++);
			continue;

		}if (!(*bub_it)->isAlive()) {
			bubbles.erase(bub_it++);
		}
		else {
			//fprintf(stderr, "Doing nothing to bubble\n");
			++bub_it;
		}
	}
	//Running through mob list with player
	mob_it = mobs.begin();
	while (mob_it != mobs.end()){
		//Check if collision happens
		if (coll::check_objects_collision(p,(*mob_it))) {
			// Check if mob is in bubble
			if ((*mob_it)->isInBubble()) {
				mobs.erase(mob_it++);
				continue;
			}
			else {
				p->set_x(500);
				p->set_y(500);
				break;
			}
		}
		mob_it++;
	}
}

void do_movements() {
	p->move();

	for (std::list<Bubble*>::iterator it = bubbles.begin(); it != bubbles.end();) {
		(*it)->move();
		++it;
	}
	for (std::list<Mob*>::iterator it = mobs.begin(); it != mobs.end();) {
		(*it)->move();
		++it;
	}
}
//Old, not used
// Check bubble collisions and mob collisions with player. Afterwards move player if not hit mob.
void move_player() {
	for (std::list<Bubble*>::iterator it = bubbles.begin(); it != bubbles.end();) {
		if ((*it)->isProtected()){
			fprintf(stderr, "Bubble is protected\n");
			++it;
			continue; // Skip bubbles which are just fired.
		}

		else if (coll::check_objects_collision(p,(*it))) {
			fprintf(stderr, "Destroying bubble\n");
			bubbles.erase(it++);
		}
		else {
			//fprintf(stderr, "Doing nothing to bubble\n");
			++it;
		}
	}
	for (std::list<Mob*>::iterator it = mobs.begin(); it != mobs.end();
			) {
				if (coll::check_objects_collision(p,(*it))) {
					p->set_x(500);
					p->set_y(500);
					break;
				}
			it++;
	}

	p->move();

}

//Old, not used
// For loop to cycle through bubbles to draw them.
// This is done last.
void draw_bubbles() {
	for (std::list<Bubble*>::iterator it = bubbles.begin(); it != bubbles.end();
			++it) {
		(*it)->draw();
	}
}

//Old, not used
// Checking wall collision and object collision with all mobs, moving bubbles after if not collided with mobs.
void move_bubbles() {
	for (std::list<Bubble*>::iterator it = bubbles.begin(); it != bubbles.end();
			) {
		if (!(*it)->isAlive()) {
			bubbles.erase(it++);
		}
		
		(*it)->move();
		++it;
	}
}
//Old, not used
void move_mobs() {
	for (std::list<Mob*>::iterator it = mobs.begin(); it != mobs.end();
			) {
			(*it)->move();
			it++;
	}
}
//Old, not used
void draw_mobs() {
	for (std::list<Mob*>::iterator it = mobs.begin(); it != mobs.end();
			) {
			(*it)->draw();
			++it;
	}
}
