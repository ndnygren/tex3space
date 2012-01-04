
#include <vector>

#ifndef NN_HEADERMAPPER_H
#define NN_HEADERMAPPER_H

template <typename T>
class headerMapper
{
	public:
	class headerRow
	{
		private:
		std::vector<T> hdata;

		public:
		void push_back(T intv) { hdata.push_back(intv);	}
		T& back() { return hdata[hdata.size() - 1];	}
		T& operator[](int i) { return hdata[i];	}
		int size() const { return hdata.size(); }
		void resize() { hdata.resize(); }
	};

	static double fabs (double input)
	{
		if (input >= 0) { return input; }
		else { return -input; }
	}

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
					if (intervals[i].low > rows.back().back().high && fabs(intervals[i].low - rows.back().back().high) > 0.001)
					{
						rows.back().push_back(T(rows.back().back().high,intervals[i].low));
					}
					rows.back().push_back(intervals[i]);
					used[i] = true;
				}
			}
			if (rows.back().back().high < max && fabs(max - rows.back().back().high) > 0.001)
			{
				rows.back().push_back(T(rows.back().back().high,max));
			}
		}
	}

	headerRow& operator[](int i) { return rows[i]; }
	int size() const { return rows.size(); }

	private:
	std::vector<headerRow> rows;
};


#endif

