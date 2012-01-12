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
#include "t3MLEditor.h"
#include "primativeDialog.h"
#include "../t3_entPrimative.h"
#include "compositeDialog.h"
#include "editComposite.h"
#include "smartAddEntityDialog.h"
#include "recenterEntDialog.h"
#include "rotateEntDialog.h"
#include <fstream>

using namespace std;

string t3MLEditor::titlebar = "tex3space v0._ ";

void t3MLEditor::buildEntList()
{
	int i;
	vector<string> names = ml->allNames();
	entModel->clear();
	QStandardItem *item;

	for (i=0; i < (int)names.size(); i++)
	{
		item = new QStandardItem(QString(names[i].c_str()));
		item->setEditable(false);
		entModel->appendRow(item);
	}
}

void t3MLEditor::setViewName(const QModelIndex& input)
{
	gl->setCurrentName(input.data().toString().toStdString());
	gl->updateGL();
}

void t3MLEditor::newFile()
{
	this->setWindowTitle(titlebar.c_str());
	ml->clear();
	buildEntList();
	gl->updateGL();
}

void t3MLEditor::openFile()
{
	ifstream ifile;
	fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Files (*.*)"));


	ifile.open(fileName.toStdString().c_str());
	if (ifile.fail())
	{
		status->setText(QString("Error: could not open file."));
	}
	else
	{
		ml->clear();
		ifile >> *ml;
		ifile.close();

		if (ml->allNames().size() == 0)
		{
			status->setText(QString("Error: invalid file type."));
		}
		else
		{
			status->setText(QString("Status: file loaded."));
			this->setWindowTitle(titlebar.c_str() + fileName);
		}

	}
	buildEntList();

}

void t3MLEditor::saveFile()
{
	ofstream ofile;

	if (fileName == "")
	{
		return;
	}

	ofile.open(fileName.toStdString().c_str());
	if (ofile.fail())
	{
		status->setText(QString("Error: could not save file."));
	}
	else
	{
		ofile << *ml;
		ofile.close();
	}
}

void t3MLEditor::saveFileAs()
{
	fileName = QFileDialog::getSaveFileName(this, tr("Save File As"), "", tr("Files (*.*)"));
	saveFile();
}

void t3MLEditor::newPrimative()
{
	t3_entPrimative *prim;
	t3_poly poly;
	double h,w,d;
	primativeDialog dia(this);

	status->setText("");

	if (dia.exec())
	{
		prim = new t3_entPrimative(dia.getName());
		h = dia.getHeight();
		w = dia.getWidth();
		d = dia.getDepth();

		//draw Bottom
		poly.addPoint(t3_point(-w/2, 0, d/2));
		poly.addPoint(t3_point(w/2, 0, d/2));
		poly.addPoint(t3_point(w/2, 0, -d/2));
		poly.addPoint(t3_point(-w/2, 0, -d/2));
		prim->addPoly(poly);
		poly.clear();

		//draw Top
		poly.addPoint(t3_point(-w/2, h, d/2));
		poly.addPoint(t3_point(w/2, h, d/2));
		poly.addPoint(t3_point(w/2, h, -d/2));
		poly.addPoint(t3_point(-w/2, h, -d/2));
		prim->addPoly(poly);
		poly.clear(); 

		//draw left
		poly.addPoint(t3_point(-w/2, 0, -d/2));
		poly.addPoint(t3_point(-w/2, h, -d/2));
		poly.addPoint(t3_point(-w/2, h, d/2));
		poly.addPoint(t3_point(-w/2, 0, d/2));
		prim->addPoly(poly);
		poly.clear();

		//draw right
		poly.addPoint(t3_point(w/2, 0, -d/2));
		poly.addPoint(t3_point(w/2, h, -d/2));
		poly.addPoint(t3_point(w/2, h, d/2));
		poly.addPoint(t3_point(w/2, 0, d/2));
		prim->addPoly(poly);
		poly.clear();
		
		//draw front
		poly.addPoint(t3_point(-w/2, 0, d/2));
		poly.addPoint(t3_point(-w/2, h, d/2));
		poly.addPoint(t3_point(w/2, h, d/2));
		poly.addPoint(t3_point(w/2, 0, d/2));
		prim->addPoly(poly);
		poly.clear();

		//draw back
		poly.addPoint(t3_point(-w/2, 0, -d/2));
		poly.addPoint(t3_point(-w/2, h, -d/2));
		poly.addPoint(t3_point(w/2, h, -d/2));
		poly.addPoint(t3_point(w/2, 0, -d/2));
		prim->addPoly(poly);
		poly.clear();

		ml->addEntity(prim);
	}
	buildEntList();
}

