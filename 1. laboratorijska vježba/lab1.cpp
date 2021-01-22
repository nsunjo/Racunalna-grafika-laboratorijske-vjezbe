#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <windows.h>

#include <string>
#include <fstream>
#include <vector>
#include "util.h"

using namespace std;

int numOfPol = 0, numOfVer = 0, numOfSpline = 0, numOfSeg = 0;
int currentT = 0; int previousT = 0, t = 0;

Poly *polygons;
Vertex *vertices, *vertex, *path, *tang, *orient;
Vertex center(0.0, 0.0, 0.0);
Vertex os(0.0, 0.0, 0.0);
Vertex s(0.0, 0.0, 1.0);
Vertex e(0.0, 0.0, 0.0);
GLuint width = 800, height = 800;

void loadObject(){
	
	vector<string> file;
  
  	ifstream ifs("kocka.obj");
  	string temp;

  	while( getline( ifs, temp ) )
     	file.push_back( temp );

  	for (int i = 0; i < file.size(); i++) {
	  	if (file.at(i).at(0) == 'f') numOfPol++;
	  	else if (file.at(i).at(0) == 'v') numOfVer++;
  	}

  	vertices = (Vertex *) malloc (numOfVer * sizeof(Vertex));
  	polygons = (Poly *) malloc (numOfPol * sizeof(Poly));


  	int oV = 0, oP = 0;

  	for (int i = 0; i < file.size(); i++) {
	  	if (file.at(i).at(0) == 'v') {
		 	float d1, d2, d3;
		  	char *text = new char[file.at(i).size()+1];
		  	std::copy(file.at(i).begin(), file.at(i).end(), text);
		  	sscanf(text, "v %f %f %f", &d1, &d2, &d3);
		  	d1 *= 4; d2 *= 4; d3 *= 4;
		  	center.x += d1; center.y += d2; center.z += d3;
		  	Vertex v(d1, d2, d3);
		  	vertices[oV] = v;
		  	oV++;
	  	}
  	}
  	center.x /= oV; 
	center.y /= oV; 
	center.z /= oV;

  	for (int i = 0; i < file.size(); i++) {
	  	if (file.at(i).at(0) == 'f') {
		  	int d1, d2, d3;
		  	char *text = new char[file.at(i).size()+1];
		  	std::copy(file.at(i).begin(), file.at(i).end(), text);
		  	sscanf(text, "f %d %d %d", &d1, &d2, &d3);
		  	Poly p(&vertices[d1-1], &vertices[d2-1], &vertices[d3-1]);
		  	polygons[oP] = p;
		  	oP++;
	  	}
  	}
  	file.clear();
}

void loadPath(){
	vector<string> file;

  	ifstream ifs2("bSpline.txt");
  	string temp2;

  	while( getline( ifs2, temp2 ) )
     	file.push_back( temp2 );
  
  	numOfSpline = file.size();
  	vertex = (Vertex *) malloc (numOfSpline * sizeof(Vertex));
  	numOfSeg = numOfSpline - 3;
	
  	for (int i = 0; i < numOfSpline; i++) {
		float d1, d2, d3;
		char *text = new char[file.at(i).size()+1];
		std::copy(file.at(i).begin(), file.at(i).end(), text);
		sscanf(text, "%f %f %f", &d1, &d2, &d3);
		Vertex v(d1, d2, d3);
		vertex[i] = v;
  	}

}

void drawObject(){
		glBegin(GL_LINES);
	for (int i = 0; i < numOfPol; i++) {
		Vertex v1 = *polygons[i].v1;
		Vertex v2 = *polygons[i].v2;
		Vertex v3 = *polygons[i].v3;
		
		glColor3f(1.0, 0.0, 1.0);
		glVertex3f(v1.x, v1.y, v1.z);
		glVertex3f(v2.x, v2.y, v2.z);

		glVertex3f(v2.x, v2.y, v2.z);
		glVertex3f(v3.x, v3.y, v3.z);

		glVertex3f(v3.x, v3.y, v3.z);
		glVertex3f(v1.x, v1.y, v1.z);
	}
	
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(center.x, center.y, center.z);
	glVertex3f(center.x + 5, center.y, center.z);

	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(center.x, center.y, center.z);
	glVertex3f(center.x, center.y + 5, center.z);

	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(center.x, center.y, center.z);
	glVertex3f(center.x, center.y, center.z + 5);

	glColor3f(1.0, 1.0, 1.0);
	glEnd();
}

void myReshape(int width, int height)
{
	width = width;                      	
    height = height;						

    glViewport(0, 0, width, height);	
	glMatrixMode(GL_PROJECTION);               
    glLoadIdentity();                          
    gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);
    glMatrixMode(GL_MODELVIEW);                 
    glLoadIdentity();                           
	glLoadIdentity();							
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );		
	glClear( GL_COLOR_BUFFER_BIT );				
	glPointSize(1.0);							
	glColor3f(1.0f, 1.0f, 1.0f);			
}

