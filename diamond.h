/*
 *  diamonds.h
 *  cottages
 *
 *  Created by Bartlomiej Kozal on 08/06/2010.
 *  Copyright 2010 Bartlomiej Kozal. All rights reserved.
 *
 */

#ifndef DIAMOND
#define DIAMOND

#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#include "object.h"

class Diamond : private Object {
	
public:
	
	Diamond();
	void draw();
	
};

#endif