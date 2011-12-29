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
	virtual std::vector<t3_poly> allPoly() const;
	virtual int subEntSize() const;
	virtual t3_sixtuple& getSubEnt(int idx);
	virtual std::string str() const;
	virtual void addSubEnt(double x, double y, double z, double yaw, double roll, const std::string& name);
	t3_entPrimative(const std::string& inname);

	virtual ~t3_entPrimative() {}
};


#endif
