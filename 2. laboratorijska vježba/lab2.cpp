#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include "util.h"

using namespace std;

vector<Particle> particles;
Source source;
GLuint width = 1280, height = 720;
Vertex cam(0.0, 0.0, 50.0);
int currentTime = 0; int previousTime = 0;
double parSize = 0.5;
double parVel = 0.5;
double parCount = 10;

void drawPar() {
	for (int i = 0; i < particles.size(); i++) {
		Particle par = particles.at(i);
		glColor3f(par.r, par.g, par.b);
		glTranslatef(par.x, par.y, par.z);
		glRotatef(par.angle, par.osX, par.osY, par.osZ);
		glBegin(GL_QUADS);
	
		glTexCoord2d(0.0,0.0); glVertex2f(-par.size, -par.size);
		glTexCoord2d(1.0,0.0); glVertex2f(-par.size, +par.size);
		glTexCoord2d(1.0,1.0); glVertex2f(+par.size, +par.size);
		glTexCoord2d(0.0,1.0); glVertex2f(+par.size, -par.size);

		glEnd();
		glRotatef(-par.angle, par.osX, par.osY, par.osZ);
		glTranslatef(-par.x, -par.y, -par.z);
	}
}

void myDisplay()
{
 	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(cam.x, cam.y, -cam.z);

	drawPar();
	glutSwapBuffers();
}

void myIdle() {
	currentTime = glutGet(GLUT_ELAPSED_TIME);
	int timeInt = currentTime - previousTime;

	if(timeInt > 100) {
		
		for (int i = 0; i < parCount; i++) {
			double x, y, z, norm;
			x = (rand()%1920-1080) / (double)1080;
			y = (rand()%1920-1080) / (double)1080;
			z = (rand()%1920-1080) / (double)1080;
			norm = pow(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0), 0.5);
			x /= norm; 
			y /= norm; 
			z /= norm;

			Particle par;
			par.x = source.x; 
			par.z = source.z; 
			par.y = source.y; 

			double temp_cR = rand()%(10-0)+0;
			double temp_cG = rand()%(10-0)+0;
			double temp_cB = rand()%(10-0)+0;

			if(temp_cR > 5){
				par.r = 1.0;
			} 
			else par.r = 0.0;

			if(temp_cB > 5){
				par.b = 1.0;
			} 
			else par.b = 0.0;

			if(temp_cG > 5){
				par.g = 1.0;
			} 
			else par.g = 0.0;

			par.vel = parVel;
			par.dX = x; 
			par.dY = y; 
			par.dZ = z;
			par.life = rand()%(200-100) + 100;
			par.size = parSize;

			particles.push_back(par);
		}
			
		for (int i =  particles.size() - 1; i >= 0; i--) {

			Vertex s(0.0, 0.0, 1.0);
			Vertex os(0.0, 0.0, 0.0);
			Vertex e(0.0, 0.0, 0.0);
				
			e.x = particles.at(i).x - cam.x;
			e.y = particles.at(i).y - cam.y;
			e.z = particles.at(i).z - cam.z;

			particles.at(i).osX = s.y*e.z - e.y*s.z; 
			particles.at(i).osY = e.x*s.z - s.x*e.z;
			particles.at(i).osZ = s.x*e.y - s.y*e.x;

			double apsS = pow(pow((double)s.x, 2.0) + pow((double)s.y, 2.0) + pow((double)s.z, 2.0), 0.5);
			double apsE = pow(pow((double)e.x, 2.0) + pow((double)e.y, 2.0) + pow((double)e.z, 2.0), 0.5);
			double se = s.x*e.x + s.y*e.y + s.z*e.z;
			double angle = acos(se/(apsS*apsE));
			particles.at(i).angle = angle / (2*3.14159) * 360;

			particles.at(i).y += particles.at(i).vel * particles.at(i).dY;
			particles.at(i).z += particles.at(i).vel * particles.at(i).dZ;
			particles.at(i).x += particles.at(i).vel * particles.at(i).dX;

			particles.at(i).life--;

			if (particles.at(i).life == 0) {
				particles.erase(particles.begin()+i);
			}
		}

		myDisplay();
		previousTime = currentTime;
	}
}

void myReshape(int width, int height)
{
	width = width;                      	
    height = height;						
    glViewport(0, 0, width, height);	
	
	glMatrixMode(GL_PROJECTION);                
    glLoadIdentity();                           
 
    gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,150.0f);
 
    glMatrixMode(GL_MODELVIEW);                
    glLoadIdentity();                          

	glLoadIdentity();						
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );		
	glClear( GL_COLOR_BUFFER_BIT );				
	glPointSize(1.0);							
	glColor3f(0.0f, 0.0f, 0.0f);				
}

void myKeyboard(unsigned char key, int x, int y) {
	if(key == 'a') source.x -= 0.5;
	if(key == 'd') source.x += 0.5;
	if(key == 'q') source.z -= 0.5;
	if(key == 'e') source.z += 0.5;
	if(key == 's') source.y -= 0.5;
	if(key == 'w') source.y += 0.5;

	if(key == 'y' && parCount > 0) parCount--;
	if(key == 'x' && parCount < 99) parCount++;

	if(key == 'l') cam.x -= 0.5;
	if(key == 'j') cam.x += 0.5;
	if(key == 'o') cam.z -= 0.5;
	if(key == 'u') cam.z += 0.5;
	if(key == 'i') cam.y -= 0.5;
	if(key == 'k') cam.y += 0.5;
	if(key == 'r'){
		cam.x = 0.0;
		cam.y = 0.0;
		cam.z = 50.0;
	} 
}

GLuint loadTexture( const char * filename, int width, int height)
{
    GLuint texture;
    BYTE * data;
    FILE * file;
	int wrap = 0;

    file = fopen( filename, "rb" );
    if ( file == NULL )  {
		return 0;
	}

    data =(BYTE*) malloc( width * height * 3 );

    fread( data, width * height * 3, 1, file );
    fclose( file );

    glGenTextures( 1, &texture );

    glBindTexture( GL_TEXTURE_2D, texture );

    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                     GL_LINEAR_MIPMAP_NEAREST );

    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                     wrap ? GL_REPEAT : GL_CLAMP );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
                     wrap ? GL_REPEAT : GL_CLAMP );

    gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height,
                       GL_RGB, GL_UNSIGNED_BYTE, data );

    free( data );

    return texture;
}

int main(int argc, char ** argv)
{
  	source.x = 0.0; 
	source.y = 0.0; 
	source.z = 0.0;
	  
  	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(width,height);
	glutInitWindowPosition(100,100);
	glutInit(&argc, argv);

	glutCreateWindow("");
	glutReshapeFunc(myReshape);
	glutDisplayFunc(myDisplay);
	glutKeyboardFunc(myKeyboard);
	glutIdleFunc(myIdle);

  	glBlendFunc(GL_SRC_ALPHA,GL_ONE);
	glEnable(GL_BLEND);
	
    glEnable( GL_TEXTURE_2D );
    glBindTexture( GL_TEXTURE_2D, loadTexture("snow.bmp", 256, 256));

	glutMainLoop();
    	return 0;
}