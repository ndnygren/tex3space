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
#include "primativeDialog.h"

double primativeDialog::getWidth() const
{
	return width->text().toDouble();
}

double primativeDialog::getHeight() const
{
	return height->text().toDouble();
}

double primativeDialog::getDepth() const
{
	return depth->text().toDouble();
}

std::string primativeDialog::getName() const
{
	return name->text().toStdString();
}

primativeDialog::primativeDialog(QWidget *par) : QDialog(par)
{
	QHBoxLayout *hbox = new QHBoxLayout();
	QValidator *doubleval = new QDoubleValidator(this);
	cols = new QGridLayout();
	labh = new QLabel(tr("Height:"));
	labw = new QLabel(tr("Width:"));
	labd = new QLabel(tr("Depth:"));
	labn = new QLabel(tr("Name:"));

	height = new QLineEdit();
	height->setValidator(doubleval);
	width = new QLineEdit();
	width->setValidator(doubleval);
	depth = new QLineEdit();
	depth->setValidator(doubleval);
	name = new QLineEdit();

	done = new QPushButton("Done");
	cancel = new QPushButton("Cancel");

	hbox->addWidget(done);
	hbox->addWidget(cancel);

	cols->addWidget(labn,0,0);
	cols->addWidget(name,0,1);
	cols->addWidget(labw,1,0);
	cols->addWidget(width,1,1);
	cols->addWidget(labh,2,0);
	cols->addWidget(height,2,1);
	cols->addWidget(labd,3,0);
	cols->addWidget(depth,3,1);
	cols->addLayout(hbox,4,0,1,0);

	connect(done,SIGNAL(clicked()),this,SLOT(accept()));
	connect(cancel,SIGNAL(clicked()),this,SLOT(reject()));

	setLayout(cols);
}

