#include <QtGui>
#include "../t3_entComposite.h"

#ifndef NN_EDITCOMPOSITEDIA_H
#define NN_EDITCOMPOSITEDIA_H

class editComposite : public QDialog
{
	Q_OBJECT

	private:
	static QStringList headers;
	t3_entComposite *entity;
	QListView *list;
	QStandardItemModel *model;
	QPushButton *done, *cancel;

	public:
	editComposite(QWidget *par, t3_entComposite *input);
};

#endif