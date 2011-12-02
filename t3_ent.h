#ifndef NN_T3ENT_H
#define NN_T3ENT_H

#include "t3_poly.h"

class t3_ent
{
	protected:
	std::string name;

	public:
	virtual int size() const = 0;
	virtual t3_poly get(int idx) const = 0;
	virtual void addPoly(const t3_poly& poly) = 0;
	virtual int subEntSize() const = 0;
	virtual std::string getSubEnt(int idx) = 0;
	virtual std::string str() const = 0;
	virtual void addSubEnt(int x, int y, int z, const std::string& name) = 0;
	virtual bool isContainer() { return false; }

	virtual ~t3_ent() {}
};

std::ostream& operator<<(std::ostream& os, const t3_ent& rhs);

#endif
