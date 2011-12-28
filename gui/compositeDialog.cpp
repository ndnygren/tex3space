#include "compositeDialog.h"

std::string compositeDialog::getName() const
{
	return name->text().toStdString();
}

compositeDialog::compositeDialog(QWidget *par): QDialog(par)
{
	QHBoxLayout *hbox = new QHBoxLayout();
	cols = new QGridLayout();
	labn = new QLabel(tr("Name:"));
	name = new QLineEdit();

	done = new QPushButton("Done");
	cancel = new QPushButton("Cancel");
	hbox->addWidget(done);
	hbox->addWidget(cancel);

	cols->addWidget(labn,0,0);
	cols->addWidget(name,0,1);
	cols->addLayout(hbox,1,0,1,0);

	connect(done,SIGNAL(clicked()),this,SLOT(accept()));
	connect(cancel,SIGNAL(clicked()),this,SLOT(reject()));

	setLayout(cols);
}