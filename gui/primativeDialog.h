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

#ifndef NN_PRIMATIVEDIALOG_H
#define NN_PRIMATIVEDIALOG_H

class primativeDialog : public QDialog
{
	Q_OBJECT

	private:
	QGridLayout *cols;
	QLabel *labh, *labw, *labd, *labn;
	QLineEdit *height, *width, *depth, *name;
	QPushButton *done, *cancel;

	public:
	double getWidth() const;
	double getHeight() const;
	double getDepth() const;
	std::string getName() const;
	primativeDialog(QWidget *par);
};

#endif

