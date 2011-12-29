#include "editComposite.h"
#include <sstream>

using namespace std;

std::string editComposite::dtostd(double x)
{
	stringstream ss;
	ss << x;
	return ss.str();
}

double editComposite::stdtod(std::string input)
{
	stringstream ss;
	ss.str(input);
	double x;
	ss >> x;

	return x;
}

void editComposite::rebuildTable()
{
	int i;
	QDoubleValidator *dub = new QDoubleValidator();
	QLineEdit *idx;

	model->setHorizontalHeaderLabels(headers);

	for (i = model->rowCount(); i < entity->subEntSize(); i++)
	{
		model->setItem(i, 1, new QStandardItem());
		model->setItem(i, 1, new QStandardItem());
		model->setItem(i, 2, new QStandardItem());
		model->setItem(i, 3, new QStandardItem());
		model->setItem(i, 4, new QStandardItem());
		model->setItem(i, 5, new QStandardItem());
		

		idx = new QLineEdit();
		idx->setValidator(dub);
		idx->setText(QString(dtostd(entity->getSubEnt(i).x).c_str()));
		table->setIndexWidget(model->index(i,0), idx);
		idx = new QLineEdit();
		idx->setValidator(dub);
		idx->setText(QString(dtostd(entity->getSubEnt(i).y).c_str()));
		table->setIndexWidget(model->index(i,1), idx);
		idx = new QLineEdit();
		idx->setValidator(dub);
		idx->setText(QString(dtostd(entity->getSubEnt(i).z).c_str()));
		table->setIndexWidget(model->index(i,2), idx);
		idx = new QLineEdit();
		idx->setValidator(dub);
		idx->setText(QString(dtostd(entity->getSubEnt(i).yaw).c_str()));
		table->setIndexWidget(model->index(i,3), idx);
		idx = new QLineEdit();
		idx->setValidator(dub);
		idx->setText(QString(dtostd(entity->getSubEnt(i).roll).c_str()));
		table->setIndexWidget(model->index(i,4), idx);
		idx = new QLineEdit();
		idx->setText(QString(entity->getSubEnt(i).name.c_str()));
		table->setIndexWidget(model->index(i,5), idx);
	}
}

void editComposite::addNewRow()
{
	entity->addSubEnt(0,0,0,0,0,"");
	rebuildTable();
}

int editComposite::size() const
{
	return model->rowCount();
}

double editComposite::getX(int i) const
{
	return stdtod(((QLineEdit*)(table->indexWidget(model->index(i,0))))->text().toStdString());
}

double editComposite::getY(int i) const
{
	return stdtod(((QLineEdit*)(table->indexWidget(model->index(i,1))))->text().toStdString());
}

double editComposite::getZ(int i) const
{
	return stdtod(((QLineEdit*)(table->indexWidget(model->index(i,2))))->text().toStdString());
}

double editComposite::getYaw(int i) const
{
	return stdtod(((QLineEdit*)(table->indexWidget(model->index(i,3))))->text().toStdString());
}

double editComposite::getRoll(int i) const
{
	return stdtod(((QLineEdit*)(table->indexWidget(model->index(i,4))))->text().toStdString());
}

string editComposite::getName(int i) const
{
	return ((QLineEdit*)(table->indexWidget(model->index(i,5))))->text().toStdString();
}


editComposite::editComposite(QWidget* par, t3_entComposite* input) : QDialog(par)
{
	QVBoxLayout *vbox = new QVBoxLayout();
	QHBoxLayout *hbox = new QHBoxLayout();

	if (headers.size() == 0)
	{
		headers.push_back("x");
		headers.push_back("y");
		headers.push_back("z");
		headers.push_back("yaw");
		headers.push_back("roll");
		headers.push_back("name");
	}
	
	done = new QPushButton("Done");
	cancel = new QPushButton("Cancel");
	newrow = new QPushButton("New Item");
	table = new QTableView();
	model = new QStandardItemModel();
	table->setModel(model);

	vbox->addWidget(table);
	vbox->addLayout(hbox);
	
	hbox->addWidget(newrow);
	hbox->addWidget(done);
	hbox->addWidget(cancel);

	connect(newrow,SIGNAL(clicked()),this,SLOT(addNewRow()));
	connect(done,SIGNAL(clicked()),this,SLOT(accept()));
	connect(cancel,SIGNAL(clicked()),this,SLOT(reject()));

	entity = input;
	setLayout(vbox);
	setMinimumWidth(700);
	rebuildTable();
}