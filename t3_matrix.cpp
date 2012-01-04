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
#include "t3_matrix.h"
#include <cmath>

void t3_matrix::makeRoll(double angle)
{
	data[0][0] = cos(angle*3.1415927/180.0);
	data[0][1] = -sin(angle*3.1415927/180.0);
	data[1][0] = sin(angle*3.1415927/180.0);
	data[1][1] = cos(angle*3.1415927/180.0);
	data[2][2] = 1;
	data[1][2] = 0;
	data[0][2] = 0;
	data[2][1] = 0;
	data[2][0] = 0;
}

void t3_matrix::makeYaw(double angle)
{
	data[0][0] = cos(angle*3.1415927/180.0);
	data[0][1] = 0;
	data[0][2] = sin(angle*3.1415927/180.0);
	data[1][0] = 0;
	data[1][1] = 1;
	data[1][2] = 0;
	data[2][0] = -sin(angle*3.1415927/180.0);
	data[2][1] = 0;
	data[2][2] = cos(angle*3.1415927/180.0);
}

t3_point t3_matrix::operator*(const t3_point& rhs) const
{
	t3_point output;
	output.x = data[0][0]*rhs.x + data[0][1]*rhs.y + data[0][2]*rhs.z;
	output.y = data[1][0]*rhs.x + data[1][1]*rhs.y + data[1][2]*rhs.z;
	output.z = data[2][0]*rhs.x + data[2][1]*rhs.y + data[2][2]*rhs.z;

	return output;
}

t3_matrix t3_matrix::operator*(const t3_matrix& rhs) const
{
	int i,j,k;
	double sum;
	t3_matrix output;
	
	for (i = 0; i < 3; i++)
	for (j = 0; j < 3; j++)
	{
		sum = 0;
		for (k = 0; k < 3; k++)
		{
			sum += data[i][k] * rhs.data[k][j];
		}
		output.data[i][j] = sum;
	}
	return output;
}
