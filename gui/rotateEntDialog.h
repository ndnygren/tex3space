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
#include <sstream>
#include "../t3_ent.h"


#ifndef NN_ROTATEENTDIALOG_H
#define NN_ROTATEENTDIALOG_H

class rotateEntDialog : public QDialog
{
	Q_OBJECT

	private:
	QLabel *anglelab;
	QLineEdit *angle;
	QVBoxLayout *vbox;
	QHBoxLayout *hbox1, *hbox2, *hbox3;
	QRadioButton *yawButton, *rollButton, *pitchButton;
	QPushButton *accbutton, *decbutton;

	QString dtoqs(double x)
	{
		std::stringstream ss;
		ss << x;
		return QString(ss.str().c_str());
	}

	static double parseD(QString input)
	{
		double x;
		std::stringstream ss(input.toStdString());
		ss >> x;

		return x;
	}

	public:

	double getAngle() const { return parseD(angle->text()); }
	bool isYaw() const { return yawButton->isChecked(); }
	bool isRoll() const { return rollButton->isChecked(); }
	bool isPitch() const { return pitchButton->isChecked(); }

	rotateEntDialog(QWidget *par, bool composite) : QDialog(par)
	{
		QValidator *doubleval = new QDoubleValidator(this);
		std::string diatitle = "Rotate Entity";

		anglelab = new QLabel("Angle:");
		angle = new QLineEdit();
		angle->setText("0");

		angle->setValidator(doubleval);

		vbox = new QVBoxLayout();
		hbox1 = new QHBoxLayout();
		hbox2 = new QHBoxLayout();
		hbox3 = new QHBoxLayout();

		yawButton = new QRadioButton("Yaw");
		rollButton = new QRadioButton("Roll");
		pitchButton = new QRadioButton("Pitch");

		yawButton->setChecked(true);

		if (composite)
		{
			pitchButton->setDisabled(true);
		}

		accbutton = new QPushButton("Accept");
		decbutton = new QPushButton("Cancel");

		hbox1->addWidget(anglelab);
		hbox1->addWidget(angle);

		hbox2->addWidget(yawButton);
		hbox2->addWidget(rollButton);
		hbox2->addWidget(pitchButton);

		hbox3->addWidget(accbutton);
		hbox3->addWidget(decbutton);

		vbox->addLayout(hbox1);
		vbox->addLayout(hbox2);
		vbox->addLayout(hbox3);

		connect(accbutton, SIGNAL(clicked()), this, SLOT(accept()));
		connect(decbutton, SIGNAL(clicked()), this, SLOT(reject()));

		setLayout(vbox);
		setWindowTitle(diatitle.c_str());
	}
};


#endif
