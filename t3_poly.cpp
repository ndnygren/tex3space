#include "t3_poly.h"

int t3_poly::size() const
{
	return list.size();
}

t3_point t3_poly::get(int idx) const
{
	return list[idx];
}

void t3_poly::addPoint(const t3_point& np)
{
	list.push_back(np);
}
