//---------------------------------------------------------------------------
//
// This software is provided 'as-is' for assignment of COMP308
// in ECS, Victoria University of Wellington,
// without any express or implied warranty.
// In no event will the authors be held liable for any
// damages arising from the use of this software.
//
// The contents of this file may not be copied or duplicated in any form
// without the prior permission of its owner.
//
// Copyright (c) 2012 by Taehyun Rhee
//
// Edited by Roma Klapaukh, Daniel Atkins, and Taehyun Rhee
//
//---------------------------------------------------------------------------

#include <GLUT/glut.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>

#ifndef __DEFINE_COMP308__
#define __DEFINE_COMP308__

using namespace std;


// Default Window
#define WIN_WIDTH	640
#define WIN_HEIGHT	480

// Projection parameters
#define G308_FOVY		20.0
#define G308_ZNEAR_3D	1
#define G308_ZFAR_3D	2000.0
#define G308_ZNEAR_2D	-50.0
#define G308_ZFAR_2D	50.0


//Animation Control
#define A_SEPARATOR -1

#define TRUE 1
#define FALSE 0


#endif
