#include "t3_ent.h"
#include <sstream>
#include <algorithm>

using namespace std;

double scaleForSVG(double input)
{
	double scale = 20;
	return (scale*input);
}

t3_ent::minmax6tuple t3_ent::findMaxMin(const std::vector<t3_poly>& polys)
{
	int i, j;
	t3_ent::minmax6tuple a;

	if (polys.size() > 0)
	{
		a.min_x = a.max_x = polys[0].get(0).x;
		a.min_y = a.max_y = polys[0].get(0).y;
		a.min_z = a.max_z = polys[0].get(0).z;
	}
		
	for (i = 0; i < (int)polys.size(); i++)
	{
		for (j = 0; j < (int)polys[i].size(); j++)
		{
			if (polys[i].get(j).x < a.min_x){ a.min_x = polys[i].get(j).x; }
			if (polys[i].get(j).x > a.max_x){ a.max_x = polys[i].get(j).x; }
			if (polys[i].get(j).y < a.min_y){ a.min_y = polys[i].get(j).y; }
			if (polys[i].get(j).y > a.max_y){ a.max_y = polys[i].get(j).y; }
			if (polys[i].get(j).z < a.min_z){ a.min_z = polys[i].get(j).z; }
			if (polys[i].get(j).z > a.max_z){ a.max_z = polys[i].get(j).z; }
		}
	}

	return a;
}

vector<t3_ent::interval> t3_ent::buildYList(const vector<linepair>& lines)
{
	vector<t3_ent::interval> intv;
	vector<t3_ent::interval>::iterator it;
	int i;

	for (i = 0; i < (int)lines.size(); i++)
	{
		if (lines[i].y1 != lines[i].y2)
		{
			intv.push_back(interval(lines[i].y1, lines[i].y2));
		}
	}

	sort(intv.begin(), intv.end());
	it = unique(intv.begin(), intv.end());
	intv.resize(it - intv.begin());

	return intv;
}

vector<t3_ent::interval> t3_ent::buildXList(const vector<linepair>& lines)
{
	vector<t3_ent::interval> intv;
	vector<t3_ent::interval>::iterator it;
	int i;

	for (i = 0; i < (int)lines.size(); i++)
	{
		if (lines[i].x1 != lines[i].x2)
		{
			intv.push_back(interval(lines[i].x1, lines[i].x2));
		}
	}

	sort(intv.begin(), intv.end());
	it = unique(intv.begin(), intv.end());
	intv.resize(it - intv.begin());

	return intv;
}

vector<double> t3_ent::endPoints(const vector<interval>& lines)
{
	vector<double> points;
	vector<double>::iterator it;
	int i;

	for (i = 0; i < (int)lines.size(); i++)
	{
		points.push_back(lines[i].low);
		points.push_back(lines[i].high);
	}

	sort(points.begin(), points.end());
	it = unique(points.begin(), points.end());
	points.resize(it - points.begin());

	return points;
}

string t3_ent::topSVG() const
{
	vector<t3_poly> polys = allPoly();
	vector<linepair> lines;
	vector<linepair>::iterator it;
	vector<interval> ylist;
	vector<double> ypoints;
	linepair offs;

	offs.x1 = 20;
	offs.y1 = 20;
	offs.x2 = 20;
	offs.y2 = 20;

	int i, j;
	
	minmax6tuple mm = findMaxMin(polys);

	stringstream ss;
	
	for (i = 0; i < (int)polys.size(); i++)
	{
		for (j = 1; j < polys[i].size(); j++)
		{
			if (polys[i][j-1].x != polys[i][j].x || polys[i][j-1].z != polys[i][j].z)
			{
				lines.push_back(linepair(scaleForSVG(polys[i][j-1].x - mm.min_x), scaleForSVG(mm.max_z - polys[i][j-1].z), scaleForSVG(polys[i][j].x - mm.min_x), scaleForSVG(mm.max_z - polys[i][j].z)));
			}
		}
	}

	sort(lines.begin(), lines.end());
	it = unique (lines.begin(), lines.end()); 
	lines.resize( it - lines.begin() ); 

	ylist = buildYList(lines);
	ypoints = endPoints(ylist);

	ss << "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">" << endl;

	for (i = 0; i < (int)ypoints.size(); i++)
	{
		ss << "\t" << "<line x1=\"" << 0 << "\" y1=\"" << ypoints[i];
		ss << "\" x2=\"" << scaleForSVG(mm.max_x - mm.min_x) << "\" y2=\"" << ypoints[i] << "\" ";
		ss << "style=\"stroke:rgb(200,200,200);stroke-width:1\"/>" << endl;
	}

	for (i = 0; i < (int)lines.size(); i++)
	{
		ss << "\t" << lines[i]  << endl;
	}
	ss << "</svg>" << endl;

	return ss.str();
}

