/*
 * Streets.cpp
 *
 *  Created on: Sep 28, 2014
 *      Author: Iury Roger Painelli
 */

#include "Streets.h"

using namespace std;

Streets::Streets(int w, int l) {
	cityWidth = w;
	cityLength = l;

	blocks.reserve(500);

	segWidth= 2.5;
	segLength = 5.0;
	numSegments = 0;
	streetSegmentLeftDL = 0;
	streetSegmentRightDL = 0;
	deadEndCrossDL = 0;
	streetsDL = 0;
	cornerDL = 0;

	std::map<std::string, int> block;
	blockIndex = block;

	numBlock = 0;
	numBuildings = 0;

	cityCentre = glm::vec3 (cityWidth/2.f, 0.f, cityLength/2.f);
	distanceZeroToCentre = glm::distance(cityCentre, glm::vec3(0.f, 0.f, 0.f));
	relation = 100.f/distanceZeroToCentre;

}

Streets::~Streets() {
	glDeleteLists(streetSegmentRightDL, 1);
	glDeleteLists(streetSegmentLeftDL, 1);
	glDeleteLists(deadEndCrossDL, 1);
	glDeleteLists(streetsDL, 1);
}

void Streets::render()
{
	numSegments = 0;
	glPushMatrix();
	drawStreets();
	glPopMatrix();
//	cout << "Segments: " << numSegments << endl;

}

void Streets::drawStreets()
{
	glCallList(streetsDL);
}

void Streets::createStreets()
{
	unsigned int i;
	float length;
	glm::vec3 blockCoords;
	glm::vec3 start, end;
	float cornerTrans = segWidth/2.f;
	streetsDL = glGenLists(1);
	Block * tb;
	glNewList(streetsDL, GL_COMPILE);
		//draw blocks
		numSegments = 0;
		for(i = 0; i<blocks.size(); i++)
		{
			tb = blocks[i];
//			blockSize = blocks[i]->getEnd() - blocks[i]->getStart();
			start = tb->getStart();
			end = tb->getEnd();
			blockCoords = tb->getEnd() - tb->getStart();
			glPushMatrix();
				//translate block to right place
				glTranslatef(start.x, 0.0, start.z);
				//create streets for the block
				glPushMatrix();
					//first side
					length = end.z - start.z;
					glPushMatrix();
						glRotatef(180, 0.f, 1.f, 0.f);
						glTranslatef(-cornerTrans, 0.f, -cornerTrans);
						glCallList(cornerDL);
					glPopMatrix();
					drawStreetLine(length, FALSE);
					glPushMatrix();
						glTranslatef(cornerTrans, 0.0, blockCoords.z-cornerTrans);
						glRotatef(-90, 0.f, 1.f, 0.f);
						glCallList(cornerDL);
					glPopMatrix();
				glPopMatrix();
				glPushMatrix();
					//second side - opposite of first
					glTranslatef(blockCoords.x, 0.f, blockCoords.z);
					glRotatef(180, 0.f, 1.f, 0.f);
					glPushMatrix();
						glRotatef(180, 0.f, 1.f, 0.f);
						glTranslatef(-cornerTrans, 0.f, -cornerTrans);
						glCallList(cornerDL);
					glPopMatrix();
					drawStreetLine(length, FALSE);
					glPushMatrix();
						glTranslatef(cornerTrans, 0.0, blockCoords.z-cornerTrans);
						glRotatef(-90, 0.f, 1.f, 0.f);
						glCallList(cornerDL);
					glPopMatrix();
				glPopMatrix();
				glPushMatrix();
					//third side
					length = end.x - start.x;
					glRotatef(90, 0.f, 1.f, 0.f);
					drawStreetLine(length, TRUE);
				glPopMatrix();
				glPushMatrix();
					//fourth side - opposite of third
					glTranslatef(blockCoords.x, 0.0, blockCoords.z);
					glRotatef(270, 0.f, 1.f, 0.f);
					drawStreetLine(length, TRUE);
				glPopMatrix();

				//draw block
				blocks[i]->renderBlock();
			glPopMatrix();
		}
	glEndList();
//	cout << "Segments: " << numSegments << endl;
}

void Streets::drawStreetLine(float length, int isLeft)
{
	float position;
	float finalPosition;

	GLuint DL;
	position = segWidth;
	finalPosition = length-segWidth*2;

	if (isLeft)
		DL = streetSegmentLeftDL;
	else
		DL = streetSegmentRightDL;

	while (position <= finalPosition)
	{
		glPushMatrix();
		glTranslatef(0.0, 0.0, position);
		glCallList(DL);
		numSegments++;
		position += segLength;
		glPopMatrix();
	}


}

