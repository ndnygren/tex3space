
#ifndef NN_T3POINT_H
#define NN_T3POINT_H

#include <iostream>

class t3_point
{
	public:
	double x;
	double y;
	double z;

	t3_point();

	t3_point(double xin, double yin, double zin = 0);
};

std::ostream& operator<<(std::ostream& os, const t3_point& rhs);
std::istream& operator>>(std::istream& is, t3_point& rhs);

#endif

