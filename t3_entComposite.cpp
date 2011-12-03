#include "t3_entComposite.h"
#include <sstream>

using namespace std;

int t3_entComposite::size() const { return 0; }

t3_poly t3_entComposite::get(int idx) const
{
	return t3_poly();
}

void t3_entComposite::addPoly(const t3_poly& poly) { }

int t3_entComposite::subEntSize() const
{
	return subent.size();
}

t3_sixtuple& t3_entComposite::getSubEnt(int idx)
{
	return subent[idx];
}

string t3_entComposite::str() const
{
	int i;
	stringstream ss;
	ss << "\\composite[" << getName() << "]" << endl <<"{" << endl;

	for (i = 0; i < subEntSize(); i++)
	{
		ss << "\t" << subent[i];
		if (i + 1 != subEntSize())
		{
			ss << ","; 
		}
		ss << endl;
	}

	ss << "}";

	return ss.str();
}

void t3_entComposite::addSubEnt(int x, int y, int z, int yaw, int roll, const string& name)
{
	subent.push_back(t3_sixtuple(x, y, z, yaw, roll, name));
}


ostream& operator<<(ostream& os, const t3_sixtuple& rhs)
{
	os << "(" << rhs.x << "," << rhs.y << "," << rhs.z << "," << rhs.yaw << "," << rhs.roll << "," << rhs.name << ")";
	return os;
}

istream& operator>>(istream& is, t3_sixtuple& rhs)
{
	char buffer[50];
	
	is.ignore(256, '(');
	is >> rhs.x;
	is.ignore(256, ',');
	is >> rhs.y;
	is.ignore(256, ',');
	is >> rhs.z;
	is.ignore(256, ',');
	is >> rhs.yaw;
	is.ignore(256, ',');
	is >> rhs.roll;
	is.ignore(256, ',');
	is.getline(buffer,256, ')');
	rhs.name = buffer;

	return is;
}