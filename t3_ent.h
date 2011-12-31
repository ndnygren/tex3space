#ifndef NN_T3ENT_H
#define NN_T3ENT_H

#include "t3_poly.h"
#include "t3_sixtuple.h"

class t3_ent
{
	protected:
	std::string name;
	static t3_sixtuple nulltuple;

	public:

	class interval
	{
		public:
		double low,high;

		interval() { low = high = 0; }

		interval(double lowin, double highin)
		{
			if (lowin < highin)
			{
				low = lowin;
				high = highin;
			}
			else
			{
				low = highin;
				high = lowin;
			}
		}
	};

	class minmax6tuple
	{
		public:
		double min_x, max_x, min_y, max_y, min_z, max_z;

		minmax6tuple()
		{
			min_x = max_x = min_y = max_y = min_z = max_z = 0;
		}
	};

	class linepair
	{
		public:
		double x1,y1,x2,y2;

		linepair()
		{
			x1 = y1 = x2 = y2 = 0;
		}

		linepair(double x1in, double y1in, double x2in, double y2in)
		{
			x1 = x1in;
			y1 = y1in;
			x2 = x2in;
			y2 = y2in;
		}
	};

	static minmax6tuple findMaxMin(const std::vector<t3_poly>& polys);
	virtual int size() const = 0;
	virtual t3_poly get(int idx) const = 0;
	virtual void addPoly(const t3_poly& poly) = 0;
	virtual std::vector<t3_poly> allPoly() const = 0;
	virtual int subEntSize() const = 0;
	virtual t3_sixtuple& getSubEnt(int idx) = 0;
	virtual std::string str() const = 0;
	virtual std::string getName() const { return name; }
	
	static std::vector<interval> buildYList(const std::vector<linepair>& lines);
	static std::vector<interval> buildXList(const std::vector<linepair>& lines);
	static std::vector<double> endPoints(const std::vector<interval>& lines);

	std::string topSVG() const;	
	std::string frontSVG() const;	
	std::string sideSVG() const;	

	virtual void addSubEnt(double x, double y, double z, double yaw, double roll, const std::string& name) = 0;
	virtual bool isContainer() { return false; }

	virtual ~t3_ent() {}
};

bool operator<(const t3_ent::interval& lhs, const t3_ent::interval& rhs);
bool operator==(const t3_ent::interval& lhs, const t3_ent::interval& rhs);

t3_ent::linepair operator+(const t3_ent::linepair& lhs, const t3_ent::linepair& rhs);
bool operator<(const t3_ent::linepair& lhs, const t3_ent::linepair& rhs);
bool operator==(const t3_ent::linepair& lhs, const t3_ent::linepair& rhs);
std::ostream& operator<<(std::ostream& os, const t3_ent::linepair& rhs);
std::ostream& operator<<(std::ostream& os, const t3_ent& rhs);

#endif
