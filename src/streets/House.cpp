/*
 * House.cpp
 *
 *  Created on: Oct 11, 2014
 *      Author: Iury Roger Painelli
 */

#include "House.h"

House::House(float w, float l, float h, textures t) : Construction(w-5.f, l-1.f, h, t) {
	storyHeight = 2.5f;
	nStories = floor(h / storyHeight);
	texWindow = gTextures.window[(Random::generateRandom(0, gTextures.window.size()))];
	texDoor = gTextures.door[(Random::generateRandom(0, gTextures.door.size()))];
	texWall = gTextures.wall[(Random::generateRandom(0, gTextures.wall.size()))];
	texRoof = gTextures.roof[(Random::generateRandom(0, gTextures.roof.size()))];
}

House::~House() {
}

void House::generateConstruction()
{
	int i;
	bool first = true;
	ConstructionDL = glGenLists(1);
	glNewList(ConstructionDL, GL_COMPILE);
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
			glScalef((width), height, (length));
			glRotatef(90, 0.f, 1.f, 0.f);
			drawRoof();
		glPopMatrix();
	glEndList();
}

void House::drawFloor(bool isFirst)
{
	glPushMatrix();
		glScalef((width), 1.f, (length));
		drawWalls();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(width/2.f, 0.f, 0.f);
		glPushMatrix();
			glTranslatef(0.f, 0.f, length/4.f);
			drawWindow();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.f, 0.f, -length/4.f);
			drawWindow();
		glPopMatrix();
		if (isFirst)
			drawDoor();
	glPopMatrix();
	glPushMatrix();
		glRotatef(180, 0.f, 1.f, 0.f);
		glTranslatef(width/2.f, 0.f, 0.f);
		glPushMatrix();
			glTranslatef(0.f, 0.f, length/4.f);
			drawWindow();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.f, 0.f, -length/4.f);
			drawWindow();
		glPopMatrix();
		if (isFirst)
			drawDoor();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.f, 0.f, length/2.f);
		glPushMatrix();
			glTranslatef(width/4.f, 0.f, 0.f);
			glRotatef(270, 0.f, 1.f, 0.f);
			drawWindow();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-width/4.f, 0.f, 0.f);
			glRotatef(270, 0.f, 1.f, 0.f);
			drawWindow();
		glPopMatrix();
	glPopMatrix();
	glPushMatrix();
		glRotatef(180, 0.f, 1.f, 0.f);
		glTranslatef(0.f, 0.f, length/2.f);
		glPushMatrix();
			glTranslatef(width/4.f, 0.f, 0.f);
			glRotatef(270, 0.f, 1.f, 0.f);
			drawWindow();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-width/4.f, 0.f, 0.f);
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


	glm::vec4 ambient = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);
	glm::vec4 diffuse = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);
	glm::vec4 specular = glm::vec4(0.f, 0.0f, 0.0f, 1.f);
	float shininess = 80;

	glMaterialfv(GL_FRONT, GL_AMBIENT, &ambient[0]);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, &diffuse[0]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, &specular[0]);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);

	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, texWall);
	for (i = 0; i < 4; ++i) {
		glPushMatrix();
			glRotatef(angle, 0.f, 1.f, 0.f);
			glBegin(GL_QUADS);
				glNormal3f(0.f, 0.f, -1.f);
				glTexCoord2f(0.f, 0.f); glVertex3f(-wSize, 0.f, -wSize);
				glTexCoord2f(10.f, 0.f); glVertex3f(wSize, 0.f, -wSize);
				glTexCoord2f(10.f, 2.f); glVertex3f(wSize, wHeight,  -wSize);
				glTexCoord2f(0.f, 2.f); glVertex3f(-wSize, wHeight, -wSize);
			glEnd();
		glPopMatrix();
		angle += 90;
	}
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void House::drawRoof()
{
	float rSize = 0.5;
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, texRoof);

	glBegin(GL_QUADS);
		glNormal3f(-0.7071, 0.7071, 0.f); glTexCoord2f(0.f, 0.f); glVertex3f(-rSize, 0.0, -rSize);
		glNormal3f(-0.7071, 0.7071, 0.f); glTexCoord2f(0.f, 2.f); glVertex3f(0.0, rSize, -rSize);
		glNormal3f(-0.7071, 0.7071, 0.f); glTexCoord2f(2.f, 2.f); glVertex3f(0.0, rSize,  rSize);
		glNormal3f(-0.7071, 0.7071, 0.f); glTexCoord2f(2.f, 0.f); glVertex3f(-rSize, 0.0,  rSize);
	glEnd();
	glBegin(GL_QUADS);
		glNormal3f(0.7071, 0.7071, 0.f); glTexCoord2f(2.f, 0.f); glVertex3f(0.0, rSize, -rSize);
		glNormal3f(0.7071, 0.7071, 0.f); glTexCoord2f(2.f, 2.f); glVertex3f(rSize, 0.0, -rSize);
		glNormal3f(0.7071, 0.7071, 0.f); glTexCoord2f(0.f, 2.f); glVertex3f(rSize, 0.0,  rSize);
		glNormal3f(0.7071, 0.7071, 0.f); glTexCoord2f(0.f, 0.f); glVertex3f(0.0, rSize,  rSize);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texWall);
	glBegin(GL_TRIANGLES);
		glNormal3f(0.f, 0.f, -1.f); glTexCoord2f(0.f, 0.f); glVertex3f(-rSize, 0.0, -rSize);
		glNormal3f(0.f, 0.f, -1.f); glTexCoord2f(5.f, 2.f); glVertex3f(0.0,  rSize, -rSize);
		glNormal3f(0.f, 0.f, -1.f); glTexCoord2f(10.f, 0.f); glVertex3f(rSize,  0.0, -rSize);
	glEnd();
	glBegin(GL_TRIANGLES);
		glNormal3f(0.f, 0.f, 1.f); glTexCoord2f(0.f, 0.f); glVertex3f(-rSize, 0.0, rSize);
		glNormal3f(0.f, 0.f, 1.f); glTexCoord2f(5.f, 2.f); glVertex3f(0.0,  rSize, rSize);
		glNormal3f(0.f, 0.f, 1.f); glTexCoord2f(10.f, 0.f); glVertex3f(rSize,  0.0, rSize);
	glEnd();
}

