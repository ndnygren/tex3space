
#include "t3_masterList.h"
#include "t3_entPrimative.h"
#include <sstream>

using namespace std;

void t3_masterList::addEntity(t3_ent* input)
{
	entity[input->getName()] = input;
}

t3_ent* t3_masterList::getEntity(const std::string& name) const
{
	return (*entity.find(name)).second;
}

string t3_masterList::str() const
{
	map<string, t3_ent*>::const_iterator it;
	stringstream ss;

	for (it = entity.begin(); it != entity.end(); it++)
	{
		ss << *((*it).second) << endl;
	}

	return ss.str();
}

ostream& operator<<(ostream& os, const t3_masterList& rhs)
{
	os << rhs.str();
	return os;
}

istream& operator>>(istream& is, t3_masterList& rhs)
{
	char buffer[50];
	char ch;
	string type;
	string name;
	t3_ent *newent;
	t3_poly poly;
	
	is.ignore(256, '\\');
	is.getline(buffer, 50, '[');
	type = buffer;
	if (type == "primative")
	{
		is.getline(buffer, 50, ']');
		name = buffer;
		newent = new t3_entPrimative(name);
		rhs.addEntity(newent);

		is.ignore(256,'{');

		do
		{
			is >> poly;
			newent->addPoly(poly);
			is >> ws >> ch;
		} while (ch != '}');
	}
	
	return is;
}


