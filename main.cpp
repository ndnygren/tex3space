#include <iostream>
#include <sstream>
#include "t3_ent.h"


using namespace std;

int main()
{
	stringstream ss;
	t3_poly poly;

	ss.str("{(1,2,3),(4,5,6),(6,5,4)}");
	ss >> poly;

	cout << poly << endl;

	return 0;
}
