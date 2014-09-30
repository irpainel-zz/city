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
#include "glm/glm.hpp"

using namespace std;


typedef struct b {
	glm::vec3 start;
	glm::vec3 end;
	int intersections;
}block;

class Streets {
public:
	Streets(int w, int l);
	virtual ~Streets();
	void render();
	void createMap();

private:
	int cityWidth, cityLength;
	vector <block> blocks;
	int numBlock;

	std::map<std::string, int> blockIndex;


	float segWidth, segLength;
	int numSegments;

	void createAvenues();
	void createStreets();
	void createBlocks();
	void drawStreets();
	void drawStreetLine(glm::vec3 size);
	void drawStreetSegment();
	void drawCityFloor();

	std::string concat(glm::vec3);
	void insertIndex(glm::vec3, int);
	int isBlockOcuppied(glm::vec3);

};

#endif /* STREETS_H_ */
