/*
 * Building.cpp
 *
 *  Created on: Oct 4, 2014
 *      Author: Iury Roger Painelli
 */

#include "Building.h"

Building::Building(float w, float l, float h) {
	this->width = w;
	this->length = l;
	this->height = h;
	buildingDL = 0;

}

Building::~Building() {
	glDeleteLists(buildingDL, 1);
}

void Building::generateBuilding()
{
	float r, g, b;
	r = Random::generateRandom(0, 10)/10.f;
	g = Random::generateRandom(0, 10)/10.f;
	b = Random::generateRandom(0, 10)/10.f;
	buildingDL = glGenLists(1);
	glNewList(buildingDL, GL_COMPILE);
		glColor3f(r, g, b);
		glPushMatrix();
			glTranslatef(0.0f, height/2.f, 0.0f);
			glScalef((width)/2, height, (length)/2);
			glutSolidCube(1);
		glPopMatrix();
	glEndList();
}

void Building::drawBuilding()
{
	glCallList(buildingDL);
}
