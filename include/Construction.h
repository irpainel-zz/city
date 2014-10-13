/*
 * Construction.h
 *
 *  Created on: Oct 4, 2014
 *      Author: Iury Roger Painelli
 */

#ifndef Construction_H_
#define Construction_H_

#include <map>
#include <cassert>
#include <sstream>
#include "GlutFramework.h"
#include "Random.h"
#include "glm/glm.hpp"
#include "textures.h"

class Construction {
public:
	Construction(float w, float l, float h, textures t);
	virtual ~Construction();

	virtual void generateConstruction();
	void drawConstruction();

protected:
	float width;
	float length;
	float height;

	//textures
	textures gTextures;

	GLuint ConstructionDL;
};

#endif /* Construction_H_ */
