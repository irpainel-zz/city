/*
 * Block.h
 *
 *  Created on: Oct 4, 2014
 *      Author: Iury Roger Painelli
 */

#ifndef BLOCK_H_
#define BLOCK_H_

#include <map>
#include <cassert>
#include <sstream>
#include "GlutFramework.h"
#include "Random.h"
#include "glm/glm.hpp"
#include "Building.h"
#include "GLerror.h"

typedef struct coord {
	glm::vec3 start;
	glm::vec3 end;
	float width;
	float length;
}c;

class Block {
public:
	Block(glm::vec3 s, glm::vec3 e);
	virtual ~Block();
	glm::vec3 getStart();
	glm::vec3 getEnd();
	int generateBlock();
	void renderBlock();


private:
	glm::vec3 start;
	glm::vec3 end;
	float width;
	float length;
	int intersections;
	GLuint blockDL;

	vector<Building *> buildings;
	//coords for each lot
	vector<coord> lotCoords;


	//methods
	void splitBlock();
	void newBuilding(float width, float length);

};

#endif /* BLOCK_H_ */
