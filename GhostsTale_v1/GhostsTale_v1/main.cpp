#include "GhostsTale_v1App.h"

int main() {
	
	int screenX = 1280;
	int screenY = 720;

	// allocation
	auto app = new GhostsTale_v1App();

	// initialise and loop
	app->run("AIE", screenX, screenY, false);

	// deallocation
	delete app;

	return 0;
}