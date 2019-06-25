#include "GhostsTale_v1App.h"

int main() {
	
	// allocation
	auto app = new GhostsTale_v1App();

	// initialise and loop
	app->run("AIE", 1280, 720, false);

	// deallocation
	delete app;

	return 0;
}