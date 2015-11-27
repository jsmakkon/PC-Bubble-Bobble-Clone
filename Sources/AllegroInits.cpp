#include <stdio.h>
#include <iostream>
#include <time.h>
#include "AllegroInits.h"

const int SCREEN_WIDTH = 880;
const int SCREEN_LENGTH = 720;
const double FPS = 60.0;


AllegroInits::AllegroInits() {
	fprintf(stderr, "Starting allegro inits\n");
	if (!al_init()) {
		fprintf(stderr, "failed to init allegro!\n");
		throw (-1);
	}

	if (!al_install_keyboard()) {
		fprintf(stderr, "failed to initialize the keyboard!\n");
		throw (-1);
	}

	if (!al_init_image_addon()) {
		fprintf(stderr, "failed to initialize the allegro image addon!\n");
		throw (-1);
	}

	display = al_create_display(SCREEN_WIDTH, SCREEN_LENGTH);

	if (!display) {
		fprintf(stderr, "failed to initialize allegro display!\n");
		throw (-1);
	}

	timer = al_create_timer(1.0 / FPS);
	if (!timer) {
		fprintf(stderr, "failed to initialize allegro timer!\n");
		al_destroy_display (display);
		throw (-1);
	}

	event_queue = al_create_event_queue();
	if (!event_queue) {
		fprintf(stderr, "failed to initialize the allegro event queue!\n");
		al_destroy_display (display);
		al_destroy_timer (timer);
		throw (-1);
	}
	
	ALLEGRO_PATH *path = al_get_standard_path( ALLEGRO_RESOURCES_PATH );
    al_change_directory( al_path_cstr( path, '/' ) );
    al_destroy_path(path);

	al_register_event_source(event_queue, al_get_display_event_source(display));

	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_register_event_source(event_queue, al_get_keyboard_event_source());

	fprintf(stderr, "Inits done!\n");
}

AllegroInits::~AllegroInits() {
	al_destroy_display (display);
	al_destroy_timer (timer);
	al_destroy_event_queue(event_queue);
}