void t3MLEditor::newComposite()
{
	t3_entComposite *ent;
	compositeDialog dia(this);

	status->setText("");

	if (dia.exec())
	{
			ent = new t3_entComposite(dia.getName(), ml);
			ml->addEntity(ent);
	}
	buildEntList();
}

void t3MLEditor::editComp()
{
	int i;
	t3_entComposite *ent;

	status->setText("");
	if (entList->currentIndex().row() == -1)
	{
		status->setText("Error: no entity selected.");
		return;
	}

	ent = (t3_entComposite*)(ml->getEntity(entList->currentIndex().data().toString().toStdString()));

	if (ent == 0 || !ent->isContainer())
	{
		status->setText("Error: entity is not composite.");
		return;
	}

	editComposite dia(this, ent);

	if (dia.exec())
	{
		for (i = 0; i < ent->subEntSize(); i++)
		{
			ent->getSubEnt(i).x = dia.getX(i);
			ent->getSubEnt(i).y = dia.getY(i);
			ent->getSubEnt(i).z = dia.getZ(i);
			ent->getSubEnt(i).yaw = dia.getYaw(i);
			ent->getSubEnt(i).roll = dia.getRoll(i);
			ent->getSubEnt(i).name = dia.getName(i);
		}
	}

	for (i = 0; i < ent->subEntSize(); i++)
	{
		if (ent->getSubEnt(i).name == "")
		{
			ent->removeSubEnt(i);
		}
	}

}

void t3MLEditor::deleteEnt()
{
	if (entList->currentIndex().row() == -1)
	{
		status->setText("Error: no entity selected.");
		return;
	}

	
	if (ml->deleteEntity(entList->currentIndex().data().toString().toStdString()))
		{ status->setText("Entity removed."); }
	else
		{ status->setText("Error: could not remove entity"); }
	
	buildEntList();
}

void t3MLEditor::recenterEnt()
{
	if (entList->currentIndex().row() == -1)
	{
		status->setText("Error: no entity selected.");
		return;
	}
	
	if (!ml->exists(entList->currentIndex().data().toString().toStdString()))
	{
		status->setText("Error: entity does not exist.");
		return;
	}

	t3_ent *ent = ml->getEntity(entList->currentIndex().data().toString().toStdString());
	recenterEntDialog dia(this, t3_ent::findMaxMin(ent->allPoly()));

	if (dia.exec())
	{
		status->setText("Entity successfully re-centered.");
		ent->recenter(dia.getX(), dia.getY(), dia.getZ());
	}
	else
	{
		status->setText("");
	}
}

void t3MLEditor::rotateEnt()
{
	status->setText("");
	if (entList->currentIndex().row() == -1)
	{
		status->setText("Error: no entity selected.");
		return;
	}
	
	if (!ml->exists(entList->currentIndex().data().toString().toStdString()))
	{
		status->setText("Error: entity does not exist.");
		return;
	}

	t3_ent *ent = ml->getEntity(entList->currentIndex().data().toString().toStdString());
	rotateEntDialog dia(this, ent->isContainer());

	if (dia.exec())
	{
		status->setText("Entity rotated.");
		if (dia.isYaw()) { ent->rotate(dia.getAngle(), t3_ent::TYPE_YAW); }
		else if (dia.isRoll()) { ent->rotate(dia.getAngle(), t3_ent::TYPE_ROLL); }
		else if (dia.isPitch()) { ent->rotate(dia.getAngle(), t3_ent::TYPE_PITCH); }
	}
}

