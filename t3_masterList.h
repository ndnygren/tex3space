

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

	~t3_masterList();
};

std::ostream& operator<<(std::ostream& os, const t3_masterList& rhs);
std::istream& operator>>(std::istream& os, t3_masterList& rhs);


#endif
