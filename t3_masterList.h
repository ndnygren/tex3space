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


/**
 * @brief A list of entities. 
 * @details Used primarily as a catalog for t3_entComposite elements to make recursive calls to sub entities. Also used to organize the list of entities for the GUI.
 * Saving and loading of files is done using stream operators with the class.
 */
class t3_masterList
{
	protected:
	/**
	 * @brief the storage for all entities
	 */
	std::map<std::string, t3_ent*> entity;

	public:

	/**
	 * @brief Tests whether or not the given entity exists
	 * @param input the name of the entity in question
	 * @returns true if the entity exists, false otherwise
	 */
	bool exists(const std::string& input) const;

	/**
	 * @brief Adds an entity to the list
	 * @param input the address of the entity to add.
	 */
	void addEntity(t3_ent* input);

	/**
	 * @brief read-only access to the entities in the list
	 * @param name The name of the entity to return
	 * @returns the address of the entity
	 */
	t3_ent* getEntity(const std::string& name) const;

	/**
	 * @brief renders a diagram of the entity in LaTeX format
	 * @returns a string containing the diagram.
	 */
	std::string texOutput() const;

	/**
	 * @brief The output of the entire list, to be used in save files.
	 * @returns All details contained in this list, in string form
	 */
	std::string str() const;

	/**
	 * @brief returns the names of all objects in the list
	 * @returns a vector contain a list of all names
	 */
	std::vector<std::string> allNames() const;

	/**
	 * @brief deletes all entities in the list, freeing memory.
	 */
	void clear();

	~t3_masterList();
};

std::ostream& operator<<(std::ostream& os, const t3_masterList& rhs);
std::istream& operator>>(std::istream& os, t3_masterList& rhs);


#endif
