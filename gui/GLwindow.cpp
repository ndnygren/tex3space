
#include "GLwindow.h"
#include <iostream>
#include <vector>

using namespace std;

GLfloat GLwindow::spec[4] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat GLwindow::shiny[1] = { 50.0 };
GLfloat GLwindow::lpos[4] = { 1.0, 1.0, 1.0, 0.0 };
GLfloat GLwindow::amb[4] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat GLwindow::diff[4] = { 1.0, 1.0, 1.0, 1.0 };

void GLwindow::setCurrentName(const std::string& input)
{
	currentName = input;
}

void GLwindow::setYaw(int in) 
{ 
	yaw = in; 
	updateGL();
}

void GLwindow::paintGL()
{
	int i,j;
	float zNear = 0.01;
	float zFar = 1000.0;
	float fov = 45.0;
	float aspect = (float)width() / (float)height();
	double min_x,max_x,min_y,max_y,min_z,max_z;
	min_x = max_x = min_y = max_y = min_z = max_z = 0;
	vector<t3_poly> toppoly;

	if (ml->exists(currentName)) 
	{
		toppoly = ml->getEntity(currentName)->allPoly();
	}

	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spec);
	glMaterialfv(GL_FRONT, GL_SHININESS, shiny);
	glLightfv(GL_LIGHT0, GL_POSITION, lpos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);
	glEnable(GL_LIGHT0);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	if (toppoly.size() > 0)
	{
		min_x = max_x = toppoly[0][0].x;
		min_y = max_y = toppoly[0][0].y;
		min_z = max_z = toppoly[0][0].z;
	}

	for (i = 0; i < (int)toppoly.size(); i++)
	{
		for (j = 0; j < (int)toppoly[i].size(); j++)
		{
			if (toppoly[i][j].x < min_x){ min_x = toppoly[i][j].x; }
			if (toppoly[i][j].x > max_x){ max_x = toppoly[i][j].x; }
			if (toppoly[i][j].y < min_y){ min_y = toppoly[i][j].y; }
			if (toppoly[i][j].y > max_y){ max_y = toppoly[i][j].y; }
			if (toppoly[i][j].z < min_z){ min_z = toppoly[i][j].z; }
			if (toppoly[i][j].z > max_z){ max_z = toppoly[i][j].z; }
		}
	}


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluPerspective(fov, aspect, zNear, zFar);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glColor4f(1.0, 1.0, 1.0, 1.0);

	glTranslatef((min_x+max_x)/-2.0, (min_y+max_y)/-2.0,
		-1.2*max(max_x-min_x, max_y-min_y));

//	glRotatef(m_rotation.x, 1, 0, 0);
	glRotatef(yaw, 0, 1, 0);
//	glRotatef(m_rotation.z, 0, 0, 1);

	for (i = 0; i < (int)toppoly.size(); i++)
	{
		glBegin(GL_LINES);
		glVertex3f(toppoly[i][0].x, toppoly[i][0].y, toppoly[i][0].z);
		for (j = 0; j < (int)toppoly[i].size(); j++)
		{
			glVertex3f(toppoly[i][j].x, toppoly[i][j].y, toppoly[i][j].z);
			glVertex3f(toppoly[i][j].x, toppoly[i][j].y, toppoly[i][j].z);
		}
		glVertex3f(toppoly[i][0].x, toppoly[i][0].y, toppoly[i][0].z);

		glEnd();
	}

	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
}

void GLwindow::resizeGL(int width, int height)
{
	float zNear = 0.01;
	float zFar = 1000.0;
	float fov = 45.0;
	float aspect = (float)width / (float)height;
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluPerspective(fov, aspect, zNear, zFar);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	
}

void GLwindow::keyPressEvent(QKeyEvent* event) 
{
	if (event->key() == Qt::Key_Escape) { close(); }
/*	else if (event->key() == Qt::Key_Up) { cam_y += 10; }
	else if (event->key() == Qt::Key_Down) { cam_y -= 10; }
	else if (event->key() == Qt::Key_Left) { cam_x -= 10; }
	else if (event->key() == Qt::Key_Right) { cam_x += 10; }*/
	else { event->ignore(); }
}

GLwindow::GLwindow(t3_masterList *mlin, QWidget *parent) : QGLWidget(parent) 
{
	setFixedSize(screen_w, screen_h);
	ml = mlin;

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	currentName = "top";
	yaw = 0;
}
