#include "t3MLeditor.h"

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

	cols->addWidget(entList,0,0);
	cols->addWidget(gl,0,1);
	cols->addWidget(status,1,1);
	setLayout(cols);

	connect(entList, SIGNAL(clicked(const QModelIndex &)), this, SLOT(setViewName(const QModelIndex &)));


	buildEntList();
}