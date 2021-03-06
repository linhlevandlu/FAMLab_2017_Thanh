/*
 Fragments Automatic Matching Laboratory (FAMLab)
 Copyright (C) 2017  Pham Xuan Thanh (xuan-thanh.pham@etu.u-bordeaux.fr)
 Version: 1.1
 Created on: December, 2017

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


#include "RegionGrowing.h"

/**
  Label all the homogeneous pixels based on threshold value

  @param gray matrix
  @param threshold value
  @param the staring point
  @param four initial values to compute the bounding rectangle
*/
void detectRegion(ptr_IntMatrix mask, float thresholdValue, Point startingPoint, int &minX, int &maxX, int &minY, int &maxY)
{
    vector<Point> seedPoints; // list of points to be checked.
    seedPoints.push_back(startingPoint);
    mask->setAtPosition(startingPoint.getY(),startingPoint.getX(),256); // label the starting Point is checked by value 256
    while(!seedPoints.empty())
    {
        // Pop a point from seedPoints
        Point checkingPoint = seedPoints.back();
        seedPoints.pop_back();

        vector<Point> tempList = growRegion(mask,thresholdValue,checkingPoint,minX,maxX,minY,maxY);
        seedPoints.insert(seedPoints.end(),tempList.begin(),tempList.end());
    }
}

/**
  Checking the current pixel and returns a list of the 4 or 8 pixels
  surrounding the seed that satisfy the criteria, here is the threshold value

  @param gray matrix
  @param threshold value
  @param the current point
  @param four initial values to compute the bounding rectangle
*/
vector<Point> growRegion(ptr_IntMatrix mask, float thresholdValue, Point checkingPoint, int &minX, int &maxX, int &minY, int &maxY)
{
    RGB colorNull;
    vector<Point> tempList;
    int x = checkingPoint.getX(), y = checkingPoint.getY();
    // checking the top
    if(mask->getAtPosition(y-1, x) < thresholdValue)
    {
        // label point by value 256
        mask->setAtPosition(y-1, x, 256);
        Point point(x,y-1,colorNull);
        tempList.push_back(point);
        minY = y-1 < minY ? y-1 : minY;
    }
    // checking the bottom
    if(mask->getAtPosition(y+1, x) < thresholdValue)
    {
        // label point by value 256
        mask->setAtPosition(y+1, x, 256);
        Point point(x,y+1,colorNull);
        tempList.push_back(point);
        maxY = y+1 > maxY ? y+1 : maxY;
    }
    // checking the left
    if(mask->getAtPosition(y, x-1) < thresholdValue)
    {
        // label point by value 256
        mask->setAtPosition(y, x-1, 256);
        Point point(x-1,y,colorNull);
        tempList.push_back(point);
        minX = x-1 < minX ? x-1 : minX;
    }
    // checking the right
    if(mask->getAtPosition(y, x+1) < thresholdValue)
    {
        // label point by value 256
        mask->setAtPosition(y, x+1, 256);
        Point point(x+1,y,colorNull);
        tempList.push_back(point);
        maxX = x+1 > maxX ? x+1 : maxX;
    }

    return tempList;
}

