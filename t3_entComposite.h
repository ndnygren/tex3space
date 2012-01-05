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
#include "t3_ent.h"
#include "t3_masterList.h"

#ifndef NN_T3ENTCOMPOSITE_H
#define NN_T3ENTCOMPOSTIE_H


/**
 * @brief The child entity of t3_ent which represents a list of othe entities
 * @details This class contains a list of other entities, either primative or composite with parameters for each decsribing rotations and translations.
 */
class t3_entComposite : public t3_ent
{
	protected:
	/**
	 * @brief The list of all sub-entities
	 */
	std::vector<t3_sixtuple> subent;

	/**
	 * @brief The master list of entities which allows this entity to make recursive calls to subentities.
	 */
	t3_masterList *ml;

	public:
	virtual int size() const;
	virtual t3_poly get(int idx) const;
	virtual void addPoly(const t3_poly& poly);
	virtual std::vector<t3_poly> allPoly() const;
	virtual int subEntSize() const;
	virtual t3_sixtuple& getSubEnt(int idx);
	virtual std::string str() const;
	virtual void addSubEnt(double x, double y, double z, double yaw, double roll, const std::string& name);
	virtual void removeSubEnt(int i);
	virtual bool isContainer() { return true; }

	t3_entComposite(const std::string& inname, t3_masterList* mlin) 
	{
		name = inname; 
		ml = mlin;
	}

	virtual ~t3_entComposite() {}
};

#endif
