#ifndef NN_T3ENT_H
#define NN_T3ENT_H

#include "t3_poly.h"

class t3_entPrimative: public t3_ent
{
	public:
	virtual int size() const;
	virtual t3_poly get(int idx) const;
	virtual int subEntSize() const;
	virtual t3_ent* getSubEnt(int idx);

	virtual ~t3_entPrimative() {}
};


#endif
