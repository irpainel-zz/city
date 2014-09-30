#include "include/GlutFramework.h"
#include "include/Render.h"

using namespace glutFramework;

int main(int argc, char *argv[]) {


	GlutFramework * render;
	render = new Render();
	render->setLookAt(-50, 50, -30, 20, 0.6, 20, 0.0, 1.0, 0.0);
	render->startFramework(argc, argv);
	
	delete (render);
	return 0;

}
