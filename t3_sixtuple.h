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
#ifndef NN_T3SIXTUPLE_H
#define NN_T3SIXTUPLE_H


/**
 * @brief A container for composite parameters. These values describe the translations and rotations of a sub-entity.
 */
class t3_sixtuple
{
	public:
	double x;
	double y;
	double z;
	double yaw;
	double roll;
	std::string name;

	t3_sixtuple(std::string inname)
	{
		x = 0;
		y = 0;
		z = 0;
		yaw = 0;
		roll = 0;
		name = inname;
	}

	t3_sixtuple(double xin, double yin, double zin, double yawin, double rollin, std::string inname)
	{
		x = xin;
		y = yin;
		z = zin;
		yaw = yawin;
		roll = rollin;
		name = inname;
	}
};

std::ostream& operator<<(std::ostream& os, const t3_sixtuple& rhs);
std::istream& operator>>(std::istream& is, t3_sixtuple& rhs);


#endif
