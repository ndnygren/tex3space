#include <iostream>
#include <sstream>
#include "t3_ent.h"


using namespace std;

int main()
{
	stringstream ss;
	t3_point pt;

	ss.str("  (    1  ,   2   ,   3   )  ");

	ss >> pt;

	cout << pt << endl;

	return 0;
}
