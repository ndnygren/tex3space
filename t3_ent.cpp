#include "t3_ent.h"
#include "headerMapper.h"
#include <sstream>
#include <algorithm>

using namespace std;

double t3_ent::textlinesize = 50.0;
int t3_ent::fontsize = 12;

template <typename T>
void removeDup(vector<T>& vect)
{
	typename vector<T>::iterator it;
	sort(vect.begin(), vect.end());
	it = unique(vect.begin(), vect.end());
	vect.resize(it - vect.begin());
}

double scaleForSVG(double input)
{
	double scale = 20;
	return (scale*input);
}

t3_ent::linepair scaleForSVG(const t3_ent::linepair& input)
{
	double scale = 20;
	return t3_ent::linepair(scale*input.x1, scale*input.y1, scale*input.x2, scale*input.y2);
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
	vector<interval> xlist;
	vector<double> xpoints;
	double lvl1 = 0, lvl2 = 0, high = 0, low = 0, highmid = 0, lowmid = 0;
	double dispxmax, dispxmin, dispymax, dispymin;
	headerMapper<interval> hm;
	int i, j;
	minmax6tuple mm = findMaxMin(polys);
	stringstream ss;
	
	dispxmax = mm.max_x;
	dispxmin = mm.min_x;
	dispymax = mm.max_z;
	dispymin = mm.min_z;

	for (i = 0; i < (int)polys.size(); i++)
	{
		for (j = 1; j < polys[i].size(); j++)
		{
			if (polys[i][j-1].x != polys[i][j].x || polys[i][j-1].z != polys[i][j].z)
			{
				lines.push_back(linepair(polys[i][j-1].x - mm.min_x, mm.max_z - polys[i][j-1].z, polys[i][j].x - mm.min_x, mm.max_z - polys[i][j].z));
			}
		}
	}

	removeDup(lines);

	ylist = buildYList(lines);
	xlist = buildXList(lines);
	ypoints = endPoints(ylist);
	xpoints = endPoints(xlist);
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
		lvl1 = scaleForSVG(dispxmax - dispxmin) + hm.size()*textlinesize; 
		ss << "\t" << "<line x1=\"" << 0 << "\" y1=\"" << scaleForSVG(ypoints[i]);
		ss << "\" x2=\"" << lvl1 << "\" y2=\"" << scaleForSVG(ypoints[i]) << "\" ";
		ss << "style=\"stroke:rgb(200,200,200);stroke-width:1\"/>" << endl;
	}


	for (i=0; i < hm.size(); i++)
	{
		for (j = 0; j < hm[i].size(); j++)
		{
			lvl1 = scaleForSVG(dispxmax - dispxmin) + (0.5 + i)*textlinesize;
			lvl2 = scaleForSVG(dispxmax - dispxmin) + (0.75 + i)*textlinesize;
			low = scaleForSVG(hm[i][j].low);
			lowmid = scaleForSVG((hm[i][j].low+hm[i][j].high)/2) - fontsize/2.0;
			high = scaleForSVG(hm[i][j].high);
			highmid = scaleForSVG((hm[i][j].low+hm[i][j].high)/2) + fontsize/2.0;

			ss << "\t" << linepair(lvl1, low, lvl2, lowmid) << endl;
			ss << "\t" << linepair(lvl1,high,lvl2,highmid) << endl;


			ss << "\t" << "<text x=\"" << lvl2 << "\" y=\"" << highmid << "\"";
			ss << " font-family=\"Verdana\" font-size=\"";
			ss << fontsize << "\" fill=\"rgb(0,0,0)\">" << endl;
			ss << "\t\t" << hm[i][j].high - hm[i][j].low << endl;
			ss << "\t" << "</text>" << endl;
		}
	}

	hm.loadIntervals(xlist);

	for (i = 0; i < (int)xpoints.size(); i++)
	{
		lvl1 = scaleForSVG(dispymax - dispymin) + hm.size()*textlinesize; 
		ss << "\t" << "<line x1=\"" << scaleForSVG(xpoints[i]) << "\" y1=\"" << 0;
		ss << "\" x2=\"" << scaleForSVG(xpoints[i]) << "\" y2=\"" << lvl1 << "\" ";
		ss << "style=\"stroke:rgb(200,200,200);stroke-width:1\"/>" << endl;
	}

	for (i=0; i < hm.size(); i++)
	{
		for (j = 0; j < hm[i].size(); j++)
		{
			lvl1 = scaleForSVG(dispymax - dispymin) + (0.5 + i)*textlinesize;
			lvl2 = scaleForSVG(dispymax - dispymin) + (0.75 + i)*textlinesize;
			low = scaleForSVG(hm[i][j].low);
			lowmid = scaleForSVG((hm[i][j].low+hm[i][j].high)/2) - fontsize/2.0;
			high = scaleForSVG(hm[i][j].high);
			highmid = scaleForSVG((hm[i][j].low+hm[i][j].high)/2) + fontsize/2.0;

			ss << "\t" << linepair(low, lvl1, lowmid, lvl2) << endl;
			ss << "\t" << linepair(high,lvl1,highmid,lvl2) << endl;


			ss << "\t" << "<text x=\"" << lowmid << "\" y=\"" << lvl2 << "\"";
			ss << " transform=\"rotate(90 " << lowmid << "," << lvl2 << ")\"";
			ss << " font-family=\"Verdana\" font-size=\"";
			ss << fontsize << "\" fill=\"rgb(0,0,0)\">" << endl;
			ss << "\t\t" << hm[i][j].high - hm[i][j].low << endl;
			ss << "\t" << "</text>" << endl;
		}
	}

	for (i = 0; i < (int)lines.size(); i++)
	{
		ss << "\t" << scaleForSVG(lines[i])  << endl;
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

