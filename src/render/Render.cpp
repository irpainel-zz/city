/*
 * Render.cpp
 *
 *  Created on: Sep 29, 2014
 *      Author: Iury Roger Painelli
 */

#include "Render.h"

using namespace glutFramework;

Render::Render() {
	toggleAxes = 0;
	th = 0;
	zoom = 1.0;

	keyDown=0;
	mouseLeftDown = false;
	mouseRightDown = false;

	winWidth = 0;
	winHeight = 0;
	midWindowX = 0;
	midWindowY = 0;

	timebase = 0;
	time = 0;
	frame = 0;

	streets = NULL;
	camera = new Camera();

	fpsInfo = "FPS: 0";
}

void Render::load()
{
	skybox = new Skybox();
	streets = new Streets(500, 500);
	streets->createMap();
	glewInit();

	if (glewIsSupported("GL_VERSION_2_0"))
		printf("OpenGL 2.0 supported.\n");
	else {
		printf("OpenGL 2.0 not supported !\n");
		exit(1);
	}
	setShaders();
}

Render::~Render() {
	delete (streets);
	delete (skybox);
	delete (camera);
}

void Render::display(float dTime)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	std::ostringstream oss;
	float textColor[3] = {1.0f, 1.0f, 1.0f};


	frame++;
	time=glutGet(GLUT_ELAPSED_TIME);
	if (time - timebase > 1000) {
		oss << "Procedural City - FPS: " << frame*1000.0/(time-timebase);
		fpsInfo = oss.str();
		timebase = time;
		frame = 0;
	}

	glEnable(GL_NORMALIZE);
	glutSetWindowTitle(fpsInfo.c_str());
	glPushMatrix();
		setCamera();
		glUseProgram(cubemap);
		skybox->drawBox();
		glUseProgram(0);
		glPushMatrix();
		glScalef(0.05, 0.05, 0.05);
		setupLights();
		glUseProgram(tex);
		streets->render();
		glUseProgram(0);
		glPopMatrix();

	glPopMatrix();




}

void Render::reshape(int width, int height) {
	winWidth = width;
	winHeight = height;
	midWindowX = winWidth/2;
	midWindowY = winHeight/2;
	glViewport(0, 0, winWidth, winHeight);
}

void Render::mouseButtonPress(int button, int state, int x, int y) {
	//printf("MouseButtonPress: x: %d y: %d\n", x, y);
	if (state == GLUT_DOWN)
	{
		if (button == GLUT_LEFT_BUTTON)
		{
			mouseLeftDown = true;
			camera->Fly(-1);
		}

		else if (button == GLUT_RIGHT_BUTTON)
		{
			mouseRightDown = true;
			camera->Fly(1);
		}

	}
	else if (state == GLUT_UP)
	{
		if (button == GLUT_LEFT_BUTTON)
			mouseLeftDown = false;
		else if (button == GLUT_RIGHT_BUTTON)
			mouseRightDown = false;
	}
}

void Render::mouseMovePassive(int x, int y) {
	//printf("MouseMove: x: %d y: %d\n", x, y);

    // This variable is hack to stop glutWarpPointer from triggering an event callback to Mouse(...)
    // This avoids it being called recursively and hanging up the event loop
    static bool just_warped = false;

    if(just_warped) {
        just_warped = false;
        return;
    }

	int dx = x - winWidth/2;
	int dy = y - winHeight/2;

	if(dx) {
		camera->RotateYaw(dx);
	}

	if(dy) {
		camera->RotatePitch(-dy);
	}

	// Reset the mouse position to the centre of the window each frame
	glutWarpPointer(midWindowX, midWindowY);

	just_warped = true;

}

void Render::keyboardDown( unsigned char key, int x, int y )
{
	/*  Exit on ESC */
	//printf( "KeyboardDown: %c = %d\n", key, (int)key );
	if (key==27) { //27 =- ESC key
		exit (0);
	}
	switch (key)
	{
	case 'z': zoom -= 0.1; break;
	case 'x': zoom += 0.1; break;
	case 'w': camera->Move(1); break;
	case 's': camera->Move(-1); break;
	case 'a': camera->Strafe(1); break;
	case 'd': camera->Strafe(-1); break;

	}
	keyStates.keyDown( (int)key );
}

void Render::keyboardUp( unsigned char key, int x, int y )
{
	// Subclass and override this method
	//printf( "KeyboardUp: %c \n", key );
	keyStates.keyUp( (int)key );
}

void Render::specialKeyboardDown( int key, int x, int y )
{
	// Subclass and override this method
	keyDown = key;
	//printf( "SpecialKeyboardDown: %d\n", key );
}

void Render::specialKeyboardUp( int key, int x, int y )
{
	// Subclass and override this method
	keyDown = 0;
	//printf( "SpecialKeyboardUp: %d \n", key );
}


void Render::setOrtho2D()
{
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluOrtho2D(0, winWidth, 0, winHeight);
}

void Render::setCamera()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(G308_FOVY, (double) winWidth / (double) winHeight, G308_ZNEAR_3D, G308_ZFAR_3D);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	camera->Refresh();
}

void Render::rotTh(int v)
{
	this->th += v;
	this->th = th%360;
}

void Render::setupLights() {

	//ambient
	float ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	float specular[] ={ 1.0f, 1.0f, 1.0f, 1.0f };
	float position[] = { 20.0f, 30.0f, 10.0f, 1.0f };

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, position);


	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
		glEnable(GL_DEPTH_TEST);
//		glEnable(GL_COLOR_MATERIAL);

}

void Render::setShaders()
{

	phong = createProgram("shaders/phong.frag", "shaders/phong.vert");
	tex = createProgram("shaders/phong_tex.frag", "shaders/phong_tex.vert");
//	bump = createProgram("shaders/phong_bump.frag", "shaders/phong_bump.vert");
	cubemap = createProgram("shaders/skybox.frag", "shaders/skybox.vert");
//	reflection = createProgram("shaders/phong_reflection.frag", "shaders/phong_reflection.vert");

}


