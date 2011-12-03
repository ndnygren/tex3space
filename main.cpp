#include <iostream>
#include <sstream>
#include "t3_masterList.h"


using namespace std;

int main()
{
	stringstream ss;
	t3_masterList ml;

	ss.str("\\primative[name]{{(1,2,3),(4,5,6),(6,5,4)},{(3,21,6),(653,34,2),(867,45,334)}}");
	ss >> ml;

	cout << ml << endl;

	return 0;
}