void House::drawDoor()
{
	float dSize = 0.5;
	float dHeight = 2.f;
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, texDoor);

	glBegin(GL_QUADS);
		glNormal3f(1.f, 0.f, 0.f); glTexCoord2f(0.f, 0.f); glVertex3f(0.01f, 0.f, -dSize);
		glNormal3f(1.f, 0.f, 0.f); glTexCoord2f(1.f, 0.f); glVertex3f(0.01f, 0.f, dSize);
		glNormal3f(1.f, 0.f, 0.f); glTexCoord2f(1.f, 1.f); glVertex3f(0.01f, dHeight,  dSize);
		glNormal3f(1.f, 0.f, 0.f); glTexCoord2f(0.f, 1.f); glVertex3f(0.01f, dHeight, -dSize);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void House::drawWindow()
{
	float dSize = 0.8f;
	float distFloor = 1.0f;
	float dHeight = 1.f + distFloor;

	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, texWindow);

	glBegin(GL_QUADS);
		glNormal3f(0.f, 0.f, 1.f); glTexCoord2f(0.f, 0.f); glVertex3f(0.01f, distFloor, -dSize);
		glNormal3f(0.f, 0.f, 1.f); glTexCoord2f(1.f, 0.f); glVertex3f(0.01f, distFloor, dSize);
		glNormal3f(0.f, 0.f, 1.f); glTexCoord2f(1.f, 1.f); glVertex3f(0.01f, dHeight,  dSize);
		glNormal3f(0.f, 0.f, 1.f); glTexCoord2f(0.f, 1.f); glVertex3f(0.01f, dHeight, -dSize);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

}
