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
#include "t3_poly.h"

using namespace std;

int t3_poly::size() const
{
	return list.size();
}

t3_point t3_poly::get(int idx) const
{
	return list[idx];
}

void t3_poly::clear()
{
	list.clear();
}

void t3_poly::addPoint(const t3_point& np)
{
	list.push_back(np);
}

void t3_poly::addPoint(int x, int y, int z)
{
	list.push_back(t3_point(x,y,z));
}

t3_point& t3_poly::operator[](int i)
{
	return list[i];
}

ostream& operator<<(ostream& os, const t3_poly& rhs)
{
	int i;

	os << '{';

	for (i = 0; i < rhs.size(); i++)
	{
		os << rhs.get(i);
		if (i+1 != rhs.size())
		{
			os << ',';
		}
	}

	os << '}';

	return os;
}

istream& operator>>(istream& is, t3_poly& rhs)
{
	t3_point tp;
	char ch;

	rhs.clear();

	is.ignore(256, '{');

	do
	{
		is >> tp;
		rhs.addPoint(tp);
		is >> ws >> ch;
		
	} while (ch != '}');
	
	
	return is;
}
