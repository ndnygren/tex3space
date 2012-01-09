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


/**
 * @brief class of staic members for converting floating point numbers into 
 * a fractional form (ex. 1.5 --> 1 1/2)
 */
class Fractionize
{
	
	public:

	/**
	 * @brief A ordered triple containing a integer pair and a floating point
	 * representation of their ratio.
	 */
	class fr_triple
	{
		public:
		/**
		 * @brief the floating point representation
		 */
		double fp;
		/**
		 * @brief The integer value of the numerator
		 */
		int n;

		/**
		 * @brief The integer value of the denominator
		 */
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

	/**
	 * @brief limit of the precision of the fractions.
	 */
	const static int max_denominator = 64;

	/**
	 * @brief cache shared by all instances of Fractionize
	 */
	static std::vector<fr_triple> data;

	/**
	 * @brief populates the cache with all pairs of fractions upto the denominator size limit.
	 */
	void init();
};



#endif
