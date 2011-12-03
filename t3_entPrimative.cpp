#include "t3_entPrimative.h"
#include <sstream>

using namespace std;

int t3_entPrimative::size() const
{
	return list.size();
}

t3_poly t3_entPrimative::get(int idx) const
{
	return list[idx];
}

void t3_entPrimative::addPoly(const t3_poly& poly)
{
	list.push_back(poly);
}

int t3_entPrimative::subEntSize() const
{
	return 0;
}

string t3_entPrimative::getSubEnt(int idx)
{
	return "";
}

std::string t3_entPrimative::str() const
{
	int i;
	stringstream ss;

	ss << "\\primative[";
	ss << name << "]" << endl << "{" << endl;
	for (i = 0; i < (int)list.size(); i++)
	{
		ss << "\t" << list[i];
		if (i+1 != (int)list.size()) { ss << ", "; }
		ss << endl;
	}

	ss << "}";

	return ss.str();
}

void t3_entPrimative::addSubEnt(int x, int y, int z, const string& name) { }

t3_entPrimative::t3_entPrimative(const string& inname)
{
	name = inname;
}

ostream& operator<<(ostream& os, const t3_ent& rhs)
{
	os << rhs.str();
	return os;
}
