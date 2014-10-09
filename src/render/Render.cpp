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

	glEnable(GL_CULL_FACE);

}

Render::~Render() {
	delete (streets);
}

void Render::display(float dTime)
{
	std::ostringstream oss;
	float textColor[3] = {1.0f, 1.0f, 1.0f};
	if (streets == NULL)
	{
		streets = new Streets(1000, 1000);
		streets->createMap();
	}

	frame++;
	time=glutGet(GLUT_ELAPSED_TIME);
	if (time - timebase > 1000) {
		oss << "Procedural City - FPS: " << frame*1000.0/(time-timebase);
		fpsInfo = oss.str();
		timebase = time;
		frame = 0;
	}

//	glutSolidTeapot(1);
	glEnable(GL_NORMALIZE);
//	glPushMatrix();
//		glMatrixMode( GL_PROJECTION );
//		glLoadIdentity();
//		gluOrtho2D(0, winWidth, 0, winHeight);
//		Viewport::RenderString(5.0f, 5.0f, GLUT_BITMAP_TIMES_ROMAN_24, fpsInfo.c_str(), textColor);
//		glMatrixMode( GL_MODELVIEW );
//	glPopMatrix();
	glutSetWindowTitle(fpsInfo.c_str());
	glPushMatrix();
		setCamera();
		glScalef(0.05, 0.05, 0.05);
		setupLights();
		glColor3f(0.5,0.5,0.5);
		streets->render();
		Viewport::drawAxes(1);

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
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glShadeModel(GL_SMOOTH);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(G308_FOVY, (double) winWidth / (double) winHeight, G308_ZNEAR_3D, G308_ZFAR_3D);
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();

//
//	gluLookAt(eyeVector.x, eyeVector.y, eyeVector.z,
//			  centerVector.x, centerVector.y, centerVector.z,
//			  upVector.x, upVector.y, upVector.z);
	camera->Refresh();
}

void Render::rotTh(int v)
{
	this->th += v;
	this->th = th%360;
}

void Render::setupLights() {

	float direction[] = { 1.0f, 1.0f, 1.0f, 0.0f };
	float diffintensity[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	float ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };

	glLightfv(GL_LIGHT0, GL_POSITION, direction);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffintensity);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

	glEnable(GL_LIGHT0);

}

