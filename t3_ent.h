#ifndef NN_T3ENT_H
#define NN_T3ENT_H

#include "t3_poly.h"
#include <string>

class t3_ent
{
	public:
	virtual int size() const = 0;
	virtual t3_poly get(int idx) const = 0;
	virtual void addPoly(const t3_poly& poly) = 0;
	virtual int subEntSize() const = 0;
	virtual std::string getSubEnt(int idx) = 0;
	virtual void addSubEnt(int x, int y, int z, const std::string& name) = 0;
	virtual bool isContainer() { return false; }

	virtual ~t3_ent() {}
};


#endif
