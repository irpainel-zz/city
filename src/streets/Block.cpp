/*
 * Block.cpp
 *
 *  Created on: Oct 4, 2014
 *      Author: Iury Roger Painelli
 */

#include "Block.h"

Block::Block(glm::vec3 s, glm::vec3 e, int centreDistance, int isPark) {
	start = s;
	end = e;
	intersections = 0;
	this->centreDistance = centreDistance;
	this->isPark = isPark;
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
	float rand = (Random::generateRandom(0, 10)+1)*10;

	if (isPark)
	{
		compilePark();
	}
	else
	{
		if (rand  > centreDistance)
		{
			newBuildingBlock();
			compileBuildings();
		}
		else
		{
			newResidentialBlock();
			compileBuildings();
		}
	}


	check_gl_error();
	return (int) buildings.size();
}

void Block::compilePark()
{

	blockDL = glGenLists(1);
	glNewList(blockDL, GL_COMPILE);
		drawBlockFloor();
	glEndList();
}
void Block::compileBuildings()
{
	unsigned int i;
	coord c;

	blockDL = glGenLists(1);
	glNewList(blockDL, GL_COMPILE);
		drawBlockFloor();
		for (i = 0; i < buildings.size(); ++i) {
			c = lotCoords[i];
			glPushMatrix();
				glTranslatef(c.start.x+c.width/2.f, 0.0, c.start.z+c.length/2.f);
				buildings[i]->drawBuilding();
			glPopMatrix();
		}
	glEndList();
}

void Block::drawBlockFloor()
{
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_QUADS);
		glVertex3f(0.f , 0.f, 0.f);
		glVertex3f(width, 0.f, 0.f);
		glVertex3f(width, 0.f, length);
		glVertex3f(0.f, 0.f, length);
	glEnd();
}
void Block::newResidentialBlock()
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
	float sizeLot = width / 2;
	sumX = sizeLot;
	while (sumX <= width)
	{
		x.push_back(sumX);
		sumX += sizeLot;

	}

	//insert coord 0 in z
	z.push_back(sumZ);
	rand = length / 5;
	sumZ = rand;
	while (sumZ <= length)
	{
		z.push_back(sumZ);
		sumZ+=rand;
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
			lotCoords.push_back(tempCoord);
			newHouse(tempCoord.width, tempCoord.length);
		}
	}
}

void Block::newBuildingBlock()
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
			//printf (" (%f,%f) (%f,%f)\n", x[i], z[j], x[i+1], z[j+1]);
			lotCoords.push_back(tempCoord);
			newBuilding(tempCoord.width, tempCoord.length);

		}
	}
}

void Block::newHouse(float width, float length)
{
	Building * tempBuilding;
	float height;
	//random 1 - 3
	float stories = (Random::generateRandom(0, 3)+1);
	height = 2.5 * stories;
	tempBuilding = new Building(width, length, height);
	tempBuilding->generateBuilding();
	buildings.push_back(tempBuilding);
}

void Block::newBuilding(float width, float length)
{
	Building * tempBuilding;
	float height;
	//random 0 - 100;
	float rand = (Random::generateRandom(0, 10)+1)*10;
	//printf("change of a short building: %d, rand got %f\n", centreDistance, rand);
	if (rand  > centreDistance)
	{
		rand = (Random::generateRandom(0, 10)+1);
		if (rand < 6)
			height = Random::generateRandom(4, 10)*10;
		else
			height = Random::generateRandom(1, 3)*10;
	}
	else
	{
		height = Random::generateRandom(1, 3)*10;
	}

	tempBuilding = new Building(width, length, height);
	tempBuilding->generateBuilding();
	buildings.push_back(tempBuilding);
}


void Block::renderBlock()
{
	glCallList(blockDL);
}
