/*
 * House.h
 *
 *  Created on: Oct 11, 2014
 *      Author: Iury Roger Painelli
 */

#ifndef HOUSE_H_
#define HOUSE_H_

#include <Construction.h>

class House: public Construction {
public:
	House(float w, float l, float h);
	virtual ~House();

	void generateConstruction();
};

#endif /* HOUSE_H_ */
