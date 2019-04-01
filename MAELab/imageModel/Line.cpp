/*
 Morphometry with Automatic Extraction of Landmarks (MAELab)
 Copyright (C) 2017  Le Van Linh (van-linh.le@u-bordeaux.fr)
 Created on: Sep 15, 2016

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see http://www.gnu.org/licenses/.
 */
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <string.h>
#include <fstream>
#include <time.h>

using namespace std;

#include "Point.h"
#include "Line.h"

//=================================================== Constructor ===========================================
Line::Line()
{
}
Line::Line(const Line &otherLine)
{
	begin = otherLine.begin;
	end = otherLine.end;
	dx = otherLine.dx;
	dy = otherLine.dy;
	length = otherLine.length;
	equation = otherLine.equation;
}

Line::Line(Point ep1, Point ep2)
{
	begin = ep1;
	end = ep2;

	dx = end.getX() - begin.getX();
	dy = end.getY() - begin.getY();

	length = lengthOfLine();

	equation = equationOfLine();
}

Line::~Line()
{
	// TODO Auto-generated destructor stub
}
//=================================================== Get and set ===========================================
Point Line::getBegin()
{
	return begin;
}
Point Line::getEnd()
{
	return end;
}

void Line::setBegin(Point ep1)
{
	begin = ep1;
	dx = end.getX() - begin.getX();
	dy = end.getY() - begin.getY();
	lengthOfLine();
}
void Line::setEnd(Point ep2)
{
	end = ep2;
	dx = end.getX() - begin.getX();
	dy = end.getY() - begin.getY();
	lengthOfLine();
}

double Line::getLength()
{
	return length;
}
std::vector<double> Line::getEquation()
{
	return equation;
}

//=================================================== Private methods ===========================================
/*
 * Check the line is a point or not
 */
bool Line::isPoint()
{
	if (begin.getX() == end.getX() && begin.getY() == end.getY())
		return true;
	return false;
}

double distancePoints(Point p1, Point p2)
{
	return sqrt(
		pow((double) (p2.getX() - p1.getX()), 2)
			+ pow((double) (p2.getY() - p1.getY()), 2));
}
/*
 * Calculate the length of line
 */
double Line::lengthOfLine()
{
	return distancePoints(begin, end);
}

/*
 * Get the equation of line (ax + by + c = 0)
 */
std::vector<double> Line::equationOfLine()
{
	std::vector<double> equa;
	if (dx == 0)
	{ //line x = n
		equa.push_back(1.0);
		equa.push_back(0.0);
		equa.push_back((double) (end.getX()));
		return equa;
	}
	else
	{
		if (dy == 0)
		{ // line y = m
			equa.push_back(0);
			equa.push_back(1);
			equa.push_back((end.getY()));
			return equa;
		}
		else
		{
			if (dx != 0 && dy != 0)
			{ // normal line
				double m = (double) dy / (double) dx;

				equa.push_back(m);
				equa.push_back(-1);
				equa.push_back((double) (begin.getY() - (m * begin.getX())));
				return equa;
			}
		}
	}

	return equa; // NULL
}
//=================================================== Public Methods ===========================================
double Line::perpendicularDistance(Point point)
{
	double a = equation.at(0);
	double b = equation.at(1);
	double c = equation.at(2);
	double distance = 0;
	if (b != 0 && a != 0)
	{
		distance = abs(
			((a * point.getX()) + (b * point.getY()) + c)
				/ (sqrt(pow(a, 2) + pow(b, 2))));
	}
	if (b == 0 && a == 1)
		distance = abs(point.getX() - c);
	if (a == 0 && b == 1)
		distance = abs(point.getY() - c);
	return distance;
}

