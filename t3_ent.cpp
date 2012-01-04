#include "t3_ent.h"
#include "headerMapper.h"
#include <sstream>
#include <algorithm>

using namespace std;

template <typename T>
void removeDup(vector<T>& vect)
{
	int i;
	typename vector<T>::iterator it;
	sort(vect.begin(), vect.end());
	it = unique(vect.begin(), vect.end());
	vect.resize(it - vect.begin());

	for (i = vect.size() - 1; i > 0; i--)
	{
		if (vect[i] == vect[i-1])
		{
			vect.erase(vect.begin() + i);
		}
	}
}

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
	int i;

	for (i = 0; i < (int)lines.size(); i++)
	{
		if (headerMapper<double>::fabs(lines[i].y1 - lines[i].y2) > 0.01)
		{
			intv.push_back(interval(lines[i].y1, lines[i].y2));
		}
	}

	removeDup(intv);

	return intv;
}

vector<t3_ent::interval> t3_ent::buildXList(const vector<linepair>& lines)
{
	vector<t3_ent::interval> intv;
	int i;

	for (i = 0; i < (int)lines.size(); i++)
	{
		if (headerMapper<double>::fabs(lines[i].x1 - lines[i].x2) > 0.01)
		{
			intv.push_back(interval(lines[i].x1, lines[i].x2));
		}
	}

	removeDup(intv);

	return intv;
}

vector<double> t3_ent::endPoints(const vector<interval>& lines)
{
	vector<double> points;
	int i;

	for (i = 0; i < (int)lines.size(); i++)
	{
		points.push_back(lines[i].low);
		points.push_back(lines[i].high);
	}

	removeDup(points);

	return points;
}

string t3_ent::topSVG() const
{
	vector<t3_poly> polys = allPoly();
	vector<linepair> lines;
	vector<interval> ylist;
	vector<double> ypoints;
	linepair offs;
	headerMapper<interval> hm;
	int i, j;
	minmax6tuple mm = findMaxMin(polys);
	stringstream ss;

	offs.x1 = 20;
	offs.y1 = 20;
	offs.x2 = 20;
	offs.y2 = 20;
	
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

	removeDup(lines);

	ylist = buildYList(lines);
	ypoints = endPoints(ylist);
	hm.loadIntervals(ylist);

	ss << "<!-- ypoints: ";
	for (i = 0; i < (int)ypoints.size(); i++) {ss << ypoints[i] << " "; }
	ss << "-->" << endl;
	ss << "<!-- ylist: ";
	for (i = 0; i < (int)ylist.size(); i++) {ss << "(" << ylist[i].low << "," << ylist[i].high << ")"; }
	ss << "-->" << endl;


	ss << "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">" << endl;

	for (i = 0; i < (int)ypoints.size(); i++)
	{
		ss << "\t" << "<line x1=\"" << 0 << "\" y1=\"" << ypoints[i];
		ss << "\" x2=\"" << scaleForSVG(mm.max_x - mm.min_x) + hm.size()*10 << "\" y2=\"" << ypoints[i] << "\" ";
		ss << "style=\"stroke:rgb(200,200,200);stroke-width:1\"/>" << endl;
	}

	for (i=0; i < hm.size(); i++)
	{
		for (j = 0; j < hm[i].size(); j++)
		{
			ss << "\t" << "<line x1=\"" << scaleForSVG(mm.max_x - mm.min_x) + i*10.0 + 5 << "\" y1=\"" << hm[i][j].low;
			ss << "\" x2=\"" << scaleForSVG(mm.max_x - mm.min_x) + i*10.0 + 5 << "\" y2=\"" << hm[i][j].high << "\" ";
			ss << "style=\"stroke:rgb(100,0,100);stroke-width:1\"/>" << endl;
		}
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
	return (lhs.high < rhs.high || (headerMapper<double>::fabs(lhs.high - rhs.high) < 0.01 && lhs.low < rhs.low));
}

bool operator==(const t3_ent::interval& lhs, const t3_ent::interval& rhs)
{
	return (headerMapper<double>::fabs(lhs.low - rhs.low) < 0.25 && headerMapper<double>::fabs(lhs.high - rhs.high) < 0.25);
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

