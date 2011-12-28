#include "t3_ent.h"
#include "t3_masterList.h"

#ifndef NN_T3ENTCOMPOSITE_H
#define NN_T3ENTCOMPOSTIE_H

class t3_entComposite : public t3_ent
{
	protected:
	std::vector<t3_sixtuple> subent;
	t3_masterList *ml;

	public:
	virtual int size() const;
	virtual t3_poly get(int idx) const;
	virtual void addPoly(const t3_poly& poly);
	virtual std::vector<t3_poly> allPoly() const;
	virtual int subEntSize() const;
	virtual t3_sixtuple& getSubEnt(int idx);
	virtual std::string str() const;
	virtual void addSubEnt(int x, int y, int z, int yaw, int roll, const std::string& name);
	virtual bool isContainer() { return true; }

	t3_entComposite(const std::string& inname, t3_masterList* mlin) 
	{
		name = inname; 
		ml = mlin;
	}

	virtual ~t3_entComposite() {}
};

#endif
