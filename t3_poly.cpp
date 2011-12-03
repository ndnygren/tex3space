#include "t3_poly.h"

using namespace std;

int t3_poly::size() const
{
	return list.size();
}

t3_point t3_poly::get(int idx) const
{
	return list[idx];
}

void t3_poly::clear()
{
	list.clear();
}

void t3_poly::addPoint(const t3_point& np)
{
	list.push_back(np);
}

void t3_poly::addPoint(int x, int y, int z)
{
	list.push_back(t3_point(x,y,z));
}

t3_point& t3_poly::operator[](int i)
{
	return list[i];
}

ostream& operator<<(ostream& os, const t3_poly& rhs)
{
	int i;

	os << '{';

	for (i = 0; i < rhs.size(); i++)
	{
		os << rhs.get(i);
		if (i+1 != rhs.size())
		{
			os << ',';
		}
	}

	os << '}';

	return os;
}

istream& operator>>(istream& is, t3_poly& rhs)
{
	t3_point tp;
	char ch;

	rhs.clear();

	is.ignore(256, '{');

	do
	{
		is >> tp;
		rhs.addPoint(tp);
		is >> ws >> ch;
		
	} while (ch != '}');
	
	
	return is;
}
