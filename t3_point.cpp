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

#include "t3_point.h"

using namespace std;

t3_point::t3_point()
{
	x = 0;
	y = 0;
	z = 0;
}

t3_point::t3_point(double xin, double yin, double zin)
{
	x = xin;
	y = yin;
	z = zin;
}

ostream& operator<<(ostream& os, const t3_point& rhs)
{
	os << "(" << rhs.x << "," << rhs.y << "," << rhs.z << ")";
	return os;
}

istream& operator>>(istream& is, t3_point& rhs)
{
	is.ignore(10, '(');
	is >> rhs.x;
	is.ignore(10, ',');
	is >> rhs.y;
	is.ignore(10, ',');
	is >> rhs.z;
	is.ignore(10, ')');

	return is;
}
