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
	QLineEdit *status;
	QGridLayout *cols;
	QListView *entList;
	QStandardItemModel *entModel;
	GLwindow *gl;

	public slots:
	void setViewName(const QModelIndex &);

	public:
	void buildEntList();
	t3MLEditor(t3_masterList *mlin, QWidget *parent = NULL);
};

#endif