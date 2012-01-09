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
#include <iostream>
#include <fstream>
#include "gui/t3MLEditor.h"

using namespace std;

char *copyright = "tex3space - renders 2D projections of 3D objects for TeX  Copyright (C) 2012 Nick Nygren";

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

