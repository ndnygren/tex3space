#include "t3MLeditor.h"

using namespace std;

t3MLEditor::t3MLEditor(t3_masterList *mlin, QWidget *parent) : QWidget(parent) 
{
	ml = mlin;
	cols = new QGridLayout();

	entList = new QListView();
	entModel = new QStandardItemModel();
	entList->setModel(entModel);
	entList->setMinimumWidth(200);
	gl = new GLwindow(mlin);

	cols->addWidget(entList,0,0);
	cols->addWidget(gl,0,1);
	setLayout(cols);
}