#include "t3_ent.h"
#include <sstream>

using namespace std;

int scaleForSVG(double input)
{
	return (int)(20*input);
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

string t3_ent::topSVG() const
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
			if (polys[i][j-1].x != polys[i][j].x || polys[i][j-1].z != polys[i][j].z)
			{
				ss << "\t<line x1=\"" << scaleForSVG(polys[i][j-1].x - mm.min_x) << "\" y1=\"" << scaleForSVG(mm.max_z - polys[i][j-1].z);
				ss << "\" x2=\"" << scaleForSVG(polys[i][j].x - mm.min_x) << "\" y2=\"" << scaleForSVG(mm.max_z - polys[i][j].z) << "\" ";
				ss << "style=\"stroke:rgb(0,0,0);stroke-width:1\"/>" << endl;
			}
		}
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