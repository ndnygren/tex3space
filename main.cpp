#include <iostream>
#include <fstream>
#include "t3_masterList.h"
#include "gui/GLwindow.h"
#include "gui/consoleOutput.h"

using namespace std;

int main(int argc, char **argv)
{
	QApplication app(argc, argv);
	ifstream ifile;
	t3_masterList ml;
	GLwindow window(&ml);
	consoleOutput co;

	if (argc < 2) { return 1; }

	cout << "attemping to load: " <<  argv[1] << "." << endl;

	ifile.open(argv[1]);

	if (!ifile.fail())
	{
		ifile >> ml;
		cout << "status: file loaded:" <<  argv[1] << "." << endl;
		ifile.close();
	}
	else
	{
		cout << "error: could not load test file:" <<  argv[1] << "." << endl;
	}

	window.show();
	co.show();
	app.exec();

	return 0;
}
