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


/**
 * @brief A list of points descibing a polygon
 */
class t3_poly
{
	protected:
	/**
	 * @brief the list of points
	 */
	std::vector<t3_point> list;

	public:
	/**
	 * @brief the size of the polygon in points
	 * @returns the number of points
	 */
	int size() const;

	/**
	 * @brief read-only access to a point
	 * @param idx the index of the desired point
	 * @returns the point at idx
	 */
	t3_point get(int idx) const;

	/**
	 * @brief removes all points in the polygon
	 */
	void clear();

	/**
	 * @brief adds a point to the polygon
	 * @param np the new point to add
	 */
	void addPoint(const t3_point& np);

	/**
	 * @brief adds a point to the polygon
	 * @param x the x coordinate of the point to add
	 * @param y the y coordinate of the point to add
	 * @param z the z coordinate of the point to add
	 */
	void addPoint(int x, int y, int z);

	/**
	 * @brief read-write access to a point
	 * @param i the index to the point to retrieve
	 * @returns the address of the point
	 */
	t3_point& operator[](int i);
};

std::ostream& operator<<(std::ostream& os, const t3_poly& rhs);
std::istream& operator>>(std::istream& is, t3_poly& rhs);

#endif
