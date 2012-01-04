#include <QtGui>

#ifndef NN_CONSOLEOUTPUT_H
#define NN_CONSOLEOUTPUT_H

class consoleOutput : public QWidget
{
	Q_OBJECT
	private:
	QHBoxLayout *hbox;
	QTextEdit *textbox;

	public:

	consoleOutput();
};


#endif

