#include <iostream>
#include <fstream>
#include "t3_masterList.h"


using namespace std;

int main()
{
	int i;
	ifstream ifile;
	t3_masterList ml;
	vector<t3_poly> polys;

	ifile.open("testfile");

	ifile >> ml;

	ifile.close();

	polys = ml.getEntity("top")->allPoly();

	for (i = 0; i < (int)polys.size(); i++)
	{
		cout << polys[i] << endl;
	}

	return 0;
}
