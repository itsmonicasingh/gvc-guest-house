#include <GL/glut.h>    // Header File For The GLUT Library 
#include <GL/gl.h>	// Header File For The OpenGL32 Library
#include <GL/glu.h>	// Header File For The GLu32 Library
#include <unistd.h>     // Header file for sleeping.
#include <stdio.h>      // Header file for standard file i/o.
#include <stdlib.h>     // Header file for malloc/free.
#include <math.h>       // Header file for trigonometric functions.
#include <string>
GLuint text[3];

// Load Bitmaps And Convert To Textures
GLvoid LoadTexture_Fridge() 
{	
	// Load Texture
	Image *image3;

	// allocate space for texture
	image3 = (Image *) malloc(sizeof(Image));
	if (image3 == NULL) {
		printf("Error allocating");
		exit(0);
	}
	if (!ImageLoad("files/fridge.bmp", image3)) {
		printf("unable to load");
		exit(1);
	}        

	// Create Textures	
	glGenTextures(3, text);

	// linear filtered texture
	glBindTexture(GL_TEXTURE_2D, text[0]);   // 2d texture (x and y size)
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // scale linearly when image bigger than texture
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // scale linearly when image smalled than texture
	glTexImage2D(GL_TEXTURE_2D, 0, 3, image3->sizeX, image3->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image3->data);
};

void fridge(float x1, float y1, float z1 )
{
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, text[0]);   // 2d texture (x and y size)
	glBegin(GL_POLYGON);
		glTexCoord2f(0,0);
		glVertex3f(x1,y1,z1);
		glTexCoord2f(1,0);
		glVertex3f(x1+0.3,y1,z1);
		glTexCoord2f(1,1);
		glVertex3f(x1+0.3,y1+0.45,z1);
		glTexCoord2f(0,1);
		glVertex3f(x1,y1+0.45,z1);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glColor4d(0.5,0.5,0.5,0.6);
	
	//quadliteral for fridge
	glBegin(GL_QUADS);
		glVertex3f(x1,y1,z1);
		glVertex3f(x1,y1+0.45,z1);
		glVertex3f(x1,y1+0.45,z1-0.2);
		glVertex3f(x1,y1,z1-0.2);	
	glEnd();
	glBegin(GL_QUADS);
		glVertex3f(x1+0.3,y1,z1);
		glVertex3f(x1+0.3,y1+0.45,z1);
		glVertex3f(x1+0.3,y1+0.45,z1-0.2);
		glVertex3f(x1+0.3,y1,z1-0.2);	
	glEnd();
	glBegin(GL_QUADS);
		glVertex3f(x1,y1+0.45,z1);
		glVertex3f(x1+0.3,y1+0.45,z1);
		glVertex3f(x1+0.3,y1+0.45,z1-0.2);
		glVertex3f(x1,y1+0.45,z1-0.2);	
	glEnd();
	glBegin(GL_QUADS);
		glVertex3f(x1,y1,z1-0.2);
		glVertex3f(x1+0.3,y1,z1-0.2);
		glVertex3f(x1+0.3,y1+0.45,z1-0.2);
		glVertex3f(x1,y1+0.45,z1-0.2);	
	glEnd();
}
