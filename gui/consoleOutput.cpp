

#include "consoleOutput.h"

consoleOutput::consoleOutput()
{
	textbox = new QTextEdit();
	hbox = new QHBoxLayout();
	hbox->addWidget(textbox);

	setLayout(hbox);
}

