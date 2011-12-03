#ifndef NN_T3SIXTUPLE_H
#define NN_T3SIXTUPLE_H

class t3_sixtuple
{
	public:
	int x;
	int y;
	int z;
	int yaw;
	int roll;
	std::string name;

	t3_sixtuple(std::string inname)
	{
		x = 0;
		y = 0;
		z = 0;
		yaw = 0;
		roll = 0;
		name = inname;
	}

	t3_sixtuple(int xin, int yin, int zin, int yawin, int rollin, std::string inname)
	{
		x = xin;
		y = yin;
		z = zin;
		yaw = yawin;
		roll = rollin;
		name = inname;
	}
};

std::ostream& operator<<(std::ostream& os, const t3_sixtuple& rhs);
std::istream& operator>>(std::istream& is, t3_sixtuple& rhs);


#endif
