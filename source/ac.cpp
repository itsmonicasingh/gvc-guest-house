#include <GL/glut.h>    // Header File For The GLUT Library 
#include <GL/gl.h>	// Header File For The OpenGL32 Library
#include <GL/glu.h>	// Header File For The GLu32 Library
#include <unistd.h>     // Header file for sleeping.
#include <stdio.h>      // Header file for standard file i/o.
#include <stdlib.h>     // Header file for malloc/free.
#include <math.h>       // Header file for trigonometric functions.
#include <string>
GLuint ac[3];

// load bitmaps and convert to textures
GLvoid LoadTexture_ac() 
{	
	// load texture
	Image *image6;

	// allocate space for texture
	image6 = (Image *) malloc(sizeof(Image));
	if (image6 == NULL) {
		printf("Error allocating");
		exit(0);
	}
	if (!ImageLoad("files/ac.bmp", image6)) {
		printf("unable to load image");
		exit(1);
	}
	glGenTextures(3, ac); // Create Textures

	// linear filtered texture
	glBindTexture(GL_TEXTURE_2D, ac[0]);   // 2d texture (x and y size)
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // scale linearly when image bigger than texture
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // scale linearly when image smalled than texture
	glTexImage2D(GL_TEXTURE_2D, 0, 3, image6->sizeX, image6->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image6->data);
};

void render_ac(float x1, float y1, float z1 )
{
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, ac[0]);   // 2d texture (x and y size)
	glBegin(GL_POLYGON);
		glTexCoord2f(0,0);
		glVertex3f(x1,y1,z1);
		glTexCoord2f(1,0);
		glVertex3f(x1+0.20,y1,z1);
		glTexCoord2f(1,1);
		glVertex3f(x1+0.20,y1+0.15,z1); 
		glTexCoord2f(0,1);
		glVertex3f(x1,y1+0.15,z1);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	
	glColor4d(0.5,0.5,0.5,0.6);  //color for ac 

	//draw quadiletral for ac	
	glBegin(GL_QUADS);
		glVertex3f(x1,y1,z1);
		glVertex3f(x1,y1+0.15,z1);
		glVertex3f(x1,y1+0.15,z1-0.01);
		glVertex3f(x1,y1,z1-0.01);
	glEnd();
	
	glBegin(GL_QUADS);
		glVertex3f(x1+0.2,y1,z1);
		glVertex3f(x1+0.2,y1+0.15,z1);
		glVertex3f(x1+0.2,y1+0.15,z1-0.01);
		glVertex3f(x1+0.2,y1,z1-0.01);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3f(x1,y1+0.15,z1);
		glVertex3f(x1+0.2,y1+0.15,z1);
		glVertex3f(x1+0.2,y1+0.15,z1-0.01);
		glVertex3f(x1,y1+0.15,z1-0.01);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3f(x1,y1,z1-0.01);
		glVertex3f(x1+0.2,y1,z1-0.01);
		glVertex3f(x1+0.2,y1+0.15,z1-0.01);
		glVertex3f(x1,y1+0.15,z1-0.01);
	glEnd();
}
