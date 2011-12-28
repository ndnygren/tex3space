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