#ifndef NN_T3ENT_H
#define NN_T3ENT_H

#include "t3_poly.h"

class t3_ent
{
	public:
	virtual int size() const = 0;
	virtual t3_poly get(int idx) const = 0;
	virtual int subEntSize() const = 0;
	virtual t3_ent* getSubEnt(int idx) = 0;

	virtual ~t3_ent() {}
};


#endif
