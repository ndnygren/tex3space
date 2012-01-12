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
#ifndef NN_T3ENT_H
#define NN_T3ENT_H

#include "t3_poly.h"
#include "t3_sixtuple.h"


/**
 * @brief Main Entity class, inherted by Primatives and Composites
 *
 */
class t3_ent
{
	protected:
	/**
	 * @brief represents the spacing (cross-span) of labels. 
	 * This may need to be modified based on label string length.
	 */
	static double textlinesize;

	/**
	 * @brief The short perpendicular line at the each end of the 
	 * label span has a length of 2*tickwidth.
	 */
	static double tickwidth;

	/**
	 * @brief The name (and unique identifier) of the entity.
	 */
	std::string name;

	/**
	 * @brief A "zero" representation returned when subEntity related calls
	 * are made to primatives.
	 */
	static t3_sixtuple nulltuple;

	/**
	 * @brief The font size to be used with labels in SVG and TeX output.
	 */
	static int fontsize;

	public:

	/**
	 * @brief Integer type code, requesting a "top" view.
	 */
	static const int TYPE_TOP = 0;

	/**
	 * @brief Integer type code, requesting a "front" view.
	 */
	static const int TYPE_FRONT = 1;

	/**
	 * @brief Integer type code, requesting a "side" view.
	 */
	static const int TYPE_SIDE = 2;

	/**
	 * @brief Integer type code, requesting yaw rotation.
	 */
	static const int TYPE_YAW = 3;

	/**
	 * @brief Integer type code, requesting a roll rotation.
	 */
	static const int TYPE_ROLL = 4;

	/**
	 * @brief Integer type code, requesting a pitch rotation.
	 */
	static const int TYPE_PITCH = 5;

	/**
	 * @brief A pair of doubles.
	 * @details In this pair, the low pair is set as the least of the input pair, while the other is set in high.
	 *
	 */
	class interval
	{
		public:
		/**
		 * @brief The lesser number in the pair
		 */
		double low;

		/**
		 * @brief The greater number in the pair
		 */
		double high;

		interval() { low = high = 0; }

		interval(double lowin, double highin)
		{
			if (lowin < highin)
			{
				low = lowin;
				high = highin;
			}
			else
			{
				low = highin;
				high = lowin;
			}
		}
	};


	/**
	 * @brief A class describing the Max and Min of a object in 3 dimensions.
	 * @details For each dimension(x,y,z) a pair is listed (max_x,min_x,...etc.)
	 */
	class minmax6tuple
	{
		public:
		double min_x, max_x, min_y, max_y, min_z, max_z;

		minmax6tuple()
		{
			min_x = max_x = min_y = max_y = min_z = max_z = 0;
		}
	};

	/** 
	 * @brief A pair of pairs, representing 2 endpoints of a line.
	 */
	class linepair
	{
		public:
		double x1,y1,x2,y2;

		linepair()
		{
			x1 = y1 = x2 = y2 = 0;
		}

		linepair(double x1in, double y1in, double x2in, double y2in)
		{
			x1 = x1in;
			y1 = y1in;
			x2 = x2in;
			y2 = y2in;
		}
	};

	/**
	 * @brief iterates over a list of polygons (t3_poly) and record the minimum and maximum dispacement reached over each dimension
	 * @param polys the list of t3_poly to analyze
	 * @returns a minmax6tuple storing the calculated values
	 */
	static minmax6tuple findMaxMin(const std::vector<t3_poly>& polys);

	/**
	 * @brief the size of the object(in number of polygons)
	 * @returns 0 if composited, the number of polygons if primative
	 */
	virtual int size() const = 0;

	/**
	 * @brief read-only access to the internal polygons of a primative
	 * @param idx the index of the polygon to access
	 * @returns the polygon at the requested index
	 */
	virtual t3_poly get(int idx) const = 0;

	/**
	 * @brief Addes a new polygon to a primative
	 * @param poly The polygon to be added
	 */
	virtual void addPoly(const t3_poly& poly) = 0;

	/**
	 * @brief Collapses the entity into a list of polygons, applying rotations and translations as needed.
	 * @returns a list of all polygons contained in the entity
	 */
	virtual std::vector<t3_poly> allPoly() const = 0;