void t3MLEditor::addToComp()
{
	t3_ent::minmax6tuple mm_new, mm_comp;
	t3_entComposite *ent;
	string newname, oldname;

	oldname = entList->currentIndex().data().toString().toStdString();

	if (entList->currentIndex().row() == -1)
	{
		status->setText("Error: no entity selected.");
		return;
	}

	smartAddEntityDialog dia(this, oldname, ml);
	ent = (t3_entComposite*)(ml->getEntity(oldname));
	
	if (ent == 0 || !ent->isContainer())
	{
		status->setText("Error: entity is not composite.");
		return;
	}

	if (dia.exec())
	{
		newname = dia.getName();

		if (!ml->exists(newname)) { return; }

		mm_new = t3_ent::findMaxMin(ml->getEntity(newname)->allPoly());
		mm_comp = t3_ent::findMaxMin(ml->getEntity(oldname)->allPoly());


		if (ent->subEntSize() == 0)
		{
			ent->addSubEnt(0, 0, 0, 0, 0, newname);
		}
		else if (dia.isTop())
		{
			ent->addSubEnt(0, mm_comp.max_y - mm_new.min_y + dia.getGap(), 0, 0, 0, newname);
		}
		else if (dia.isBottom())
		{
			ent->addSubEnt(0, mm_comp.min_y - mm_new.max_y - dia.getGap(), 0, 0, 0, newname);
		}
		else if (dia.isLeft())
		{
			ent->addSubEnt(mm_comp.min_x - mm_new.max_x - dia.getGap(), 0, 0, 0, 0, newname);
		}
		else if (dia.isRight())
		{
			ent->addSubEnt(mm_comp.max_x - mm_new.min_x + dia.getGap(), 0, 0, 0, 0, newname);
		}
		else if (dia.isFront())
		{
			ent->addSubEnt(0, 0, mm_comp.max_z - mm_new.min_z + dia.getGap(), 0, 0, newname);
		}
		else if (dia.isBack())
		{
			ent->addSubEnt(0, 0, mm_comp.min_z - mm_new.max_z - dia.getGap(), 0, 0, newname);
		}

	}
}

void t3MLEditor::exportSVG()
{
	ofstream ofile;
	exportDialog dia(this);
	if (dia.exec())
	{
		QString svgName = QFileDialog::getSaveFileName(this, tr("Export File As"), "", tr("SVG Files (*.svg)"));
	
		ofile.open(svgName.toStdString().c_str());
		if (ofile.fail())
		{
			status->setText(QString("Error: could not export file."));
		}
		else
		{
			if (dia.top())
			{
				ofile << ml->getEntity(entList->currentIndex().data().toString().toStdString())->topSVG();
			}
			else if (dia.front())
			{
				ofile << ml->getEntity(entList->currentIndex().data().toString().toStdString())->frontSVG();
			}
			else
			{
				ofile << ml->getEntity(entList->currentIndex().data().toString().toStdString())->sideSVG();
			}
			ofile.close();
		}
	}
}