double Line::angleLines(Line otherLine)
{

	double slope1, slope2;
	if (dx == 0 && otherLine.dx == 0)
		return 0;
	if (dx == 0 && otherLine.dx != 0)
	{ // line 1 is parallel with Oy
		slope2 = (double) otherLine.dy / (double) otherLine.dx;
		double angle = atan(abs(1 / slope2)) * 180 / M_PI;
		if (angle < 0)
			angle += 360;
		return angle;
	}
	if (dx != 0 && otherLine.dx == 0)
	{ //otherLine is parallel with Oy
		slope1 = (double) dy / (double) dx;
		double angle = atan(abs(1 / slope1)) * 180 / M_PI;
		if (angle < 0)
			angle += 360;
		return angle;
	}

	slope1 = (double) dy / (double) dx;
	slope2 = (double) otherLine.dy / (double) otherLine.dx;

	if ((slope1 == 0 && slope2 == 0)) // parallel lines
		return 0;
	if (slope1 * slope2 == -1) // perpendicular lines
		return 90;
	if (slope1 == 0 && slope2 != 0)
	{ // line 1 is parallel with Ox
		double angle = atan(abs(slope2)) * 180 / M_PI;
		if (angle < 0)
			angle += 360;
		return angle;
	}
	if (slope1 != 0 && slope2 == 0)
	{ // otherLine is parallel with Ox
		double angle = atan(abs(slope1)) * 180 / M_PI;
		if (angle < 0)
			angle += 360;
		return angle;
	}
	double angle = atan(abs((slope1 - slope2) / (1 + slope1 * slope2)))
		* 180/ M_PI;
	if (angle < 0)
		angle += 360;
	return angle;
}

Point Line::intersection(Line otherLine)
{

	double a1 = equation.at(0);
	double b1 = equation.at(1);
	double c1 = equation.at(2);

	double a2 = otherLine.equation.at(0);
	double b2 = otherLine.equation.at(1);
	double c2 = otherLine.equation.at(2);

	if ((b1 == 0 && b2 == 0) || (a1 == a2)) // parallel lines
		return Point(-1, -1);

	double a; // = a1 - a2;
	double c; // = c2 - c1;
	double x = 0; // = c / a;
	double y = 0; // = (a1 * x) + c1;

	if (b1 == 0 && b2 != 0)
	{
		x = c1;
		y = (a2 * x) + c2;
	}
	else
	{
		if (b1 != 0 && b2 == 0)
		{
			x = c2;
			y = (a1 * x) + c1;
		}
	}
	if (b1 != 0 && b2 != 0)
	{
		a = a1 - a2;
		c = c2 - c1;
		x = c / a;
		y = (a1 * x) + c1;
	}
	return Point(round(x), round(y));
}

bool Line::checkBelongPoint(Point point)
{
	if (perpendicularDistance(point) == 0)
		return true;
	return false;
}
vector<Point> Line::interParallel(Line line1, Line line2, double distance1,
	double distance2, int width, int height)
{
	vector<double> equation1 = line1.equationOfLine();
	vector<double> equation2 = line2.equationOfLine();
	double a = equation1[0];
	double b = equation1[2];
	double c = equation2[0];
	double d = equation2[2];
	double e = distance1 * (sqrt((a * a) + 1));
	double f = distance2 * (sqrt((c * c) + 1));

	vector<Point> result;

	double x0 = 0, y0 = 0;
	x0 = (f + b - d - e) / (c - a);
	if (x0 >= 0 && x0 < width)
	{
		y0 = a * x0 + b - e;
		if (y0 >= 0 && y0 < height)
		{
			result.push_back(Point(x0, y0));
		}
	}
	x0 = (b - e - f - d) / (c - a);
	if (x0 >= 0 && x0 < width)
	{
		y0 = a * x0 + b - e;
		if (y0 >= 0 && y0 < height)
		{
			result.push_back(Point(x0, y0));
		}
	}
	x0 = (f + b - d + e) / (c - a);
	if (x0 >= 0 && x0 < width)
	{
		y0 = a * x0 + b + e;
		if (y0 >= 0 && y0 < height)
		{
			result.push_back(Point(x0, y0));
		}
	}
	x0 = (b + e - f - d) / (c - a);
	if (x0 >= 0 && x0 < width)
	{
		y0 = a * x0 + b + e;
		if (y0 >= 0 && y0 < height)
		{
			result.push_back(Point(x0, y0));
		}
	}
	return result;
}
