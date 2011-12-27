#include "t3MLeditor.h"
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
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Files (*.*)"));
	ifstream ifile;

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

t3MLEditor::t3MLEditor(t3_masterList *mlin, QWidget *parent) : QWidget(parent) 
{
	ml = mlin;
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

	fileMenu->addAction(newAct);
	fileMenu->addAction(openAct);
	
	cols->setMenuBar(menuBar);
	cols->addWidget(entList,0,0);
	cols->addWidget(gl,0,1);
	cols->addWidget(status,1,1);
	setLayout(cols);

	connect(entList, SIGNAL(clicked(const QModelIndex &)), this, SLOT(setViewName(const QModelIndex &)));

	buildEntList();
}