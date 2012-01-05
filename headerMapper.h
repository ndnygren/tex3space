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

#ifndef NN_HEADERMAPPER_H
#define NN_HEADERMAPPER_H

/**
 * @brief A class for calculating positions of various, possibly overlapping, labels
 */
template <typename T>
class headerMapper
{
	public:
	/**
	 * @brief A list of non overlapping intervals representing valid label positions
	 */
	class headerRow
	{
		private:
		/**
		 * @brief the list of intervals
		 */
		std::vector<T> hdata;

		public:
		void push_back(T intv) { hdata.push_back(intv);	}
		T& back() { return hdata[hdata.size() - 1];	}
		T& operator[](int i) { return hdata[i];	}
		int size() const { return hdata.size(); }
		void resize() { hdata.resize(); }
	};

	/**
	 * @brief usual floating point absolute value operator
	 * @param input a number
	 * @returns the absolute value of the supplied number
	 */
	static double fabs (double input)
	{
		if (input >= 0) { return input; }
		else { return -input; }
	}

	/**
	 * @brief qouble floating point equivalence test
	 * @param lhs double to be tested
	 * @param rhs double to be tested
	 * @returns true if and only if lhs and rhs differ only by a small threshold.
	 */
	static bool equiv(double lhs, double rhs)
	{
		return fabs(lhs-rhs) < DFPET;
	}

	/**
	 * @brief Loads a list of intervals and computes a valid solution from them.
	 * @param intervals The list of intervals to process
	 */
	void loadIntervals(const std::vector<T>& intervals)
	{
		int i, loop;
		double max = intervals[0].low;
		headerRow temprow;
		std::vector<bool> used;
		used.resize(intervals.size());

		rows.clear();

		for (i = 0; i < (int)intervals.size(); i++) 
		{
			used[i] = false;
			if (intervals[i].high > max) { max = intervals[i].high; }
		}

		for (loop = 0; loop < (int)intervals.size(); loop++)
		{
			for (i = loop; i < (int)intervals.size() && used[i]; i++) { }
			if (i >= (int)intervals.size()) { return; }

			rows.push_back(temprow);
			if (intervals[i].low > 0)
			{
				rows.back().push_back(T(0,intervals[i].low));
			}
			rows.back().push_back(intervals[i]);
			used[i] = true;

			for (; i < (int)intervals.size(); i++) 
			{
				if (!used[i] && (rows.back().back().high < intervals[i].low
					|| fabs(rows.back().back().high - intervals[i].low) < 0.01))
				{
					if (intervals[i].low > rows.back().back().high && !equiv(intervals[i].low, rows.back().back().high))
					{
						rows.back().push_back(T(rows.back().back().high,intervals[i].low));
					}
					rows.back().push_back(intervals[i]);
					used[i] = true;
				}
			}
			if (rows.back().back().high < max && !equiv(max, rows.back().back().high))
			{
				rows.back().push_back(T(rows.back().back().high,max));
			}
		}
	}

	/**
	 * @brief Access to the underlying rows of non-overlapping intervals
	 * @param i the index of the row
	 * @returns the address of the row
	 */
	headerRow& operator[](int i) { return rows[i]; }

	/**
	 * @brief the number of rows
	 * @returns the number of rows
	 */
	int size() const { return rows.size(); }

	private:
	/**
	 * @brief The list of row vectors. Each row will contain a non-overlaping subset of the input intervals. Every interval will be represented in exactly one row.
	 */
	std::vector<headerRow> rows;
	static double DFPET;
};


#endif

