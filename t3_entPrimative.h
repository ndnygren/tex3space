#ifndef NN_T3ENTPRIMATIVE_H
#define NN_T3ENTPRIMATIVE_H

#include "t3_ent.h"

class t3_entPrimative: public t3_ent
{
	protected:
	std::vector<t3_poly> list;

	public:
	virtual int size() const;
	virtual t3_poly get(int idx) const;
	virtual void addPoly(const t3_poly& poly);
	virtual int subEntSize() const;
	virtual std::string getSubEnt(int idx);
	virtual void addSubEnt(int x, int y, int z, const std::string& name) = 0;

	virtual ~t3_entPrimative() {}
};


#endif
