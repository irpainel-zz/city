/*
 * House.cpp
 *
 *  Created on: Oct 11, 2014
 *      Author: Iury Roger Painelli
 */

#include "House.h"

House::House(float w, float l, float h) : Construction(w, l, h) {
	storyHeight = 2.5f;
	nStories = floor(h / storyHeight);
}

House::~House() {
}

void House::generateConstruction()
{
	float r, g, b;
	int i;
	bool first = true;
	r = Random::generateRandom(0, 10)/10.f;
	g = Random::generateRandom(0, 10)/10.f;
	b = Random::generateRandom(0, 10)/10.f;
	ConstructionDL = glGenLists(1);
	glNewList(ConstructionDL, GL_COMPILE);
		glColor3f(r, g, b);
		for (i =0; i < nStories; i++)
		{
			glPushMatrix();
			glTranslatef(0.0f, storyHeight*i, 0.0f);
			drawFloor(first);
			first = false;
			glPopMatrix();
		}
		glPushMatrix();
			glTranslatef(0.f, height, 0.f);
			glScalef((width)/2, height, (length)/2);
			glRotatef(90, 0.f, 1.f, 0.f);
			drawRoof();
		glPopMatrix();
	glEndList();
}

void House::drawFloor(bool isFirst)
{
	float r, g, b;
	glPushMatrix();
		glScalef((width)/2, 1.f, (length)/2);
		drawWalls();
	glPopMatrix();
	r = Random::generateRandom(0, 10)/10.f;
	g = Random::generateRandom(0, 10)/10.f;
	b = Random::generateRandom(0, 10)/10.f;
	glColor3f(r, g, b);
	glPushMatrix();
		glTranslatef(width/4.f, 0.f, 0.f);
		glPushMatrix();
			glTranslatef(0.f, 0.f, length/8.f);
			drawWindow();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.f, 0.f, -length/8.f);
			drawWindow();
		glPopMatrix();
		if (isFirst)
			drawDoor();
	glPopMatrix();
	glPushMatrix();
		glRotatef(180, 0.f, 1.f, 0.f);
		glTranslatef(width/4.f, 0.f, 0.f);
		glPushMatrix();
			glTranslatef(0.f, 0.f, length/8.f);
			drawWindow();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.f, 0.f, -length/8.f);
			drawWindow();
		glPopMatrix();
		if (isFirst)
			drawDoor();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.f, 0.f, length/4.f);
		glPushMatrix();
			glTranslatef(width/8.f, 0.f, 0.f);
			glRotatef(270, 0.f, 1.f, 0.f);
			drawWindow();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-width/8.f, 0.f, 0.f);
			glRotatef(270, 0.f, 1.f, 0.f);
			drawWindow();
		glPopMatrix();
	glPopMatrix();
	glPushMatrix();
		glRotatef(180, 0.f, 1.f, 0.f);
		glTranslatef(0.f, 0.f, length/4.f);
		glPushMatrix();
			glTranslatef(width/8.f, 0.f, 0.f);
			glRotatef(270, 0.f, 1.f, 0.f);
			drawWindow();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-width/8.f, 0.f, 0.f);
			glRotatef(270, 0.f, 1.f, 0.f);
			drawWindow();
		glPopMatrix();
	glPopMatrix();
}

void House::drawWalls()
{
	float wSize = 0.5;
	float wHeight = storyHeight;
	int i, angle = 0;
	for (i = 0; i < 4; ++i) {
		glPushMatrix();
			glRotatef(angle, 0.f, 1.f, 0.f);
			glBegin(GL_QUADS);
				glNormal3f(0.f, 0.f, 1.f);
				glTexCoord2f(0.f, 0.f); glVertex3f(-wSize, 0.f, -wSize);
				glTexCoord2f(1.f, 0.f); glVertex3f(wSize, 0.f, -wSize);
				glTexCoord2f(1.f, 1.f); glVertex3f(wSize, wHeight,  -wSize);
				glTexCoord2f(0.f, 1.f); glVertex3f(-wSize, wHeight, -wSize);
			glEnd();
		glPopMatrix();
		angle += 90;
	}
}