void myDisplay()
{
	glLoadIdentity();
 	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glTranslatef(-5.0, -5.0, -65.0);
	glBegin (GL_LINE_STRIP);
	for(int i = 0; i < 100*numOfSeg; i++) {
		glVertex3f(path[i].x, path[i].y, path[i].z);
	}
	glEnd();

	glBegin (GL_LINES);
	for (int i = 0; i < numOfSeg*8; i+=2) {
		glVertex3f(tang[i].x, tang[i].y, tang[i].z);
		glVertex3f(tang[i+1].x, tang[i+1].y, tang[i+1].z);
	}
	glEnd();

	glTranslatef(path[t].x, path[t].y, path[t].z);
	
	e.x = orient[2*t+1].x - orient[2*t].x;
	e.y = orient[2*t+1].y - orient[2*t].y;
	e.z = orient[2*t+1].z - orient[2*t].z;
	
	os.x = s.y*e.z - e.y*s.z;
	os.y = e.x*s.z - s.x*e.z;
	os.z = s.x*e.y - s.y*e.x;

	double apsS = pow(pow((double)s.x, 2.0) + pow((double)s.y, 2.0) + pow((double)s.z, 2.0), 0.5);
	double apsE = pow(pow((double)e.x, 2.0) + pow((double)e.y, 2.0) + pow((double)e.z, 2.0), 0.5);
	double se = s.x*e.x + s.y*e.y + s.z*e.z;
	double kut = acos(se/(apsS*apsE));
	kut = kut / (2*3.1415) * 360;
	glRotatef(kut, os.x, os.y, os.z);
	
	glTranslatef(-center.x, -center.y, -center.z);

	drawObject();

	t++;
	if (t == 100*numOfSeg) t = 0;

	glFlush();
}

void myIdle() {
	currentT = glutGet(GLUT_ELAPSED_TIME);
	int timeInterval = currentT - previousT;
	if(timeInterval > 5) {
		myDisplay();
		previousT = currentT;
	}
}

int main(int argc, char ** argv){
	
	loadObject();
	loadPath();

  	path = (Vertex *) malloc (100 * numOfSeg * sizeof(Vertex));
  	tang = (Vertex *) malloc (numOfSeg *8 * sizeof(Vertex));
  	orient = (Vertex *) malloc (numOfSeg * 2 * 100 * sizeof(Vertex));
  	int tangPr = 0, tangN = 0;

  	for (int i = 0; i < numOfSeg; i++) {
		Vertex r0 = vertex[i];
	 	Vertex r1 = vertex[i+1];
	  	Vertex r2 = vertex[i+2];
	  	Vertex r3 = vertex[i+3];

	  	for (int j = 0; j < 100; j++) {
			float t = j/100.0;

			float f1 = (- pow(t,3.0) + 3*pow(t,2.0) - 3*t + 1) / 6.0;
			float f2 = (3*pow(t,3.0) - 6*pow(t,2.0) + 4) / 6.0;
			float f3 = (- 3*pow(t,3.0) + 3*pow(t,2.0) + 3*t + 1) / 6.0;
			float f4 = pow(t,3.0) / 6.0;

			path[100*i + j].x = f1*r0.x + f2*r1.x + f3*r2.x + f4*r3.x;
			path[100*i + j].y = f1*r0.y + f2*r1.y + f3*r2.y + f4*r3.y;
			path[100*i + j].z = f1*r0.z + f2*r1.z + f3*r2.z + f4*r3.z;
		  
			float t1 = 0.5 * (-pow(t, 2.0) + 2*t -1);
			float t2 = 0.5 * (3 * pow(t, 2.0) - 4*t);
			float t3 = 0.5 * (-3* pow(t, 2.0) + 2*t +1);
			float t4 = 0.5 * (pow(t, 2.0));

			orient[tangN].x = path[100*i + j].x;
			orient[tangN].y = path[100*i + j].y;
			orient[tangN].z = path[100*i + j].z;
			
			float vx = t1*r0.x + t2*r1.x + t3*r2.x + t4*r3.x;
			float vy = t1*r0.y + t2*r1.y + t3*r2.y + t4*r3.y;
			float vz = t1*r0.z + t2*r1.z + t3*r2.z + t4*r3.z;
			  
			orient[tangN+1].x = orient[tangN].x + vx;
			orient[tangN+1].y = orient[tangN].y + vy;
			orient[tangN+1].z = orient[tangN].z + vz;
			tangN+=2;

			if (j % 25 == 0 ) {
				tang[tangPr].x = path[100*i + j].x;
				tang[tangPr].y = path[100*i + j].y;
				tang[tangPr].z = path[100*i + j].z;
				
			  
				tang[tangPr+1].x = tang[tangPr].x + vx/2;
				tang[tangPr+1].y = tang[tangPr].y + vy/2;
				tang[tangPr+1].z = tang[tangPr].z + vz/2;
				tangPr+=2;
			}
		}
  	}

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(width,height);
	glutInitWindowPosition(100,100);
	glutInit(&argc, argv);

	glutCreateWindow("");
	glutReshapeFunc(myReshape);
	glutDisplayFunc(myDisplay);
	glutIdleFunc(myIdle);
	glutMainLoop();
    
	return 0;
}