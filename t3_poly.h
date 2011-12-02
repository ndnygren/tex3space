
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
	void addPoint(const t3_point& np);
};

#endif
