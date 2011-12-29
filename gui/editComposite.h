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