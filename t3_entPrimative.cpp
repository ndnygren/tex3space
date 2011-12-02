#include "t3_entPrimative.h"

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

void t3_entPrimative::addSubEnt(int x, int y, int z, const string& name) { }

