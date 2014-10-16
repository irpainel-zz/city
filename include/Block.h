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
#include "Construction.h"
#include "Building.h"
#include "House.h"
#include "GLerror.h"
#include "textures.h"

typedef struct coord {
	glm::vec3 start;
	glm::vec3 end;
	float width;
	float length;
}c;

class Block {
public:
	Block(glm::vec3 s, glm::vec3 e, int centreDistance, int isPark, textures t);
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
	int centreDistance;
	int isPark;
	GLuint blockDL;

	vector<Construction *> constructions;
	//coords for each lot
	vector<coord> lotCoords;

	//textures
	textures gTextures;


	//methods
	void splitBlock();
	void newParkBlock();
	void newBuildingBlock();
	void newResidentialBlock();
	void newBuilding(float width, float length);
	void newHouse(float width, float length);

	//compile display list
	void compileConstructions(GLuint floorTexture);
	void compilePark();
	void drawBlockFloor(GLuint texture);

};

#endif /* BLOCK_H_ */
