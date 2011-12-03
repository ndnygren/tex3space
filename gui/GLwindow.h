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

public:
	static const int screen_w = 640;
	static const int screen_h = 480;
	GLwindow(t3_masterList *mlin, QWidget *parent = NULL);
};

#endif
