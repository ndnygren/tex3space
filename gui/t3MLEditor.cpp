#include "t3MLeditor.h"
#include "../t3_entPrimative.h"
#include "primativeDialog.h"
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
	ml->clear();
	buildEntList();
	gl->updateGL();
}

void t3MLEditor::openFile()
{
	ifstream ifile;
	fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Files (*.*)"));


	ifile.open(fileName.toStdString());
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

	ofile.open(fileName.toStdString());
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

t3MLEditor::t3MLEditor(t3_masterList *mlin, QWidget *parent) : QWidget(parent) 
{
	this->setWindowTitle("tex3space v0._");
	fileName = "";
	ml = mlin;
	nPrButton = new QPushButton("New Primative");
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
	saveAsAct->setShortcuts(QKeySequence::SaveAs);
	saveAsAct->setStatusTip(tr("Save file under new location"));
	connect(saveAsAct,SIGNAL(triggered()),this,SLOT(saveFileAs()));

	exitAct = new QAction(tr("E&xit"), this);
	exitAct->setShortcuts(QKeySequence::Quit);
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

	cols->setMenuBar(menuBar);
	cols->addWidget(entList,0,0);
	cols->addWidget(gl,0,1,0,1);
	cols->addWidget(nPrButton,1,0);
	cols->addWidget(status,2,1);
	setLayout(cols);

	connect(entList, SIGNAL(clicked(const QModelIndex &)), this, SLOT(setViewName(const QModelIndex &)));
	connect(nPrButton, SIGNAL(clicked()), this, SLOT(newPrimative()));

	buildEntList();
}