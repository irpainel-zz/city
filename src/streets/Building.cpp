/*
 * Building.cpp
 *
 *  Created on: Oct 11, 2014
 *      Author: Iury Roger Painelli
 */

#include <Building.h>

Building::Building(float w, float l, float h, textures t) : Construction(w, l, h, t) {
	// TODO Auto-generated constructor stub
	storeyHeight = 2.5;
	num_stories = w / storeyHeight;
	texBuilding = gTextures.building[Random::generateRandom(0, gTextures.building.size())];

}

Building::~Building() {
	// TODO Auto-generated destructor stub
}


void Building::generateConstruction()
{
//	float r, g, b;
//	r = Random::generateRandom(0, 10)/10.f;
//	g = Random::generateRandom(0, 10)/10.f;
//	b = Random::generateRandom(0, 10)/10.f;
	ConstructionDL = glGenLists(1);
	glNewList(ConstructionDL, GL_COMPILE);
		for(int i = 0; i < num_stories; i++) {
			glPushMatrix();
				glTranslatef(0.0, storeyHeight * i, 0.0);
				drawBuilding(false);
			glPopMatrix();
		}
//		glColor3f(r, g, b);
//		glPushMatrix();
//			glTranslatef(0.0f, height/2.f, 0.0f);
//			glScalef((width)/2, height, (length)/2);
//			glutSolidCube(1);
//		glPopMatrix();
	glEndList();
}

void Building::drawBuilding(bool firstStorey) {
	glPushMatrix();
		glScalef((width)/2, 1.f, (length)/2);
		drawWallTex();
	glPopMatrix();
}

void Building::drawWallTex() {
	int angle = 1;
	float wsize = 0.5;

	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, texBuilding);

	for(int i = 0; i < 4; i++) {
		glPushMatrix();
			glRotatef(angle, 0.0, 1.0, 0.0);
			glBegin(GL_QUADS);
				glNormal3f(0.0, 0.0, -1.0);
				glTexCoord2f(0.0, 0.0); glVertex3f(-wsize, 0.0, -wsize);
				glTexCoord2f(1.0, 0.0); glVertex3f(wsize, 0.0, -wsize);
				glTexCoord2f(1.0, 1.0); glVertex3f(wsize, storeyHeight, -wsize);
				glTexCoord2f(0.0, 1.0); glVertex3f(-wsize, storeyHeight, -wsize);
			glEnd();
		glPopMatrix();
		angle += 90;
	}

	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
}
