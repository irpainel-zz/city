/*
 * Render.h
 *
 *  Created on: Aug 29, 2014
 *      Author: Iury Roger Painelli
 */

#ifndef RENDER_H_
#define RENDER_H_


#include "GlutFramework.h"
#include "Viewport.h"
#include "Streets.h"

using namespace glutFramework;

#define CTRL_BTN 114
#define SHIFT_BTN 112

class Render : public GlutFramework {
public:
	Render();
	virtual ~Render();

	/*  Toggles */
	int toggleAxes;   /* toggle axes on and off */

	//virtual void load();

	void display(float dTime);
	void reshape(int width, int height);

	/** Called when the mouse buttons are pressed.
	 @param button - the mouse buttons
	 @param state - the state of the buttons
	 @param x - the x coordinate
	 @param y - the y coordinate
	 */
	void mouseButtonPress(int button, int state, int x, int y);

	/** Called when the mouse moves on the screen.
	 @param x - the x coordinate
	 @param y - the y coordinate
	 */
	void mouseMove(int x, int y);

	/** The keyboard function is called when a standard key is pressed down.
	 @param key - the key press
	 @param x - the x coordinate of the mouse
	 @param y - the y coordinate of the mouse
	 */
	void keyboardDown( unsigned char key, int x, int y );

	/** The keyboard function is called when a standard key is "unpressed".
	 @param key - the key press
	 @param x - the x coordinate of the mouse
	 @param y - the y coordinate of the mouse
	 */
	void keyboardUp( unsigned char key, int x, int y );

	/** The keyboard function is called when a special key is pressed down.
	 (F1 keys, Home, Inser, Delete, Page Up/Down, End, arrow keys)
	 http://www.opengl.org/resources/libraries/glut/spec3/node54.html
	 @param key - the key press
	 @param x - the x coordinate of the mouse
	 @param y - the y coordinate of the mouse
	 */
	void specialKeyboardDown( int key, int x, int y );

	/** The keyboard function is called when a special key is "unpressed.
	 (F1 keys, Home, Inser, Delete, Page Up/Down, End, arrow keys)
	 @param key - the key press
	 @param x - the x coordinate of the mouse
	 @param y - the y coordinate of the mouse
	 */
	void specialKeyboardUp( int key, int x, int y );

	void setupLights();

	void setOrtho2D();
	void setCamera();

	void rotTh(int v);

private:

	/*  Display view */
	int th;  /* azimuth of view angle */
	float zoom;
	//keyboard key
	int keyDown;

	int winWidth, winHeight;

	Streets * streets;

};


#endif /* RENDER_H_ */
