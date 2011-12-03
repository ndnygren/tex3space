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
	stringstream ss;
	ss << "\\composite[" << getName() << "]" << endl;

	return ss.str();
}

void t3_entComposite::addSubEnt(int x, int y, int z, int yaw, int roll, const string& name)
{
	subent.push_back(t3_sixtuple(x, y, z, yaw, roll, name));
}
