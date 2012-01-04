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
	t3_point& operator[](int i);
};

std::ostream& operator<<(std::ostream& os, const t3_poly& rhs);
std::istream& operator>>(std::istream& is, t3_poly& rhs);

#endif
