/*
 * Random.cpp
 *
 *  Created on: Sep 28, 2014
 *      Author: Iury Roger Painelli
 */

#include "Random.h"

Random::Random() {
	// TODO Auto-generated constructor stub

}

Random::~Random() {
	// TODO Auto-generated destructor stub
}

int Random::generateRandom(int from, int to)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(from, to);

    return dist(mt);
}
