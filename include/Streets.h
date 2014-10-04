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

	GLuint streetSegmentDL;

	std::map<std::string, int> blockIndex;


	float segWidth, segLength;
	int numSegments;

	void createAvenues();
	void createStreets();
	void createBlocks();
	void drawStreets();
	void drawStreetLine(glm::vec3 size);
	void drawCityFloor();
	void createStreetSegmentGeometry();

	std::string concat(glm::vec3);
	void insertIndex(glm::vec3, int);
	int isBlockOcuppied(glm::vec3);

};

#endif /* STREETS_H_ */
