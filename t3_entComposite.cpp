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
#include "t3_entComposite.h"
#include "t3_matrix.h"
#include <sstream>

using namespace std;

int t3_entComposite::size() const { return 0; }

t3_poly t3_entComposite::get(int idx) const
{
	return t3_poly();
}

void t3_entComposite::addPoly(const t3_poly& poly) { }

vector<t3_poly> t3_entComposite::allPoly() const
{
	int i, j, k;
	vector<t3_poly> outlist;
	vector<t3_poly> templist;
	t3_matrix yawmat, rollmat;
	t3_poly tp;

	for (i = 0; i < subEntSize(); i++)
	{
		if (ml->exists(subent[i].name))
		{
			templist = ml->getEntity(subent[i].name)->allPoly();
		}
		else
		{
			templist.clear();
		}
		yawmat.makeYaw(subent[i].yaw);
		rollmat.makeRoll(subent[i].roll);
		for (j = 0; j < (int)templist.size(); j++)
		{
			tp = templist[j];
			for (k = 0; k < tp.size(); k++)
			{
				tp[k] = yawmat*tp[k];
				tp[k] = rollmat*tp[k];
				tp[k].x += subent[i].x;
				tp[k].y += subent[i].y;
				tp[k].z += subent[i].z;
			}
			outlist.push_back(tp);
		}
	}

	return outlist;
}

int t3_entComposite::subEntSize() const
{
	return subent.size();
}

t3_sixtuple& t3_entComposite::getSubEnt(int idx)
{
	return subent[idx];
}

string t3_entComposite::str() const
{
	int i;
	stringstream ss;
	ss << "\\composite[" << getName() << "]" << endl <<"{" << endl;

	for (i = 0; i < subEntSize(); i++)
	{
		ss << "\t" << subent[i];
		if (i + 1 != subEntSize())
		{
			ss << ","; 
		}
		ss << endl;
	}

	ss << "}";

	return ss.str();
}

void t3_entComposite::addSubEnt(double x, double y, double z, double yaw, double roll, const string& name)
{
	subent.push_back(t3_sixtuple(x, y, z, yaw, roll, name));
}

void t3_entComposite::removeSubEnt(int i)
{
	subent.erase(subent.begin() + i);
}

void t3_entComposite::recenter(double dx, double dy, double dz)
{
	int i;

	for (i = 0; i < subEntSize(); i++)
	{
		getSubEnt(i).x -= dx;
		getSubEnt(i).y -= dy;
		getSubEnt(i).z -= dz;
	}
}

ostream& operator<<(ostream& os, const t3_sixtuple& rhs)
{
	os << "(" << rhs.x << "," << rhs.y << "," << rhs.z << "," << rhs.yaw << "," << rhs.roll << "," << rhs.name << ")";
	return os;
}

istream& operator>>(istream& is, t3_sixtuple& rhs)
{
	char buffer[50];
	
	is.ignore(256, '(');
	is >> rhs.x;
	is.ignore(256, ',');
	is >> rhs.y;
	is.ignore(256, ',');
	is >> rhs.z;
	is.ignore(256, ',');
	is >> rhs.yaw;
	is.ignore(256, ',');
	is >> rhs.roll;
	is.ignore(256, ',');
	is.getline(buffer,256, ')');
	rhs.name = buffer;

	return is;
}
