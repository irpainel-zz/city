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

	winWidth = 0;
	winHeight = 0;

	streets = new Streets(1000, 1000);

}

Render::~Render() {
}

void Render::display(float dTime)
{
//	glutSolidTeapot(1);
	glEnable(GL_NORMALIZE);
	setCamera();
	glPushMatrix();
	glScalef(0.05, 0.05, 0.05);
	glScalef(zoom, zoom, zoom);
	setupLights();
	glColor3f(0.5,0.5,0.5);
	streets->render();
	Viewport::drawAxes(1);
	glPopMatrix();


}

void Render::reshape(int width, int height) {
	winWidth = width;
	winHeight = height;
	glViewport(0, 0, winWidth, winHeight);
}

void Render::mouseButtonPress(int button, int state, int x, int y) {
	//printf("MouseButtonPress: x: %d y: %d\n", x, y);
}

void Render::mouseMove(int x, int y) {
	//printf("MouseMove: x: %d y: %d\n", x, y);

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
	default: break;
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
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(eyeVector.x, eyeVector.y, eyeVector.z,
			  centerVector.x, centerVector.y, centerVector.z,
			  upVector.x, upVector.y, upVector.z);
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
