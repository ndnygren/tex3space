#include "editComposite.h"

QStringList editComposite::headers;

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
	list = new QListView();
	model = new QStandardItemModel();
	model->setHorizontalHeaderLabels(headers);
	list->setModel(model);

	vbox->addWidget(list);
	vbox->addLayout(hbox);
	
	hbox->addWidget(done);
	hbox->addWidget(cancel);

	connect(done,SIGNAL(clicked()),this,SLOT(accept()));
	connect(cancel,SIGNAL(clicked()),this,SLOT(reject()));

	entity = input;
	setLayout(vbox);
}