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

#include <vector>
#include <string>

#ifndef NN_FRACTIONIZE_H
#define NN_FRACTIONIZE_H

class Fractionize
{
	
	public:

	class fr_triple
	{
		public:
		double fp;
		int n;
		int d;
		
		fr_triple();
		fr_triple(double fpin, int nin, int din);
		
		bool operator<(const fr_triple& rhs) const;
		bool operator==(const fr_triple& rhs) const;
	};

	static double dabs(double input);
	static int gcd(int lhs, int rhs);
	std::string convert(double input) const;
	Fractionize();

	protected:

	const static int max_denominator = 64;
	static std::vector<fr_triple> data;
	void init();
};



#endif
