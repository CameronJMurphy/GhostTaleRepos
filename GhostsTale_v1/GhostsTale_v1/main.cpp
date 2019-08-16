#include "GhostsTale_v1App.h"




int main() {
	
	int screenX = 21 * 34;
	int screenY = 21 * 34;
	
	
	// allocation
	auto app = new GhostsTale_v1App();

	// initialise and loop
	app->run("AIE", screenX, screenY, false);

	// deallocation
	delete app;

	return 0;
}