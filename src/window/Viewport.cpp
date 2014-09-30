/*
 * Viewport.cpp
 *
 *  Created on: Aug 29, 2014
 *      Author: Iury Roger Painelli
 */

#include "Viewport.h"

using namespace glutFramework;

Viewport::Viewport() {
	// TODO Auto-generated constructor stub

}

Viewport::~Viewport() {
	// TODO Auto-generated destructor stub
}

/*
 * drawAxes()
 * ------
 * Draw the axes
 */
void Viewport::drawAxes(int toggleAxes)
{
  if (toggleAxes) {
    /*  Length of axes */
    double len = 10000.0;
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_LINES);
    glVertex3d(-len,0,0);
    glVertex3d(len,0,0);
    glEnd();
    glColor3f(0.0,1.0,0.0);
    glBegin(GL_LINES);
    glVertex3d(0,-len,0);
    glVertex3d(0,len,0);
    glEnd();
    glColor3f(0.0,0.0,1.0);
    glBegin(GL_LINES);
    glVertex3d(0,0,-len);
    glVertex3d(0,0,len);
    glEnd();
  }
}

/*
 *  drawFloor()
 *  ------
 *  Draw the floor
 */
void Viewport::drawFloor(int toggleFloor)
{
	if (toggleFloor)
	{
	  

		glEnable (GL_BLEND);
		glBlendFunc (GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

		glPushMatrix();
		glColor4f(0,0.2,0.2,0.5);
		glTranslated(0, -0.05, 0);
		glScalef(10, 0.1, 10);
		glutSolidCube(1);
		glPopMatrix();
		
		glDisable (GL_BLEND);
	}
}

void Viewport::RenderString(float x, float y, void *font, const char* string, float* rgb)
{
	int i=0, len;

	glColor3f(rgb[0], rgb[1], rgb[2]);
	glRasterPos2f(x, y);

	len = strlen(string);
	while(i < len){
	   glutBitmapCharacter(font, string[i]);
	   i++;
	}
}
