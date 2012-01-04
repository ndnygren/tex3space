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
#include <fstream>

using namespace std;

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
	this->setWindowTitle("tex3space v0._");
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
			this->setWindowTitle("tex3space v0._ - " + fileName);
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
	t3_entComposite *ent = (t3_entComposite*)(ml->getEntity(entList->currentIndex().data().toString().toStdString()));
	if (ent == 0 || !ent->isContainer())
	{
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
	this->setWindowTitle("tex3space v0._");
	fileName = "";
	ml = mlin;
	nPrButton = new QPushButton("New Primative");
	nCmButton = new QPushButton("New Composite");
	edCmpButton = new QPushButton("Edit Composite");
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

	cols->setMenuBar(menuBar);
	cols->addWidget(entList,0,0);
	cols->addWidget(gl,0,1);
	cols->addWidget(hslide,1,1);
	cols->addLayout(hbuttonbox, 1, 0);
	cols->addWidget(status,2,0,1,0);
	setLayout(cols);

	connect(hslide, SIGNAL(valueChanged(int)), gl, SLOT(setYaw(int)));
	connect(entList, SIGNAL(activated(const QModelIndex &)), this, SLOT(setViewName(const QModelIndex &)));
	connect(nPrButton, SIGNAL(clicked()), this, SLOT(newPrimative()));
	connect(nCmButton, SIGNAL(clicked()), this, SLOT(newComposite()));
	connect(edCmpButton, SIGNAL(clicked()), this, SLOT(editComp()));

	buildEntList();
}