t3MLEditor::t3MLEditor(t3_masterList *mlin, QWidget *parent) : QWidget(parent) 
{
	QHBoxLayout *hbuttonbox = new QHBoxLayout();
	this->setWindowTitle(titlebar.c_str());
	fileName = "";
	ml = mlin;

	nPrButton = new QPushButton("New Primative");
	nPrButton->setMaximumWidth(110);
	nCmButton = new QPushButton("New Composite");
	nCmButton->setMaximumWidth(110);
	edCmpButton = new QPushButton("Edit Composite");
	edCmpButton->setMaximumWidth(110);
	delButton = new QPushButton("Delete");
	delButton->setMaximumWidth(80);
	addCompButton = new QPushButton("Add To...");
	addCompButton->setMaximumWidth(80);
	recenterButton = new QPushButton("Re-Center");
	recenterButton->setMaximumWidth(90);
	rotateButton = new QPushButton("Rotate");
	rotateButton->setMaximumWidth(80);

	hslide = new QSlider(Qt::Horizontal);
	hslide->setMinimum(-179);
	hslide->setMaximum(180);
	hslide->setValue(0);

	cols = new QGridLayout();
	status = new QLineEdit("started");
	entList = new QListView();
	entModel = new QStandardItemModel();
	entList->setModel(entModel);
	entList->setMinimumWidth(200);
	gl = new GLwindow(mlin);

	menuBar = new QMenuBar();
	fileMenu = menuBar->addMenu(tr("&File"));

	newAct = new QAction(tr("&New"), this);
	newAct->setShortcuts(QKeySequence::New);
	newAct->setStatusTip(tr("Create a new file"));
	connect(newAct,SIGNAL(triggered()),this,SLOT(newFile()));

	openAct = new QAction(tr("&Open"), this);
	openAct->setShortcuts(QKeySequence::Open);
	openAct->setStatusTip(tr("Open an existing file"));
	connect(openAct,SIGNAL(triggered()),this,SLOT(openFile()));

	saveAct = new QAction(tr("&Save"), this);
	saveAct->setShortcuts(QKeySequence::Save);
	saveAct->setStatusTip(tr("Save file"));
	connect(saveAct,SIGNAL(triggered()),this,SLOT(saveFile()));

	saveAsAct = new QAction(tr("Save &As"), this);
	saveAsAct->setStatusTip(tr("Save file under new location"));
	connect(saveAsAct,SIGNAL(triggered()),this,SLOT(saveFileAs()));

	exitAct = new QAction(tr("E&xit"), this);
	exitAct->setStatusTip(tr("Close program"));

	fileMenu->addAction(newAct);
	fileMenu->addSeparator();
	fileMenu->addAction(openAct);
	fileMenu->addAction(saveAct);
	fileMenu->addAction(saveAsAct);
	fileMenu->addSeparator();
	fileMenu->addAction(exitAct);

	exportMenu = menuBar->addMenu(tr("E&xport"));
	toSVGAct = new QAction(tr("to &SVG"), this);
	toSVGAct->setStatusTip(tr("Export diagram to SVG"));
	exportMenu->addAction(toSVGAct);
	connect(toSVGAct,SIGNAL(triggered()),this,SLOT(exportSVG()));

	hbuttonbox->addWidget(nPrButton);
	hbuttonbox->addWidget(nCmButton);
	hbuttonbox->addWidget(edCmpButton);
	hbuttonbox->addWidget(delButton);
	hbuttonbox->addWidget(addCompButton);
	hbuttonbox->addWidget(recenterButton);
	hbuttonbox->addWidget(rotateButton);

	cols->setMenuBar(menuBar);
	cols->addWidget(entList,0,0,2,1);
	cols->addWidget(gl,0,1);
	cols->addWidget(hslide,1,1);
	cols->addLayout(hbuttonbox, 2, 0, 1, 2);
	cols->addWidget(status,3,0, 1,2);
	setLayout(cols);

	connect(hslide, SIGNAL(valueChanged(int)), gl, SLOT(setYaw(int)));
	connect(entList, SIGNAL(activated(const QModelIndex &)), this, SLOT(setViewName(const QModelIndex &)));
	connect(nPrButton, SIGNAL(clicked()), this, SLOT(newPrimative()));
	connect(nCmButton, SIGNAL(clicked()), this, SLOT(newComposite()));
	connect(edCmpButton, SIGNAL(clicked()), this, SLOT(editComp()));
	connect(delButton, SIGNAL(clicked()), this, SLOT(deleteEnt()));
	connect(addCompButton, SIGNAL(clicked()), this, SLOT(addToComp()));
	connect(recenterButton, SIGNAL(clicked()), this, SLOT(recenterEnt()));
	connect(rotateButton, SIGNAL(clicked()), this, SLOT(rotateEnt()));

	buildEntList();
}

