
#ifndef NN_T3MATRIX_H
#define NN_T3MATRIX_H

#include "t3_point.h"

class t3_matrix
{
	double data[3][3];

	public:
	void makeYaw(double angle);
	void makeRoll(double angle);
	
	t3_point operator*(const t3_point& rhs) const;
	t3_matrix operator*(const t3_matrix& rhs) const;
};


#endif
