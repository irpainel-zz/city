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

	segWidth= 3.0;
	segLength = 5.0;
	numSegments = 0;
	streetSegmentDL = 0;

	std::map<std::string, int> block;
	blockIndex = block;

	numBlock = 0;
	numBuildings = 0;

}

Streets::~Streets() {
	glDeleteLists(streetSegmentDL, 1);
}

void Streets::render()
{
	numSegments = 0;
	glPushMatrix();
//	drawCityFloor();
	drawStreets();
	glPopMatrix();
//	cout << "Segments: " << numSegments << endl;

}

void Streets::drawStreets()
{
	unsigned int i;
	glm::vec3 blockSize;
	//draw blocks
	numSegments = 0;
	for(i = 0; i<blocks.size(); i++)
	{

		blockSize = blocks[i]->getEnd() - blocks[i]->getStart();
		glPushMatrix();
			glTranslatef(0.0, 0.0, blocks[i]->getStart().z);
			glTranslatef(blocks[i]->getStart().x, 0.0, 0.0);
			drawStreetLine(blockSize);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(blocks[i]->getStart().x, 0.f, blocks[i]->getStart().z);
			blocks[i]->renderBlock();
		glPopMatrix();
	}
//	cout << "Segments: " << numSegments << endl;
}

void Streets::drawStreetLine(glm::vec3 size)
{
	float position;
	float finalPosition;

	position = segLength;
	finalPosition = size.x - segLength;
	check_gl_error();


	while (position <= finalPosition)
	{
		glPushMatrix();
		glRotatef(90, 0.f, 1.0, 0.f);
		glPushMatrix();
		glTranslatef(0.0, 0.0, position);
		glCallList(streetSegmentDL);
		numSegments++;
		position += segLength;
		glPopMatrix();
		glPopMatrix();
	}

	//draw streets in Z axis
	position = segLength;
	finalPosition = size.z - segLength;
	while (position <= finalPosition)
	{
		glPushMatrix();
		glTranslatef(0.0, 0.0, position);
		glCallList(streetSegmentDL);
		numSegments++;
		position += segLength;
		glPopMatrix();
	}


}

void Streets::createStreetSegmentGeometry()
{
	streetSegmentDL = glGenLists(1);
	glNewList(streetSegmentDL, GL_COMPILE);
		glColor3f(0.9, 0.9, 0.9);
		glBegin(GL_QUADS);
			glVertex3f(-segWidth, 0.1, -segLength);
			glVertex3f(segWidth, 0.1, -segLength);
			glVertex3f(segWidth, 0.1, segLength);
			glVertex3f(-segWidth, 0.1, segLength);
		glEnd();
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
	createStreetSegmentGeometry();
}

void Streets::createBlocks()
{
	Block * tempBlock;
	glm::vec3 tempStart, tempEnd;
	int blockWidth = 100;
	int blockLength = 200;

	int rowX=0, rowZ=0;
	int xCoord, zCoord;

	numBlock = 0;
	while(rowZ < cityLength)
	{
		while (rowX < cityWidth)
		{
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
//					cout << "RANDOM (BIGGER BLOCK)" << endl;
					//Bigger in X or Z?
					int rand = Random::generateRandom(1, 10);
					if (rand <= 5)
					{
						//In X (Width)!
//						cout << " in X" << endl;
						if (xCoord != cityWidth)
							xCoord += blockWidth;
					}
					else
					{
						//In Z (Length)!
//						cout << " in Z" << endl;
						if (zCoord != cityLength)
							zCoord += blockLength;
					}
				}
				tempEnd = glm::vec3(xCoord, 0.0, zCoord);
//				printf ("Block %d, start (%f,%f) end (%f,%f)\n", nBlock,
//						tempBlock.start.x, tempBlock.start.z, tempBlock.end.x, tempBlock.end.z);
				tempBlock = new Block(tempStart, tempEnd);

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