void Streets::drawOuterStreets()
{

}
void Streets::createStreetGeometry()
{
	float size;
	GLuint crossTexture;
	GLuint texture = ImageLoader::readTexture("assets/textures/road/street1.jpg");

	streetSegmentLeftDL = glGenLists(1);
	glNewList(streetSegmentLeftDL, GL_COMPILE);
	glEnable(GL_TEXTURE_2D);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, texture);
	glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_QUADS);
			glTexCoord2f(0.f, 0.f); glVertex3f(-segWidth, 0.01, 0.0);
			glTexCoord2f(0.5f, 0.f); glVertex3f(0.0, 0.01, 0.0);
			glTexCoord2f(0.5f, 1.f); glVertex3f(0.0, 0.01, segLength);
			glTexCoord2f(0.f, 1.f); glVertex3f(-segWidth, 0.01, segLength);
		glEnd();
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	glEndList();

	streetSegmentRightDL = glGenLists(1);
	glNewList(streetSegmentRightDL, GL_COMPILE);
	glEnable(GL_TEXTURE_2D);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, texture);
	glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_QUADS);
			glTexCoord2f(0.5f, 0.f); glVertex3f(0.0, 0.01, 0.0);
			glTexCoord2f(1.f, 0.f); glVertex3f(segWidth, 0.01, 0.0);
			glTexCoord2f(1.f, 1.f); glVertex3f(segWidth, 0.01, segLength);
			glTexCoord2f(0.5f, 1.f); glVertex3f(0.0, 0.01, segLength);
		glEnd();
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	glEndList();


	crossTexture = ImageLoader::readTexture("assets/textures/road/cross1.jpg");

	deadEndCrossDL = glGenLists(1);
	size = segWidth;
	glNewList(deadEndCrossDL, GL_COMPILE);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, crossTexture);
	glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_QUADS);
			glTexCoord2f(0.5f, 0.f); glVertex3f(0.0, 0.01, 0.0);
			glTexCoord2f(1.f,  0.f); glVertex3f(size, 0.01, 0.0);
			glTexCoord2f(1.f,  1.f); glVertex3f(size, 0.01, size*2);
			glTexCoord2f(0.5f, 1.f); glVertex3f(0.0, 0.01, size*2);
		glEnd();
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	glEndList();

	cornerDL = glGenLists(1);
	size = segWidth;
	glNewList(cornerDL, GL_COMPILE);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, crossTexture);
	glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_QUADS);
			glTexCoord2f(0.f, 0.f); glVertex3f(-size/2.f, 0.01, -size/2.f);
			glTexCoord2f(0.5f, 0.f); glVertex3f(size/2.f, 0.01, -size/2.f);
			glTexCoord2f(0.5f, 0.5f); glVertex3f(size/2.f, 0.01, size/2.f);
			glTexCoord2f(0.f, 0.5f); glVertex3f(-size/2.f, 0.01, size/2.f);
		glEnd();
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	glEndList();


}



void Streets::drawCityFloor()
{
	int l = cityWidth;
	int w = cityLength;
	glBegin(GL_QUADS);
		glVertex3d(0.f , 0.f, 0.f);
		glVertex3d(w, 0.f, 0.f);
		glVertex3d(w, 0.f, l);
		glVertex3d(0.f, 0.f, l);
	glEnd();
}
void Streets::createMap()
{
	printf("Creating blocks...\n");
	createBlocks();
	printf("Total of %d buildings in %d Blocks created\n", numBuildings, numBlock);
	printf("Generating geometries...\n");
	createStreetGeometry();
	createStreets();
}

void Streets::createBlocks()
{
	Block * tempBlock;
	glm::vec3 tempStart, tempEnd;
	int blockWidth = 50;
	int blockLength = 100;
	int isPark = FALSE;

	int rowX=0, rowZ=0;
	int xCoord, zCoord;

	numBlock = 0;
	while(rowZ < cityLength)
	{
		while (rowX < cityWidth)
		{
			isPark = FALSE;
			xCoord = rowX;
			zCoord = rowZ;
			tempStart = glm::vec3(xCoord, 0.0, zCoord);

			xCoord += blockWidth;
			zCoord += blockLength;

			//check if the next block to be created is already occupied
			if(!isBlockOcuppied(glm::vec3(xCoord, 0.0, zCoord)))
			{
				//the block is bigger than others? 10% of chance
				if (Random::generateRandom(1, 10) == 1)
				{
					//cout << "RANDOM (BIGGER BLOCK)" << endl;
					//Bigger in X or Z?
					int rand = Random::generateRandom(1, 10);
					if (rand <= 5)
					{
						//In X (Width)!
						//cout << " in X" << endl;
						if (xCoord != cityWidth)
							xCoord += blockWidth;
					}
					else
					{
						//In Z (Length)!
						//cout << " in Z" << endl;
						isPark = TRUE;
						if (zCoord != cityLength)
							zCoord += blockLength;
					}
				}
				tempEnd = glm::vec3(xCoord, 0.0, zCoord);
				//printf ("Block %d, start (%f,%f) end (%f,%f)\n", nBlock,
					//tempBlock.start.x, tempBlock.start.z, tempBlock.end.x, tempBlock.end.z);

				float distanceFromCentre = abs(glm::distance(tempStart, cityCentre));

				//scale distance from centre to a scale from 1 to 100;
				int distanceToScale = (int) (relation * distanceFromCentre);
				//printf ("(%f, %f) dist %d\n", tempStart.x, tempStart.z, relationCentreBlock);
				tempBlock = new Block(tempStart, tempEnd, distanceToScale, isPark);

				numBuildings += tempBlock->generateBlock();
				blocks.push_back(tempBlock);

				insertIndex(tempEnd, numBlock);
				numBlock++;
			}
			rowX += blockWidth;
		}
		rowZ += blockLength;
		rowX = 0;
	}

}

void Streets::createAvenues()
{
}

void Streets::insertIndex(glm::vec3 t, int n)
{
	std::string key;
	//create key for the index
	key = concat(t);
	//insert to index
	blockIndex[key] = n;
//	printf("Key: %s BlockN %d\n", key.c_str(), n);
}

int Streets::isBlockOcuppied(glm::vec3 t)
{
	std::string key = concat(t);
	// check if key is present
	if (blockIndex.find(key) != blockIndex.end())
		return 1;
	else
		return 0;
}

std::string Streets::concat(glm::vec3 t)
{
	std::ostringstream oss;
	oss << t.x << t.z;
	return oss.str();
}
