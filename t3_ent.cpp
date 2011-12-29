#include "t3_ent.h"
#include <sstream>

using namespace std;

int scaleForSVG(double input)
{
	return (int)(20*input);
}

string t3_ent::topSVG() const
{
	vector<t3_poly> polys = allPoly();
	int i, j;
	double min_x, max_x, min_y, max_y, min_z, max_z;
	stringstream ss;

	if (polys.size() > 0)
	{
		min_x = max_x = polys[0][0].x;
		min_y = max_y = polys[0][0].y;
		min_z = max_z = polys[0][0].z;
	}
		
	for (i = 0; i < (int)polys.size(); i++)
	{
		for (j = 0; j < (int)polys[i].size(); j++)
		{
			if (polys[i][j].x < min_x){ min_x = polys[i][j].x; }
			if (polys[i][j].x > max_x){ max_x = polys[i][j].x; }
			if (polys[i][j].y < min_y){ min_y = polys[i][j].y; }
			if (polys[i][j].y > max_y){ max_y = polys[i][j].y; }
			if (polys[i][j].z < min_z){ min_z = polys[i][j].z; }
			if (polys[i][j].z > max_z){ max_z = polys[i][j].z; }
		}
	}
		
	ss << "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">" << endl;
	
	for (i = 0; i < (int)polys.size(); i++)
	{
		for (j = 1; j < polys[i].size(); j++)
		{
			if (polys[i][j-1].x != polys[i][j].x || polys[i][j-1].z != polys[i][j].z)
			{
				ss << "\t<line x1=\"" << scaleForSVG(polys[i][j-1].x - min_x) << "\" y1=\"" << scaleForSVG(max_z - polys[i][j-1].z);
				ss << "\" x2=\"" << scaleForSVG(polys[i][j].x - min_x) << "\" y2=\"" << scaleForSVG(max_z - polys[i][j].z) << "\" ";
				ss << "style=\"stroke:rgb(0,0,0);stroke-width:1\"/>" << endl;
			}
		}
	}

	ss << "</svg>" << endl;

	return ss.str();
}