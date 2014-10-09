/*
 * Streets.h
 *
 *  Created on: Sep 28, 2014
 *      Author: Iury Roger Painelli
 */

#ifndef STREETS_H_
#define STREETS_H_

#include <map>
#include <cassert>
#include <sstream>
#include "GlutFramework.h"
#include "Random.h"
#include "Block.h"
#include "glm/glm.hpp"
#include "GLerror.h"
#include "ImageLoader.h"

using namespace std;

class Streets {
public:
	Streets(int w, int l);
	virtual ~Streets();
	void render();
	void createMap();

private:
	int cityWidth, cityLength;
	vector <Block*> blocks;
	int numBlock;
	int numBuildings;
	glm::vec3 cityCentre;
	//farthest point from centre - actually just (0,0) - (Centre.x, Centre.z)
	float distanceZeroToCentre;
	//relation from centre to block (in a scale from 0 - 100),
	//a bit complicated explanation
	//I am transforming the distance from the centre in a scale from 0 (close) - 100 (far)
	//so its possible to use this distance in any map size
	float relation;

	GLuint streetSegmentRightDL;
	GLuint streetSegmentLeftDL;
	GLuint streetsDL;
	GLuint cornerDL;
	GLuint deadEndCrossDL;


	std::map<std::string, int> blockIndex;


	float segWidth, segLength;
	int numSegments;

	void createAvenues();
	void createStreets();
	void createBlocks();
	void drawStreets();
	void drawStreetLine(float length, int isLeft);
	void drawOuterStreets();
	void drawCityFloor();
	void createStreetGeometry();
	void defineCityCentre();

	std::string concat(glm::vec3);
	void insertIndex(glm::vec3, int);
	int isBlockOcuppied(glm::vec3);

};

#endif /* STREETS_H_ */
