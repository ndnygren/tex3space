
#include "t3_masterList.h"
#include "t3_entPrimative.h"
#include "t3_entComposite.h"
#include <sstream>
#include <vector>

using namespace std;


bool t3_masterList::exists(const std::string& input) const
{
		return entity.count(input);
}

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
	t3_sixtuple six("");

	while (!is.eof())
	{
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
		else if (type == "composite")
		{
			is.getline(buffer, 50, ']');
			name = buffer;
			newent = new t3_entComposite(name, &rhs);
			rhs.addEntity(newent);

			is.ignore(256,'{');

			do
			{
				is >> six;
				newent->addSubEnt(six.x, six.y, six.z, six.yaw, six.roll, six.name);
				is >> ws >> ch;
			} while (ch != '}');
		}
	}

	return is;
}

string t3_masterList::texOutput() const
{
	double xdir;
	int i,j;
	stringstream ss;
	vector<t3_poly> toppoly = getEntity("top")->allPoly();

	ss << "\\documentclass[10pt]{article}" << endl;
	ss << "\\usepackage[margin=0.5in]{geometry}" << endl;
	ss << "\\usepackage{graphicx}" << endl;
	ss << "\\usepackage{amsmath}" << endl;
	ss << "\\usepackage{amsthm}" << endl;
	ss << "\\usepackage{amssymb}" << endl;
	ss << "\\usepackage{pict2e}" << endl;
	ss << "\\usepackage{subfig}" << endl;
	ss << "\\begin{document}" << endl;
	
	ss << "\\begin{picture}" << endl;

	for (i = 0; i < (int)toppoly.size(); i++)
	{
		for (j = 1; j < (int)toppoly[i].size(); j++)
		{
			xdir = toppoly[i][j-1].x;
			ss << "\t\\put(" << toppoly[i][j-1].x << "," << toppoly[i][j-1].y << "){";
			ss << "\\line(";
			ss << ")";
			ss << "}\n";
		}
	}

	ss << "\\end{picture}" << endl;

	ss << "\\end{document}" << endl;

	return ss.str();
}


vector<string> t3_masterList::allNames() const
{
	int i,j;
	string swap;
	map<string, t3_ent*>::const_iterator it;
	vector<string> names;
	names.reserve(entity.size() + 1);

	for (it = entity.begin(); it != entity.end(); it++)
	{
		names.push_back((*it).first);
	}

	for (i = (int)names.size() - 1; i > 0; i--)
	{
		for (j = i; j > 0 && names[j] < names[j-1]; j--)
		{
			swap = names[j];
			names[j] = names[j-1];
			names[j-1] = swap;
		}
	}

	return names;
}


t3_masterList::~t3_masterList()
{
	map<string, t3_ent*>::const_iterator it;

	for (it = entity.begin(); it != entity.end(); it++)
	{
		delete (*it).second;
	}
}
