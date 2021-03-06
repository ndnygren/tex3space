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

#ifndef NN_COMPOSITEDIALOG_H
#define NN_COMPOSITEDIALOG_H

class compositeDialog : public QDialog
{
	Q_OBJECT
	private:
	QGridLayout *cols;
	QLabel *labn;
	QLineEdit *name;
	QPushButton *done, *cancel;


	public:
	std::string getName() const;
	compositeDialog(QWidget *par);
};

class exportDialog : public QDialog
{
	Q_OBJECT
	private:
	QVBoxLayout *vbox;
	QRadioButton *topbutton;
	QRadioButton *sidebutton;
	QRadioButton *frontbutton;
	QButtonGroup *buttongroup;
	QPushButton *done, *cancel;


	public:
	std::string getName() const;

	bool top() const { return topbutton->isChecked(); }
	bool front() const { return frontbutton->isChecked(); }
	bool side() const { return sidebutton->isChecked(); }

	exportDialog(QWidget *par) : QDialog(par)
	{
		QHBoxLayout *hbox = new QHBoxLayout();
		vbox = new QVBoxLayout();
		topbutton = new QRadioButton("Top");
		frontbutton = new QRadioButton("Front");
		sidebutton = new QRadioButton("Side");
		done = new QPushButton("Done");
		cancel = new QPushButton("Cancel");

		buttongroup = new QButtonGroup();
		buttongroup->addButton(topbutton);
		buttongroup->addButton(frontbutton);
		buttongroup->addButton(sidebutton);

		vbox->addWidget(topbutton);
		vbox->addWidget(frontbutton);
		vbox->addWidget(sidebutton);
		hbox->addWidget(done);
		hbox->addWidget(cancel);
		vbox->addLayout(hbox);

		topbutton->setChecked(true);
		connect(done,SIGNAL(clicked()),this,SLOT(accept()));
		connect(cancel,SIGNAL(clicked()),this,SLOT(reject()));
		setLayout(vbox);
	}
};


#endif

