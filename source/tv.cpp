#include <GL/glut.h>    // Header File For The GLUT Library 
#include <GL/gl.h>	// Header File For The OpenGL32 Library
#include <GL/glu.h>	// Header File For The GLu32 Library
#include <unistd.h>     // Header file for sleeping.
#include <stdio.h>      // Header file for standard file i/o.
#include <stdlib.h>     // Header file for malloc/free.
#include <math.h>       // Header file for trigonometric functions.
#include <string>
GLuint txt[3];

// Load Bitmaps And Convert To Textures
GLvoid LoadTexture_tv() 
{	
	// Load Texture
	Image *image4;
	// allocate space for texture
	image4 = (Image *) malloc(sizeof(Image));
	if (image4 == NULL) {
		printf("Error allocating space");
		exit(0);
	}

	if (!ImageLoad("files/tv.bmp", image4)) {
		printf("unable to load");
		exit(1);
	}

	// Create Textures	
	glGenTextures(3, txt);

	// linear filtered texture
	glBindTexture(GL_TEXTURE_2D, txt[0]);   // 2d texture (x and y size)
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // scale linearly when image bigger than texture
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // scale linearly when image smalled than texture
	glTexImage2D(GL_TEXTURE_2D, 0, 3, image4->sizeX, image4->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image4->data);
};

void tv(float x1, float y1, float z1 )
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, txt[0]);   // 2d texture (x and y size)
	glBegin(GL_POLYGON);
		glTexCoord2f(0,0);
		glVertex3f(x1,y1,z1);
		glTexCoord2f(1,0);
		glVertex3f(x1+0.25,y1,z1);
		glTexCoord2f(1,1);
		glVertex3f(x1+0.25,y1+0.15,z1); 
		glTexCoord2f(0,1);
		glVertex3f(x1,y1+0.15,z1);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glColor4d(0.5,0.5,0.5,0.6); //color for tv quadliteral

	glBegin(GL_QUADS);
		glVertex3f(x1,y1,z1);
		glVertex3f(x1,y1+0.15,z1);
		glVertex3f(x1,y1+0.15,z1-0.01);
		glVertex3f(x1,y1,z1-0.01);
	glEnd();
	glBegin(GL_QUADS);
		glVertex3f(x1+0.25,y1,z1);
		glVertex3f(x1+0.25,y1+0.15,z1);
		glVertex3f(x1+0.25,y1+0.15,z1-0.01);
		glVertex3f(x1+0.25,y1,z1-0.01);
	glEnd();
	glBegin(GL_QUADS);
		glVertex3f(x1,y1+0.15,z1);
		glVertex3f(x1+0.25,y1+0.15,z1);
		glVertex3f(x1+0.25,y1+0.15,z1-0.01);
		glVertex3f(x1,y1+0.15,z1-0.01);
	glEnd();
	glBegin(GL_QUADS);
		glVertex3f(x1,y1,z1-0.01);
		glVertex3f(x1+0.25,y1,z1-0.01);
		glVertex3f(x1+0.25,y1+0.15,z1-0.01);
	glVertex3f(x1,y1+0.15,z1-0.01);
	glEnd();
}
