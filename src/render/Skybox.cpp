/*
 * Skybox.cpp
 *
 *  Created on: Sep 19, 2014
 *      Author: Iury Roger Painelli
 */

#include "Skybox.h"

Skybox::Skybox() {
	createSkybox();

}

Skybox::~Skybox() {
	// TODO Auto-generated destructor stub
}

void Skybox::drawBox()
{

	glDepthMask (GL_FALSE);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	glActiveTexture (GL_TEXTURE0);
	glBindTexture (GL_TEXTURE_CUBE_MAP, texCubeName);

	glPushMatrix();
	glScalef(100, 100, 100);
	//left
	glBegin(GL_QUADS);
	       glVertex3f(  -10.f, -10.f, -10.f );
	       glVertex3f( 	 -10.f, -10.f, 10.f );
	       glVertex3f(   -10.f,10.f, 10.f );
	       glVertex3f(  -10.f,10.f, -10.f );
	glEnd();
	//front
	glBegin(GL_QUADS);
	       glVertex3f(   -10.f, -10.f, 10.f );
	       glVertex3f(  10.f, -10.f,10.f );
	       glVertex3f(   10.f,10.f,10.f );
	       glVertex3f(   -10.f,10.f, 10.f );
	glEnd();
	//right
	glBegin(GL_QUADS);
	       glVertex3f(  10.f, -10.f,10.f );
	       glVertex3f( 	10.f,-10.f,-10.f );
	       glVertex3f(  10.f,10.f,-10.f );
	       glVertex3f(   10.f, 10.f,10.f );
	glEnd();
	//back
	glBegin(GL_QUADS);
	       glVertex3f(  10.f, -10.f,-10.f );
	       glVertex3f( 	-10.f, -10.f, -10.f );
	       glVertex3f(  -10.f,10.f, -10.f );
	       glVertex3f(  10.f,10.f,-10.f );
	glEnd();
	//top
	glBegin(GL_QUADS);
	       glVertex3f(  -10.f, 10.f, 10.f );
	       glVertex3f( 	 10.f, 10.f, 10.f );
	       glVertex3f(   10.f, 10.f,-10.f );
	       glVertex3f(  -10.f, 10.f,-10.f );
	glEnd();
	//bottom
	glBegin(GL_QUADS);
	       glVertex3f(  -10.f,-10.f,-10.f );
	       glVertex3f( 	10.f,-10.f, -10.f );
	       glVertex3f(   10.f,-10.f, 10.f );
	       glVertex3f(   -10.f,-10.f,10.f );
	glEnd();
	glPopMatrix();


	glFlush();
	glBindTexture (GL_TEXTURE_CUBE_MAP, 0);
	glDepthMask (GL_TRUE);
}

void Skybox::createSkybox()
{
	int i;
	//glEnable(GL_DEPTH_TEST);
	static GLenum faceTarget[6] = {
	  GL_TEXTURE_CUBE_MAP_POSITIVE_X,
	  GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
	  GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
	  GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
	  GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
	  GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
	};

	const char *faceFile[6] =  {
	  "assets/textures/sky/xpos.jpg",
	  "assets/textures/sky/xneg.jpg",
	  "assets/textures/sky/yneg.jpg",
	  "assets/textures/sky/ypos.jpg",
	  "assets/textures/sky/zpos.jpg",
	  "assets/textures/sky/zneg.jpg",
	};
	glEnable(GL_TEXTURE_CUBE_MAP);
	glGenTextures(1, &texCubeName);
	for (i=0; i<6; i++) {
		loadFace(faceTarget[i], faceFile[i]);
	}

  glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
  glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

void Skybox::loadFace(GLenum target, const char *fn)
{
	glBindTexture (GL_TEXTURE_CUBE_MAP, texCubeName);
	unsigned int i;
	char filename[50];
	strcpy(filename, fn);

		for (i = 0; i < strlen(filename); i++) {
			if (filename[i] == '.') {
				break;
			}
		}
		char extension[5];
		strcpy(extension, &filename[i + 1]);
		//printf(extension);
		if (strcmp(extension, "jpg") == 0 || strcmp(extension, "jpeg") == 0)
			ImageLoader::loadTextureFromJPEG(filename, &tCubeMap);
		else {
			printf("Invalid format. Only supports JPEG and PNG.\n");
			exit(1);
		}

			glTexImage2D(target, 0, GL_RGB, tCubeMap.width, tCubeMap.height, 0, GL_RGB,
					GL_UNSIGNED_BYTE, tCubeMap.textureData);

		//Once the texture has been loaded by GL, we don't need this anymore.
		free(tCubeMap.textureData);

}
