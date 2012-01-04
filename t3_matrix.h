/* tex3space - renders 2D projections of 3D objects for TeX
* Copyright (C) 2012 Nick Nygren
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>. */

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
