#ifndef NN_T3ENTCOMPOSITE_H
#define NN_T3ENTCOMPOSTIE_H

#include "t3_poly.h"
#include "t3_subent.h"

class t3_entComposite : public t3_ent
{
	protected:
	std::vector<t3_sixtuple> subent;

	public:
	virtual int size() const;
	virtual t3_poly get(int idx) const;
	virtual void addPoly(const t3_poly& poly);
	virtual int subEntSize() const;
	virtual t3_sixtuple& getSubEnt(int idx);
	virtual std::string str() const;
	virtual void addSubEnt(int x, int y, int z, int yaw, int roll, const std::string& name);
	virtual bool isContainer() { return true; }

	virtual ~t3_entComposite() {}
};

#endif
