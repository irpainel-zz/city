/*
 * Viewport.h
 *
 *  Created on: Aug 29, 2014
 *      Author: Iury Roger Painelli
 */

#ifndef VIEWPORT_H_
#define VIEWPORT_H_
#include "GlutFramework.h"

using namespace glutFramework;

class Viewport {
public:
	Viewport();
	virtual ~Viewport();
	static void drawAxes(int toggleAxes);
	static void drawFloor(int toggleFloor);
	static void RenderString(float x, float y, void *font, const char* string, float* rgb);
};


#endif /* VIEWPORT_H_ */
