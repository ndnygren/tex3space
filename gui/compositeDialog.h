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


#endif