string t3_ent::frontSVG() const
{
	vector<t3_poly> polys = allPoly();
	int i, j;
	
	minmax6tuple mm = findMaxMin(polys);

	stringstream ss;

	ss << "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">" << endl;
	
	for (i = 0; i < (int)polys.size(); i++)
	{
		for (j = 1; j < polys[i].size(); j++)
		{
			if (polys[i][j-1].x != polys[i][j].x || polys[i][j-1].y != polys[i][j].y)
			{
				ss << "\t<line x1=\"" << scaleForSVG(polys[i][j-1].x - mm.min_x) << "\" y1=\"" << scaleForSVG(mm.max_y - polys[i][j-1].y);
				ss << "\" x2=\"" << scaleForSVG(polys[i][j].x - mm.min_x) << "\" y2=\"" << scaleForSVG(mm.max_y - polys[i][j].y) << "\" ";
				ss << "style=\"stroke:rgb(0,0,0);stroke-width:1\"/>" << endl;
			}
		}
	}

	ss << "</svg>" << endl;

	return ss.str();
}

string t3_ent::sideSVG() const
{
	vector<t3_poly> polys = allPoly();
	int i, j;
	
	minmax6tuple mm = findMaxMin(polys);

	stringstream ss;

	ss << "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">" << endl;
	
	for (i = 0; i < (int)polys.size(); i++)
	{
		for (j = 1; j < polys[i].size(); j++)
		{
			if (polys[i][j-1].y != polys[i][j].y || polys[i][j-1].z != polys[i][j].z)
			{
				ss << "\t<line x1=\"" << scaleForSVG(polys[i][j-1].z - mm.min_z) << "\" y1=\"" << scaleForSVG(mm.max_y - polys[i][j-1].y);
				ss << "\" x2=\"" << scaleForSVG(polys[i][j].z - mm.min_z) << "\" y2=\"" << scaleForSVG(mm.max_y - polys[i][j].y) << "\" ";
				ss << "style=\"stroke:rgb(0,0,0);stroke-width:1\"/>" << endl;
			}
		}
	}

	ss << "</svg>" << endl;

	return ss.str();
}

bool operator<(const t3_ent::interval& lhs, const t3_ent::interval& rhs)
{
	return (lhs.high < rhs.high || (lhs.high == rhs.high && lhs.low < rhs.low));
}

bool operator==(const t3_ent::interval& lhs, const t3_ent::interval& rhs)
{
	return (lhs.low == rhs.low && lhs.high == rhs.high);
}

t3_ent::linepair operator+(const t3_ent::linepair& lhs, const t3_ent::linepair& rhs)
{
	t3_ent::linepair p = lhs;

	p.x1 += rhs.x1;
	p.y1 += rhs.y1;
	p.x2 += rhs.x2;
	p.y2 += rhs.y2;

	return p;
}

bool operator<(const t3_ent::linepair& lhs, const t3_ent::linepair& rhs)
{
	if (lhs.x1 < rhs.x1)
	{
		return true;
	}
	else if (lhs.x1 == rhs.x1 && lhs.y1 < rhs.y1)	
	{
		return true;
	}
	else if (lhs.x1 == rhs.x1 && lhs.y1 == rhs.y1 && lhs.x2 < rhs.x2)
	{
		return true;
	}
	else if (lhs.x1 == rhs.x1 && lhs.y1 == rhs.y1 && lhs.x2 == rhs.x2 && lhs.y2 < rhs.y2)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool operator==(const t3_ent::linepair& lhs, const t3_ent::linepair& rhs)
{
	return (lhs.x1 == rhs.x1 && lhs.y1 == rhs.y1 && lhs.x2 == rhs.x2 && lhs.y2 == rhs.y2);
}

std::ostream& operator<<(std::ostream& os, const t3_ent::linepair& rhs)
{
	os << "<line x1=\"" << rhs.x1 << "\" y1=\"" << rhs.y1;
	os << "\" x2=\"" << rhs.x2 << "\" y2=\"" << rhs.y2 << "\" ";
	os << "style=\"stroke:rgb(0,0,0);stroke-width:1\"/>";

	return os;
}