	/**
	 * @brief The number of sub-entitys contained in a Composite
	 * @returns 0 for primatives, number of subentities for a composite
	 */
	virtual int subEntSize() const = 0;

	/**
	 * @brief read/write access to an underlying entity
	 * @param idx index of the subentity
	 * @returns the address of the subentity
	 */
	virtual t3_sixtuple& getSubEnt(int idx) = 0;

	/**
	 * @brief The string representation of the entity (for save files)
	 * @returns A string containing a full description of the entity
	 */
	virtual std::string str() const = 0;

	/**
	 * @brief the name (and unique identifier) of the entity
	 * @returns the name of the entity
	 */
	virtual std::string getName() const { return name; }
	
	/**
	 * @brief Calculate a list of vertical intervals from a list of lines
	 * @details Ignoring the x components of each endpoint of each line, an interval(unique) is added for every line with a non-zero vertical span
	 * @param lines the list of lines to be analyze
	 * @returns the list of interval
	 */
	static std::vector<interval> buildYList(const std::vector<linepair>& lines);

	/**
	 * @brief Calculate a list of horizontal intervals from a list of lines
	 * @details Ignoring the y components of each endpoint of each line, an interval(unique) is added for every line with a non-zero horizontal span
	 * @param lines the list of lines to be analyze
	 * @returns the list of interval
	 */
	static std::vector<interval> buildXList(const std::vector<linepair>& lines);

	/**
	 * @brief calculates a list of unique endpoints from a list of intervals
	 * @param lines the list of intervals to be analyzed
	 * @returns a list of all unqiue endpoints
	 */
	static std::vector<double> endPoints(const std::vector<interval>& lines);

	/**
	 * @brief renders a SVG diagram of the entity (top view) in string form.
	 * @param type the typecode of the view (default top)
	 * @returns a string containing the SVG diagram
	 */
	std::string topSVG(int type = 0) const;	

	/**
	 * @brief renders a SVG diagram of the entity (front view) in string form.
	 * @returns a string containing the SVG diagram
	 */
	std::string frontSVG() const;	

	/**
	 * @brief renders a SVG diagram of the entity (side view) in string form.
	 * @returns a string containing the SVG diagram
	 */
	std::string sideSVG() const;	

	/**
	 * @brief Adds a sub entity to a composite entity
	 * @param x the displacement on the x axis of the sub entity
	 * @param y the displacement on the y axis of the sub entity
	 * @param z the displacement on the z axis of the sub entity
	 * @param yaw the rotation around the y axis of the sub entity
	 * @param roll the rotation around the z axis of the entity
	 * @param name the unique name identifiying the entity
	 */
	virtual void addSubEnt(double x, double y, double z, double yaw, double roll, const std::string& name) = 0;

	/**
	 * @brief distingishes between primatives and composites
	 * @returns true for composites and false for primatives.
	 */
	virtual bool isContainer() { return false; }

	/**
	 * @brief moves the zero point within the entities space(or equivalently moves the entire entity relative to zero)
	 * @param dx the offset along the x axis
	 * @param dy the offset along the y axis
	 * @param dz the offset along the z axis
	 */
	virtual void recenter(double dx, double dy, double dz) = 0;

	/**
	 * @brief rotates the entity
	 * @param angle the angle (in degrees) of rotation
	 * @param type the axis type code of the rotation (TYPE_YAW, TYPE_ROLL, TYPE_PITCH)
	 */
	virtual void rotate(double angle, int type) = 0;

	virtual ~t3_ent() {}
};

bool operator<(const t3_ent::interval& lhs, const t3_ent::interval& rhs);
bool operator==(const t3_ent::interval& lhs, const t3_ent::interval& rhs);

t3_ent::linepair operator+(const t3_ent::linepair& lhs, const t3_ent::linepair& rhs);
bool operator<(const t3_ent::linepair& lhs, const t3_ent::linepair& rhs);
bool operator==(const t3_ent::linepair& lhs, const t3_ent::linepair& rhs);
std::ostream& operator<<(std::ostream& os, const t3_ent::linepair& rhs);
std::ostream& operator<<(std::ostream& os, const t3_ent& rhs);

#endif
