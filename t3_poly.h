
#ifndef NN_T3POLY_H
#define NN_T3POLY_H


#include "t3_point.h"
#include <vector>

class t3_poly
{
	protected:
	std::vector<t3_point> list;

	public:
	int size() const;
	t3_point get(int idx) const;
	void clear();
	void addPoint(const t3_point& np);
	void addPoint(int x, int y, int z);
};

std::ostream& operator<<(std::ostream& os, const t3_poly& rhs);
std::istream& operator>>(std::istream& is, t3_poly& rhs);

#endif
