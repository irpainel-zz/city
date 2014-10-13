/*
 * Building.cpp
 *
 *  Created on: Oct 11, 2014
 *      Author: Iury Roger Painelli
 */

#include <Building.h>

Building::Building(float w, float l, float h, textures t) : Construction(w, l, h, t) {
	// TODO Auto-generated constructor stub

}

Building::~Building() {
	// TODO Auto-generated destructor stub
}


void Building::generateConstruction()
{
	float r, g, b;
	r = Random::generateRandom(0, 10)/10.f;
	g = Random::generateRandom(0, 10)/10.f;
	b = Random::generateRandom(0, 10)/10.f;
	ConstructionDL = glGenLists(1);
	glNewList(ConstructionDL, GL_COMPILE);
		glColor3f(r, g, b);
		glPushMatrix();
			glTranslatef(0.0f, height/2.f, 0.0f);
			glScalef((width)/2, height, (length)/2);
			glutSolidCube(1);
		glPopMatrix();
	glEndList();
}
