
#include "t3_point.h"

using namespace std;

t3_point::t3_point()
{
	x = 0;
	y = 0;
	z = 0;
}

t3_point::t3_point(long long int xin, long long int yin, long long int zin)
{
	x = xin;
	y = yin;
	z = zin;
}

ostream& operator<<(ostream& os, const t3_point& rhs)
{
	os << "(" << rhs.x << "," << rhs.y << "," << rhs.z << ")";
	return os;
}

istream& operator>>(istream& is, t3_point& rhs)
{
	is.ignore(10, '(');
	is >> rhs.x;
	is.ignore(10, ',');
	is >> rhs.y;
	is.ignore(10, ',');
	is >> rhs.z;
	is.ignore(10, ')');

	return is;
}
