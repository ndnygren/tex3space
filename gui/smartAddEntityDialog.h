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
#include <vector>
#include <sstream>
#include "../t3_masterList.h"

#ifndef NN_SMARTADDENTITYDIALOG_H
#define NN_SMARTADDENTITYDIALOG_H

class smartAddEntityDialog : public QDialog
{
	Q_OBJECT

	private:
	QComboBox *combo;
	QStandardItemModel *model;
	QVBoxLayout *vbox;
	QHBoxLayout *hbox, *hbox2;
	QLineEdit *gapsize;
	QLabel *gaplabel;
	QGridLayout *radiogrid;
	QRadioButton *lb, *rb, *hb, *ub, *fb, *bb;
	QButtonGroup *radiogroup;
	QPushButton *accbutton, *decbutton;

	public:
	std::string getName() const
	{
		return combo->itemText(combo->currentIndex()).toStdString();
	}

	double getGap() const
	{
		double g = 0;
		std::stringstream ss(gapsize->text().toStdString());
		ss >> g;

		return g;
	}

	bool isLeft() const { return lb->isChecked(); }
	bool isRight() const { return rb->isChecked(); }
	bool isTop() const { return hb->isChecked(); }
	bool isBottom() const { return ub->isChecked(); }
	bool isFront() const { return fb->isChecked(); }
	bool isBack() const { return bb->isChecked(); }


	smartAddEntityDialog(QWidget *par, std::string name, t3_masterList *ml) : QDialog(par)
	{
		int i;
		std::string diatitle = "Add To " + name;
		std::vector<std::string> names = ml->allNames();
		QStandardItem *item;
		QValidator *doubleval = new QDoubleValidator(this);


		model = new QStandardItemModel();
		combo = new QComboBox();
		combo->setModel(model);

		for (i=0; i < (int)names.size(); i++)
		{
			if (name != names[i])
			{
				item = new QStandardItem(QString(names[i].c_str()));
				item->setEditable(false);
				model->appendRow(item);
			}
		}

		vbox = new QVBoxLayout();
		hbox = new QHBoxLayout();
		hbox2 = new QHBoxLayout();
		radiogrid = new QGridLayout();
		
		gapsize = new QLineEdit();
		gapsize->setValidator(doubleval);
		gaplabel = new QLabel("Gap:");

		lb = new QRadioButton("to Left");
		rb = new QRadioButton("to Right");
		hb = new QRadioButton("to Top");
		ub = new QRadioButton("to Bottom");
		fb = new QRadioButton("to Front");
		bb = new QRadioButton("to Back");

		lb->setChecked(true);

		accbutton = new QPushButton("Accept");
		decbutton = new QPushButton("Cancel");

		radiogrid->addWidget(lb, 0, 0);
		radiogrid->addWidget(rb, 0, 1);
		radiogrid->addWidget(hb, 1, 0);
		radiogrid->addWidget(ub, 1, 1);
		radiogrid->addWidget(fb, 2, 0);
		radiogrid->addWidget(bb, 2, 1);

		hbox->addWidget(accbutton);
		hbox->addWidget(decbutton);

		hbox2->addWidget(gaplabel);
		hbox2->addWidget(gapsize);

		vbox->addWidget(combo);
		vbox->addLayout(radiogrid);
		vbox->addLayout(hbox2);
		vbox->addLayout(hbox);
		
		connect(accbutton, SIGNAL(clicked()), this, SLOT(accept()));
		connect(decbutton, SIGNAL(clicked()), this, SLOT(reject()));

		gapsize->setText("0");

		setLayout(vbox);
		setWindowTitle(diatitle.c_str());
	}
};



#endif


