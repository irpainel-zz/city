/*
 * textures.h
 *
 *  Created on: Oct 13, 2014
 *      Author: Iury Roger Painelli
 */

#ifndef TEXTURES_H_
#define TEXTURES_H_

#include <vector>
#include "GlutFramework.h"
#include "glm/glm.hpp"

using namespace std;

typedef struct textures {
	vector<GLuint> grass;
	vector<GLuint> window;
	vector<GLuint> door;
	vector<GLuint> wall;
	vector<GLuint> roof;
	vector<GLuint> building;
	vector<GLuint> building_roof;
}tex;




#endif /* TEXTURES_H_ */
