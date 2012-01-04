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


#ifndef NN_T3MASTERLIST_H
#define NN_T3MASTERLIST_H

#include "t3_ent.h"
#include <map>
#include <vector>

class t3_masterList
{
	protected:
	std::map<std::string, t3_ent*> entity;

	public:

	bool exists(const std::string& input) const;
	void addEntity(t3_ent* input);
	t3_ent* getEntity(const std::string& name) const;
	std::string texOutput() const;
	std::string str() const;
	std::vector<std::string> allNames() const;
	void clear();

	~t3_masterList();
};

std::ostream& operator<<(std::ostream& os, const t3_masterList& rhs);
std::istream& operator>>(std::istream& os, t3_masterList& rhs);


#endif
