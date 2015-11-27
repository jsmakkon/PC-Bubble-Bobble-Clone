#include <stdio.h>
#include <iostream>
#include <time.h>
#include <list>

#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"

#include "AllegroInits.h"
#include "Levelstart.h"

static AllegroInits* inits;

int main(){
	fprintf(stderr, "Starting program\n");
	//TODO: Menu
	inits = new AllegroInits();
	int level = runLevel(inits);

	return 0;
}