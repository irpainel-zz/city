/*
 * Block.cpp
 *
 *  Created on: Oct 4, 2014
 *      Author: Iury Roger Painelli
 */

#include "Block.h"

Block::Block(glm::vec3 s, glm::vec3 e, int centreDistance, int isPark, textures t) {
	start = s;
	end = e;
	intersections = 0;
	this->centreDistance = centreDistance;
	this->isPark = isPark;
	blockDL = 0;
	width = end.x - start.x;
	length = end.z - start.z;

	constructions.reserve(10);

	gTextures = t;

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
			compileConstructions();
		}
		else
		{
			newResidentialBlock();
			compileConstructions();
		}
	}


	check_gl_error();
	return (int) constructions.size();
}

void Block::compilePark()
{

	blockDL = glGenLists(1);
	glNewList(blockDL, GL_COMPILE);
		drawBlockFloor();
	glEndList();
}
void Block::compileConstructions()
{
	unsigned int i;
	coord c;

	blockDL = glGenLists(1);
	glNewList(blockDL, GL_COMPILE);
		drawBlockFloor();
		for (i = 0; i < constructions.size(); ++i) {
			c = lotCoords[i];
			glPushMatrix();
				glTranslatef(c.start.x+c.width/2.f, 0.0, c.start.z+c.length/2.f);
				constructions[i]->drawConstruction();
			glPopMatrix();
		}
	glEndList();
}

void Block::drawBlockFloor()
{
	glPushMatrix();

	glm::vec4 ambient = glm::vec4(0.6f, 0.6f, 0.6f, 1.0f);
	glm::vec4 diffuse = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);
	glm::vec4 specular = glm::vec4(0.f, 0.0f, 0.0f, 1.f);
	float shininess = 1;

	glMaterialfv(GL_FRONT, GL_AMBIENT, &ambient[0]);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, &diffuse[0]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, &specular[0]);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, gTextures.grass[(Random::generateRandom(0, gTextures.grass.size()))]);

	glBegin(GL_QUADS);
		glNormal3f(0.f, 1.f, 0.f); glTexCoord2f(0.f, 0.f); glVertex3f(0.f , 0.f, 0.f);
		glNormal3f(0.f, 1.f, 0.f); glTexCoord2f(20.f, 0.f); glVertex3f(width, 0.f, 0.f);
		glNormal3f(0.f, 1.f, 0.f); glTexCoord2f(20.f, 20.f); glVertex3f(width, 0.f, length);
		glNormal3f(0.f, 1.f, 0.f); glTexCoord2f(0.f, 20.f); glVertex3f(0.f, 0.f, length);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	ambient = glm::vec4(0.8f, 0.8f, 0.8f, 1.f);
	diffuse = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);
	specular = glm::vec4(0.f, 0.f, 0.f, 1.f);
	shininess = 20;
	glMaterialfv(GL_FRONT, GL_AMBIENT, &ambient[0]);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, &diffuse[0]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, &specular[0]);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);
	glPopMatrix();
}
void Block::newResidentialBlock()
{
	vector<float> x;
	vector<float> z;
	float startX = 2.5;
	float startZ = 2.5;
	float endX = 2.5;
	float endZ = 2.5;
	int rand;
	unsigned int i;
	unsigned int j;

	cout << " new block" << endl;
	//insert coord 0 in x
//	x.push_back(startX);
	//insert coord 0 in z
//	z.push_back(startZ);
	while (startX < width)
	{
		cout << " new" << endl;
		rand = Random::generateRandom(2, 3);
		if (endX+rand*10 > (width - 20))
			endX = width;
		else
			endX += rand*10;
		printf("sX %f, eX %f \n", startX, endX);
		while (startZ < length)
		{

			coord tempCoord;
			tempCoord.start.x = startX;
			tempCoord.start.y = 0.0;
			tempCoord.start.z = startZ;

			rand = Random::generateRandom(1, 3);
			if (endZ+rand*10 > (length - 10))
				endZ = length;
			else
				endZ += rand*10;

			printf("sX %f, sZ %f, eX %f eZ %f, W %f, L %f \n", startX, startZ, endX, endZ, width, length);
//			z.push_back(startZ);
//			x.push_back(startX);
			tempCoord.end.x = endX;
			tempCoord.end.y = 0.0;
			tempCoord.end.z = startZ;
			tempCoord.width = (endX - startX) - 2.0;
			tempCoord.length = (endZ - startZ) - 2.0;
			lotCoords.push_back(tempCoord);
			newHouse(tempCoord.width, tempCoord.length);
			startZ=endZ;
		}
		endZ = startZ = 2.5;
		startX = endX;
	}

//	//insert coord 0 in x
//	x.push_back(sumX);
//	float sizeLot = width / 2;
//	sumX = sizeLot;
//	while (sumX <= width)
//	{
//		x.push_back(sumX);
//		sumX += sizeLot;
//
//	}

//	//insert coord 0 in z
//	z.push_back(sumZ);
//	rand = length / 5;
//	sumZ = rand;
//	while (sumZ <= length)
//	{
//		z.push_back(sumZ);
//		sumZ+=rand;
//	}

//	for (i = 0; i < x.size()-1; i++)
//	{
//		for (j = 0; j < z.size()-1; ++j) {
//			coord tempCoord;
//			tempCoord.start.x = x[i];
//			tempCoord.start.y = 0.0;
//			tempCoord.start.z = z[j];
//			tempCoord.end.x = x[i+1];
//			tempCoord.end.y = 0.0;
//			tempCoord.end.z = z[j+1];
//			tempCoord.width = (x[i+1] - x[i]) - 2.0;
//			tempCoord.length = (z[j+1] - z[j]) - 2.0;
//			lotCoords.push_back(tempCoord);
//			newHouse(tempCoord.width, tempCoord.length);
//		}
//	}
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
		rand = Random::generateRandom(2, 5);
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
		rand = Random::generateRandom(2, 5);
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
	Construction * tempConstruction;
	float height;
	//random 1 - 3
	float stories = (Random::generateRandom(0, 3)+1);
	height = 2.5 * stories;
	tempConstruction = new House(width, length, height, gTextures);
	tempConstruction->generateConstruction();
	constructions.push_back(tempConstruction);
}

void Block::newBuilding(float width, float length)
{
	Construction * tempConstruction;
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

	tempConstruction = new Building(width, length, height, gTextures);
	tempConstruction->generateConstruction();
	constructions.push_back(tempConstruction);
}


void Block::renderBlock()
{
	glCallList(blockDL);
}
