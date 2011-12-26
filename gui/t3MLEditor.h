#include <QtGui>
#include "GLWindow.h"
#include "../t3_masterList.h"

#ifndef NN_T3MLEDITOR_H
#define NN_T3MLEDITOR_H


class t3MLEditor : public QWidget
{
	Q_OBJECT

	private:
	t3_masterList *ml;
	QGridLayout *cols;
	QListView *entList;
	QAbstractItemModel *entModel;
	GLwindow *gl;

	public:
	t3MLEditor(t3_masterList *mlin, QWidget *parent = NULL);
};


#endif