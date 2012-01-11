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
#include "t3_entPrimative.h"
#include <sstream>

using namespace std;

t3_sixtuple t3_ent::nulltuple("");

int t3_entPrimative::size() const
{
	return list.size();
}

t3_poly t3_entPrimative::get(int idx) const
{
	return list[idx];
}

void t3_entPrimative::addPoly(const t3_poly& poly)
{
	list.push_back(poly);
}

vector<t3_poly> t3_entPrimative::allPoly() const
{
	return list;
}

int t3_entPrimative::subEntSize() const
{
	return 0;
}

t3_sixtuple& t3_entPrimative::getSubEnt(int idx)
{
	return nulltuple;
}

std::string t3_entPrimative::str() const
{
	int i;
	stringstream ss;

	ss << "\\primative[";
	ss << name << "]" << endl << "{" << endl;
	for (i = 0; i < (int)list.size(); i++)
	{
		ss << "\t" << list[i];
		if (i+1 != (int)list.size()) { ss << ", "; }
		ss << endl;
	}

	ss << "}";

	return ss.str();
}

void t3_entPrimative::addSubEnt(double x, double y, double z, double yaw, double roll, const string& name) { }

void t3_entPrimative::recenter(double dx, double dy, double dz)
{
	int i, j;

	for (i = 0; i < (int)list.size(); i++)
	{
		for (j = 0; j < list[i].size(); j++)
		{
			list[i][j].x -= dx;
			list[i][j].y -= dy;
			list[i][j].z -= dz;
		}
	}
}

t3_entPrimative::t3_entPrimative(const string& inname)
{
	name = inname;
}

ostream& operator<<(ostream& os, const t3_ent& rhs)
{
	os << rhs.str();
	return os;
}