void House::drawRoof()
{
	float rSize = 0.5;
	glBegin(GL_QUADS);
		glNormal3f(-0.7071, 0.7071, 0.f); glTexCoord2f(0.f, 0.f); glVertex3f(-rSize, 0.0, -rSize);
		glNormal3f(-0.7071, 0.7071, 0.f); glTexCoord2f(1.f, 0.f); glVertex3f(0.0, rSize, -rSize);
		glNormal3f(-0.7071, 0.7071, 0.f); glTexCoord2f(1.f, 1.f); glVertex3f(0.0, rSize,  rSize);
		glNormal3f(-0.7071, 0.7071, 0.f); glTexCoord2f(0.f, 1.f); glVertex3f(-rSize, 0.0,  rSize);
	glEnd();
	glBegin(GL_QUADS);
		glNormal3f(0.7071, 0.7071, 0.f); glTexCoord2f(0.f, 1.f); glVertex3f(0.0, rSize, -rSize);
		glNormal3f(0.7071, 0.7071, 0.f); glTexCoord2f(1.f, 1.f); glVertex3f(rSize, 0.0, -rSize);
		glNormal3f(0.7071, 0.7071, 0.f); glTexCoord2f(1.f, 0.f); glVertex3f(rSize, 0.0,  rSize);
		glNormal3f(0.7071, 0.7071, 0.f); glTexCoord2f(0.f, 0.f); glVertex3f(0.0, rSize,  rSize);
	glEnd();
	glBegin(GL_TRIANGLES);
		glNormal3f(0.f, 0.f, -1.f); glVertex3f(-rSize, 0.0, -rSize);
		glNormal3f(0.f, 0.f, -1.f); glVertex3f(0.0,  rSize, -rSize);
		glNormal3f(0.f, 0.f, -1.f); glVertex3f(rSize,  0.0, -rSize);
	glEnd();
	glBegin(GL_TRIANGLES);
		glNormal3f(0.f, 0.f, 1.f); glVertex3f(-rSize, 0.0, rSize);
		glNormal3f(0.f, 0.f, 1.f); glVertex3f(0.0,  rSize, rSize);
		glNormal3f(0.f, 0.f, 1.f); glVertex3f(rSize,  0.0, rSize);
	glEnd();
}

void House::drawDoor()
{
	float dSize = 0.5;
	float dHeight = 2.f;
	glBegin(GL_QUADS);
		glNormal3f(1.f, 0.f, 0.f); glTexCoord2f(0.f, 0.f); glVertex3f(0.01f, 0.f, -dSize);
		glNormal3f(1.f, 0.f, 0.f); glTexCoord2f(1.f, 0.f); glVertex3f(0.01f, 0.f, dSize);
		glNormal3f(1.f, 0.f, 0.f); glTexCoord2f(1.f, 1.f); glVertex3f(0.01f, dHeight,  dSize);
		glNormal3f(1.f, 0.f, 0.f); glTexCoord2f(0.f, 1.f); glVertex3f(0.01f, dHeight, -dSize);
	glEnd();
}

void House::drawWindow()
{
	float dSize = 0.8f;
	float distFloor = 1.0f;
	float dHeight = 1.f + distFloor;
	glBegin(GL_QUADS);
		glNormal3f(0.f, 0.f, 1.f); glTexCoord2f(0.f, 0.f); glVertex3f(0.01f, distFloor, -dSize);
		glNormal3f(0.f, 0.f, 1.f); glTexCoord2f(1.f, 0.f); glVertex3f(0.01f, distFloor, dSize);
		glNormal3f(0.f, 0.f, 1.f); glTexCoord2f(1.f, 1.f); glVertex3f(0.01f, dHeight,  dSize);
		glNormal3f(0.f, 0.f, 1.f); glTexCoord2f(0.f, 1.f); glVertex3f(0.01f, dHeight, -dSize);
	glEnd();
}
