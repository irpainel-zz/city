/*
 * Random.h
 *
 *  Created on: Sep 28, 2014
 *      Author: Iury Roger Painelli
 */

#ifndef RANDOM_H_
#define RANDOM_H_

#include <GlutFramework.h>
#include <iostream>
#include <random>
//#include <bits/random.h>

class Random {
public:
	Random();
	virtual ~Random();

	static int generateRandom(int from, int to);
};

#endif /* RANDOM_H_ */
