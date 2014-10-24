#include <GL/glut.h>    // Header File For The GLUT Library 
#include <GL/gl.h>	// Header File For The OpenGL32 Library
#include <GL/glu.h>	// Header File For The GLu32 Library
#include <unistd.h>     // Header file for sleeping.
#include <stdio.h>      // Header file for standard file i/o.
#include <stdlib.h>     // Header file for malloc/free.
#include <math.h>       // Header file for trigonometric functions.
#include <string>

GLuint texture[3];       // storage for 3 textures;

typedef struct {         // vertex coordinates - 3d and texture
	GLfloat x, y, z;     // 3d coords.
	GLfloat u, v;        // texture coords.
} VERTEX;

typedef struct {         // triangle
	VERTEX vertex[4];    // 3 vertices array
} TRIANGLE;

typedef struct {         // sector of a 3d environment
	int numtriangles;    // number of triangles in the sector
	TRIANGLE* triangle;  // pointer to array of triangles.
} SECTOR;


SECTOR sector1;

GLuint loop;

void readstr(FILE *f, char *string)
{
	do {
		fgets(string, 255, f); // read the line
	} while ((string[0] == '/') || (string[0] == '\n'));
	return;
}

// loads the world from a text file.
void SetupWorld() 
{
	float x, y, z, u, v;
	int vert;
	int numtriangles;
	FILE *filein;        // file to load the coordinates of house
	char oneline[255];
	filein = fopen("files/tmp.txt", "rt");
	readstr(filein, oneline);
	sscanf(oneline, "NUMOFTRIANGLE %d\n", &numtriangles);
	sector1.numtriangles = numtriangles;
	sector1.triangle = (TRIANGLE *) malloc(sizeof(TRIANGLE)*numtriangles);

	for (loop = 0; loop < numtriangles; loop++) {
		for (vert = 0; vert < 4; vert++) {
				readstr(filein,oneline);
				sscanf(oneline, "%f %f %f %f %f", &x, &y, &z, &u, &v);
				sector1.triangle[loop].vertex[vert].x = x;
				sector1.triangle[loop].vertex[vert].y = y;
				sector1.triangle[loop].vertex[vert].z = z;
				sector1.triangle[loop].vertex[vert].u = u;
				sector1.triangle[loop].vertex[vert].v = v;
		}
	}

	fclose(filein);
	return;
}
// Load Bitmaps And Convert To Textures
GLvoid LoadGLTextures() 
{	
	// Load Texture
	Image *image1;
	Image *image2;

	// allocate space for texture
	image1 = (Image *) malloc(sizeof(Image));
	image2 = (Image *) malloc(sizeof(Image));
	if (image1 == NULL) {
		printf("Error allocating");
		exit(0);
	}
	//load floor texture
	
	if (!ImageLoad("files/floor.bmp", image1)) {
		printf("unable to load");
		exit(1);
	}        

	// Create Textures	
	glGenTextures(3, texture);

	// linear filtered texture
	glBindTexture(GL_TEXTURE_2D, texture[0]);   // 2d texture (x and y size)
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // scale linearly when image bigger than texture
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // scale linearly when image smalled than texture
	glTexImage2D(GL_TEXTURE_2D, 0, 3, image1->sizeX, image1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image1->data);
	
	if (!ImageLoad("files/upper_floor.bmp", image2)) {
		printf("unable to load");
		exit(1);
	}        
	glBindTexture(GL_TEXTURE_2D, texture[1]);   // 2d texture (x and y size)
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // scale linearly when image bigger than texture
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // scale linearly when image smalled than texture
	glTexImage2D(GL_TEXTURE_2D, 0, 3, image2->sizeX, image2->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image2->data);
};
//external structure of guest house
void model() 
{	
	GLfloat x_m, y_m, z_m, u_m, v_m;	
	int numtriangles;
	numtriangles = sector1.numtriangles;
	for ( loop=0; loop < numtriangles; loop++ ) {        // loop through all the triangles
		if(loop == 0 || loop == 2)
		{
			glEnable(GL_TEXTURE_2D);
		}
		if (loop == 0){
			glBindTexture(GL_TEXTURE_2D, texture[0]);   // 2d texture (x and y size)
		}
		if ( loop == 2) {
			glBindTexture(GL_TEXTURE_2D, texture[1]);   
		}
		glBegin(GL_POLYGON);
			glNormal3f( 0.0f, 0.0f, 1.0f);

			x_m = sector1.triangle[loop].vertex[0].x;
			y_m = sector1.triangle[loop].vertex[0].y;
			z_m = sector1.triangle[loop].vertex[0].z;
			u_m = sector1.triangle[loop].vertex[0].u;
			v_m = sector1.triangle[loop].vertex[0].v;
			if(loop == 0 || loop == 2) {
				glTexCoord2f(0,0);
			}

			glColor3f(0.9,0.9,0.9);  //color for model
			glVertex3f(x_m,y_m,z_m);
	
			x_m = sector1.triangle[loop].vertex[1].x;
			y_m = sector1.triangle[loop].vertex[1].y;
			z_m = sector1.triangle[loop].vertex[1].z;
			u_m = sector1.triangle[loop].vertex[1].u;
			v_m = sector1.triangle[loop].vertex[1].v;
			if ( loop == 0 || loop == 2) {
			       	glTexCoord2f(0,50); 
			}
	
			glVertex3f(x_m,y_m,z_m);

			x_m = sector1.triangle[loop].vertex[2].x;
			y_m = sector1.triangle[loop].vertex[2].y;
			z_m = sector1.triangle[loop].vertex[2].z;
			u_m = sector1.triangle[loop].vertex[2].u;
			v_m = sector1.triangle[loop].vertex[2].v;
			if( loop ==  0 || loop == 2 ) {
				glTexCoord2f(50,50); 
			}
			glVertex3f(x_m,y_m,z_m);

			x_m = sector1.triangle[loop].vertex[3].x;
			y_m = sector1.triangle[loop].vertex[3].y;
			z_m = sector1.triangle[loop].vertex[3].z;
			u_m = sector1.triangle[loop].vertex[3].u;
			v_m = sector1.triangle[loop].vertex[3].v;
			if( loop ==  0 || loop == 2 ) {
				glTexCoord2f(50,0); 
			}
			glVertex3f(x_m,y_m,z_m);
		glEnd();	
	glDisable(GL_TEXTURE_2D);
	}
}
