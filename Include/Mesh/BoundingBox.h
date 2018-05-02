#ifndef BOUNDINGBOX_H_
#define BOUNDINGBOX_H_

#include <algorithm>

#include <wx/wx.h>

/**
 * @class boundingBox
 * @author Phillip
 * @date 01/02/18
 * @file BoundingBox.h
 * @brief This class is used to contain the data structure of the bounding box for a closed contour
 * In order to use this class, points must be "added" in order for the bounding box to odetermine 
 * if the max bounds or min bounds needs to be changed. It is recommended to use the constuctor
 * with the parameter when setting first points. The empty construtor is used for a two-step 
 * creation process.
 */
class boundingBox
{
private:
	
	//! The max point for the bounding box
	wxRealPoint p_maxBounds = wxRealPoint(0, 0);
	
	//! The min point for the bounding box
	wxRealPoint p_minBounds = wxRealPoint(0, 0);
	
public:

	/**
	 * @brief The constructor which requires a starting point. THis will set the 
	 * max and min bounds equal to the point. This constructor is recomendded as 
	 * the bounding box will correctly function with this constructor in any case.
	 * @param startingPoint The first point for the bounding box
	 */
	boundingBox(wxRealPoint startingPoint)
	{
		p_maxBounds = startingPoint;
		p_minBounds = startingPoint;
	}
	
	/**
	 * @brief An empty constructor. This constructor is given as a form of a two step creation
	 * process.
	 */
	boundingBox()
	{
		
	}

	/**
	 * @brief "Adds" a point to the bounding box. THis function will check if the x and y
	 * values are greater or less then the x and y values of the max or min points, respectively.
	 * If so, then replace the max/min values with the values contained in point.
	 * @param point Point that is to be "added" to the bounding box
	 */
	void addPoint(wxRealPoint point)
	{
		p_maxBounds.x = std::max(p_maxBounds.x, point.x);
		p_maxBounds.y = std::max(p_maxBounds.y, point.y);
		
		p_minBounds.x = std::min(p_minBounds.x, point.x);
		p_minBounds.y = std::min(p_minBounds.y, point.y);
	}

	/**
	 * @brief Retrieves the max point of the bounding box
	 * @return Returns a point representing the maxiumum point of the bounding box
	 */
	wxRealPoint getMaxBounds()
	{
		return p_maxBounds;
	}
	
	/**
	 * @brief Retrieves the min point of the bounding box
	 * @return Returns a point representing the minimium point of the bounding box
	 */
	wxRealPoint getMinBounds()
	{
		return p_minBounds;
	}
	
	/**
	 * @brief 	Function that will check if the current bounding box is inside of another
	 * 			bounding box. This is comparing from the persepective that the this bounding box
	 * 			is contained inside of the compare bounding box.
	 * @param compare
	 * @return 
	 */
	bool isInside(boundingBox compare)
	{
		bool xMaxIsGreater = compare.getMaxBounds().x >= p_maxBounds.x;
		bool yMaxIsGreater = compare.getMaxBounds().y >= p_maxBounds.y;
		
		bool xMinIsLesser = compare.getMinBounds().x <= p_minBounds.x;
		bool yMinIsLesser = compare.getMinBounds().y <= p_minBounds.y;
		
		bool minShared = compare.getMinBounds() == p_minBounds;
		bool maxShared = compare.getMaxBounds() == p_maxBounds;
		
		if(minShared)
		{
			if(xMaxIsGreater && yMaxIsGreater)
				return true;
			else
				return false;
		}
		else if(maxShared)
		{
			if(xMinIsLesser && yMinIsLesser)
				return true;
			else
				return false;
		}
		else
		{
			if(xMaxIsGreater && yMaxIsGreater && xMinIsLesser && yMinIsLesser)
				return true;
			else
				return false;
		}
	}
	
	bool operator==(boundingBox compareBox)
	{
		if(p_maxBounds == compareBox.getMaxBounds() && p_minBounds == compareBox.getMinBounds())
			return true;
		else
			return false;
	}
	
	bool operator>=(boundingBox compareBox)
	{
		if((p_maxBounds.x >= compareBox.getMaxBounds().x && p_maxBounds.y >= compareBox.getMaxBounds().y) && 
			(p_minBounds.x <= compareBox.getMinBounds().x && p_minBounds.y <= compareBox.getMinBounds().y))
		{
			return true;
		}
		else
			return false;
	}
	
	bool operator!=(boundingBox compareBox)
	{
		if(p_maxBounds == compareBox.getMaxBounds() && p_minBounds == compareBox.getMinBounds())
			return false;
		else
			return true;
	}
	
};

#endif