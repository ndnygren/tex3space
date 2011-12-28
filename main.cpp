#include <iostream>
#include <fstream>
#include "t3_masterList.h"
#include "gui/GLwindow.h"
#include "gui/t3MLEditor.h"

using namespace std;

int main(int argc, char **argv)
{
	QApplication app(argc, argv);
	ifstream ifile;
	t3_masterList ml;
	t3MLEditor window(&ml);

	if (argc > 1)
	{
		cout << "attemping to load: " <<  argv[1] << "." << endl;

		ifile.open(argv[1]);

		if (!ifile.fail())
		{
			ifile >> ml;
			window.buildEntList();
			cout << "status: file loaded:" <<  argv[1] << "." << endl;
			ifile.close();
		}
		else
		{
			cout << "error: could not load test file:" <<  argv[1] << "." << endl;
		}
	}
	window.show();
	app.exec();

	return 0;
}