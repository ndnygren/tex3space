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

#ifndef NN_T3POINT_H
#define NN_T3POINT_H

#include <iostream>


/**
 * @brief a triple of doubles, representing a point in R^3
 */
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

