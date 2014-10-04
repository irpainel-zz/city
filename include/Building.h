/*
 * Building.h
 *
 *  Created on: Oct 4, 2014
 *      Author: Iury Roger Painelli
 */

#ifndef BUILDING_H_
#define BUILDING_H_

#include <map>
#include <cassert>
#include <sstream>
#include "GlutFramework.h"
#include "Random.h"
#include "glm/glm.hpp"

class Building {
public:
	Building(float w, float l, float h);
	virtual ~Building();

	void generateBuilding();
	void drawBuilding();

private:
	float width;
	float length;
	float height;

	GLuint buildingDL;
};

#endif /* BUILDING_H_ */
