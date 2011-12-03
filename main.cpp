#include <iostream>
#include <fstream>
#include "t3_masterList.h"
#include "gui/GLwindow.h"


using namespace std;

int main(int argc, char **argv)
{
	QApplication app(argc, argv);
	ifstream ifile;
	t3_masterList ml;
	GLwindow window(&ml);

	ifile.open("testfile");

	ifile >> ml;

	ifile.close();

	window.show();

	app.exec();

	return 0;
}
