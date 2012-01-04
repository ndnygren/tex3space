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
#include "../t3_entComposite.h"

#ifndef NN_EDITCOMPOSITEDIA_H
#define NN_EDITCOMPOSITEDIA_H

class editComposite : public QDialog
{
	Q_OBJECT

	private:
	QStringList headers;
	t3_entComposite *entity;
	QTableView *table;
	QStandardItemModel *model;
	QPushButton *done, *cancel, *newrow;

	void rebuildTable();

	public slots:
	void addNewRow();

	public:
	static std::string dtostd(double input);
	static double stdtod(std::string input);
	int size() const;
	double getX(int i) const;
	double getY(int i) const;
	double getZ(int i) const;
	double getYaw(int i) const;
	double getRoll(int i) const;
	std::string getName(int i) const;
	editComposite(QWidget *par, t3_entComposite *input);
};

#endif

