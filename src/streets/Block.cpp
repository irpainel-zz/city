/*
 * Block.cpp
 *
 *  Created on: Oct 4, 2014
 *      Author: Iury Roger Painelli
 */

#include "Block.h"

Block::Block(glm::vec3 s, glm::vec3 e) {
	start = s;
	end = e;
	intersections = 0;
	blockDL = 0;
	width = end.x - start.x;
	length = end.z - start.z;

	buildings.reserve(10);

}

Block::~Block() {
	// TODO Auto-generated destructor stub
}

glm::vec3 Block::getStart()
{
	return this->start;
}

glm::vec3 Block::getEnd()
{
	return this->end;
}


int Block::generateBlock()
{
	unsigned int i;
	coord c;

	//split building lots
	splitBlock();

	blockDL = glGenLists(1);
	glNewList(blockDL, GL_COMPILE);
		glColor3f(0.0f, 1.0f, 0.0f);
		glBegin(GL_QUADS);
//			printf ("0: (%f,%f) \n", start.x , start.z);
			glVertex3f(0.f , 0.f, 0.f);
//			printf ("1: (%f,%f) \n", end.x , start.z);
			glVertex3f(width, 0.f, 0.f);
//			printf ("2: (%f,%f) \n", end.x , end.z);
			glVertex3f(width, 0.f, length);
//			printf ("3: (%f,%f) \n", start.x , end.z);
			glVertex3f(0.f, 0.f, length);
		glEnd();
		for (i = 0; i < buildings.size(); ++i) {
			c = lotCoords[i];
			glPushMatrix();
				glTranslatef(c.start.x+c.width/2.f, 0.0, c.start.z+c.length/2.f);
				buildings[i]->drawBuilding();
			glPopMatrix();
		}
	glEndList();
	check_gl_error();
	return (int) buildings.size();
}

void Block::splitBlock()
{
	vector<float> x;
	vector<float> z;
	float sumX = 0;
	float sumZ = 0;
	int rand;
	unsigned int i;
	unsigned int j;

	//insert coord 0 in x
	x.push_back(sumX);
	while (sumX < width)
	{
		rand = Random::generateRandom(1, 5);
		if (sumX+rand*10 > (width - 30))
			sumX = width;
		else
			sumX += rand*10;
		x.push_back(sumX);
	}

	//insert coord 0 in z
	z.push_back(sumZ);
	while (sumZ < length)
	{
		rand = Random::generateRandom(1, 5);
		if (sumZ+rand*10 > (length - 30))
			sumZ = length;
		else
			sumZ += rand*10;
		z.push_back(sumZ);
	}
	for (i = 0; i < x.size()-1; i++)
	{
		for (j = 0; j < z.size()-1; ++j) {
			coord tempCoord;
			tempCoord.start.x = x[i];
			tempCoord.start.y = 0.0;
			tempCoord.start.z = z[j];
			tempCoord.end.x = x[i+1];
			tempCoord.end.y = 0.0;
			tempCoord.end.z = z[j+1];
			tempCoord.width = x[i+1] - x[i];
			tempCoord.length = z[j+1] - z[j];
//			printf (" (%f,%f) (%f,%f)\n", x[i], z[j], x[i+1], z[j+1]);
			lotCoords.push_back(tempCoord);
			newBuilding(tempCoord.width, tempCoord.length);

		}
	}
}

void Block::newBuilding(float width, float length)
{
	Building * tempBuilding;
	float height = Random::generateRandom(1, 10)*10;
	tempBuilding = new Building(width, length, height);
	tempBuilding->generateBuilding();
	buildings.push_back(tempBuilding);
}


void Block::renderBlock()
{
	glCallList(blockDL);
}
