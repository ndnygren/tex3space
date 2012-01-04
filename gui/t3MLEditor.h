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
#include <QtGui>
#include "GLwindow.h"
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

	QMenuBar *menuBar;
	QMenu *fileMenu;
	QAction *newAct;
	QAction *openAct;
	QAction *saveAct;
	QAction *saveAsAct;
	QAction *exitAct;
	QMenu *exportMenu;
	QAction *toSVGAct;
	QPushButton *nPrButton, *nCmButton, *edCmpButton;
	QSlider *hslide;

	protected:
	QString fileName;

	public slots:
	void setViewName(const QModelIndex &);
	void newFile();
	void openFile();
	void saveFile();
	void saveFileAs();
	void newPrimative();
	void newComposite();
	void editComp();
	void exportSVG();

	public:
	void buildEntList();
	t3MLEditor(t3_masterList *mlin, QWidget *parent = NULL);
};

#endif

