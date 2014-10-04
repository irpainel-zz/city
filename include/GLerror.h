/*
 * GLerror.h
 *
 *  Created on: Oct 4, 2014
 *      Author: Iury Roger Painelli
 */
#include "GlutFramework.h"
#include <iostream>
#include <string>

#ifndef GLERROR_H
#define GLERROR_H

void _check_gl_error(const char *file, int line);

///
/// Usage
/// [... some opengl calls]
/// check_gl_error();
///
#define check_gl_error() _check_gl_error(__FILE__,__LINE__)

#endif // GLERROR_H
