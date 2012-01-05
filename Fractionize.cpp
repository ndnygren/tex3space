/* tex3space - renders 2D projections of 3D objects for TeX
* Copyright (C) 2012 Nick Nygren
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>. */

#include "Fractionize.h"
#include <algorithm>
#include <sstream>
#include <cmath>

using namespace std;

Fractionize::fr_triple::fr_triple()
{
	fp = 0;
	n = d = 0;
}

Fractionize::fr_triple::fr_triple(double fpin, int nin, int din)
{
	fp = fpin;
	n = nin;
	d = din;
}

bool Fractionize::fr_triple::operator<(const fr_triple& rhs) const
{
	return (n < rhs.n) || (n == rhs.n && d < rhs.d);
}

bool Fractionize::fr_triple::operator==(const fr_triple& rhs) const
{
	return (n == rhs.n && d == rhs.d);
}

std::vector<Fractionize::fr_triple> Fractionize::data;

void Fractionize::init()
{
	int i,j,g;
	fr_triple swap;
	vector<fr_triple>::iterator it;
	data.push_back(fr_triple(0,0,1));

	for (i = 2; i < max_denominator; i++)
		for (j = 1; j < i; j++)
		{
			g = gcd(i,j);
			data.push_back(fr_triple((double)j/(double)i,j/g,i/g));
		}

	sort(data.begin(), data.end());
	it = unique(data.begin(), data.end());
	data.resize(it-data.begin());

	for (i = 1; i < (int)data.size(); i++)
	for (j = i; j >= 1 && data[j].fp < data[j-1].fp; j--)
	{
		swap = data[j];
		data[j] = data[j-1];
		data[j-1] = swap;
	}
}

double Fractionize::dabs(double input)
{
	if (input < 0)
	{	
		return -input;
	}
	else
	{
		return input;
	}
}

int Fractionize::gcd(int lhs, int rhs)
{
	int a,b,c;

	if (lhs == 0 && rhs == 0)
	{
		return 1;
	}
	else if (lhs == 0 || rhs == 0)
	{
		return max(abs(lhs),abs(rhs));
	}

	a = lhs;
	b = rhs;
	c = a % b;

	while (c != 0)
	{
		a = b;
		b = c;
		c = a % b;
	}

	return abs(b);
}

std::string Fractionize::convert(double input) const
{
	double flr = floor(dabs(input));
	double dec = dabs(input) - flr;
	int mid, high, low;

	double closestdub = data[0].fp;
	int closestidx = 0;

	stringstream ss;

	if (dabs(1-dec) < 0.0001)
	{ 
		ss << (flr+1);
		return ss.str();
	}

	if (dec == 0) 
	{ 
		ss << flr;
		return ss.str();
	}

	low = 0;
	high = data.size();

	while (high - low > 0)
	{
		mid = (low + high) / 2;

		if (data[mid].fp == dec)
		{
			high = low;
		}
		else if (dec < data[mid].fp)
		{
			high = mid;
		}
		else
		{
			low = mid + 1;
		}

		if (dabs(dec - data[mid].fp) <  dabs(dec - closestdub))
		{
			closestdub = data[mid].fp;
			closestidx = mid;
		}
		
	}

	if (flr != 0)
	{
		ss << flr;
	}

	if (flr != 0 && closestidx != 0)
	{
		ss << " ";
	}

	if (closestidx != 0)
	{	
		ss << data[closestidx].n << "/" << data[closestidx].d;
	}

	return ss.str();
}

Fractionize::Fractionize()
{
	if (data.size() == 0)
	{
		init();
	}
}

