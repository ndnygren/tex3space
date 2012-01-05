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
#ifndef NN_T3ENTPRIMATIVE_H
#define NN_T3ENTPRIMATIVE_H

#include "t3_ent.h"


/**
 *@brief The child class of t3_ent representing primative entities.
 *@details This class contains a vector of polygons(t3_poly)
 */
class t3_entPrimative: public t3_ent
{
	protected:
	/**
	 * @brief the list of polygons that make up this entity
	 */
	std::vector<t3_poly> list;

	public:
	virtual int size() const;
	virtual t3_poly get(int idx) const;
	virtual void addPoly(const t3_poly& poly);
	virtual std::vector<t3_poly> allPoly() const;
	virtual int subEntSize() const;
	virtual t3_sixtuple& getSubEnt(int idx);
	virtual std::string str() const;
	virtual void addSubEnt(double x, double y, double z, double yaw, double roll, const std::string& name);
	t3_entPrimative(const std::string& inname);

	virtual ~t3_entPrimative() {}
};


#endif
