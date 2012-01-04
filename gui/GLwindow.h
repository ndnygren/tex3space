/* tex3space - renders 2D projections of 3D objects for TeX
* Copyright (C) 2012 Nick Nygren
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>. */
#ifndef NN_T3GLWINDOW_H
#define NN_T3GLWINDOW_H

#include <QtGui>
#include <QtOpenGL/QGLWidget>
#include "../t3_masterList.h"

class GLwindow : public QGLWidget 
{
	Q_OBJECT

protected:
	static GLfloat spec[4];
	static GLfloat shiny[1];
	static GLfloat lpos[4];
	static GLfloat amb[4];
	static GLfloat diff[4];

	t3_masterList *ml;
	void keyPressEvent(QKeyEvent *event);
	void paintGL();
	void resizeGL(int width, int height);
	std::string currentName;
	int yaw;

public slots:
	void setYaw(int in);

public:	
	static const int screen_w = 640;
	static const int screen_h = 360;
	void setCurrentName(const std::string& input);
	GLwindow(t3_masterList *mlin, QWidget *parent = NULL);
};

#endif
