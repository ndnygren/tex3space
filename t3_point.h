
#ifndef NN_T3POINT_H
#define NN_T3POINT_H

#include <iostream>

class t3_point
{
	public:
	long long int x;
	long long int y;
	long long int z;

	t3_point();

	t3_point(long long int xin, long long int yin, long long int zin = 0);
};

std::ostream& operator<<(std::ostream& os, const t3_point& rhs);
std::istream& operator>>(std::istream& is, t3_point& rhs);

#endif

