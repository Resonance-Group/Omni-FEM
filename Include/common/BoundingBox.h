#ifndef BOUNDINGBOX_H_
#define BOUNDINGBOX_H_

#include <algorithm>

#include <wx/wx.h>

class boundingBox
{
private:
	
	wxRealPoint p_maxBounds = wxRealPoint(0, 0);
	
	wxRealPoint p_minBounds = wxRealPoint(0, 0);
	
public:

	boundingBox(wxRealPoint startingPoint)
	{
		p_maxBounds = startingPoint;
		p_minBounds = startingPoint;
	}
	
	boundingBox()
	{
		
	}

	void addPoint(wxRealPoint point)
	{
		p_maxBounds.x = std::max(p_maxBounds.x, point.x);
		p_maxBounds.y = std::max(p_maxBounds.y, point.y);
		
		p_minBounds.x = std::min(p_minBounds.x, point.x);
		p_minBounds.y = std::min(p_minBounds.y, point.y);
	}

	wxRealPoint getMaxBounds()
	{
		return p_maxBounds;
	}
	
	wxRealPoint getMinBounds()
	{
		return p_minBounds;
	}
	
	/**
	 * @brief 	FUnction that will check if the current bounding box is inside of another
	 * 			bounding box. This is comparing from the persepective that the this bounding box
	 * 			is contained inside of the compare bounding box.
	 * @param compare
	 * @return 
	 */
	bool isInside(boundingBox compare)
	{
		bool xMaxIsGreater = compare.getMaxBounds().x > p_maxBounds.x;
		bool yMaxIsGreater = compare.getMaxBounds().y > p_maxBounds.y;
		
		bool xMinIsLesser = compare.getMinBounds().x < p_minBounds.x;
		bool yMinIsLesser = compare.getMinBounds().y < p_minBounds.y;
		
		if(xMaxIsGreater && yMaxIsGreater && xMinIsLesser && yMinIsLesser)
			return true;
		else
			return false;
	}
	
	bool operator==(boundingBox compareBox)
	{
		if(p_maxBounds == compareBox.getMinBounds() && p_minBounds == compareBox.getMinBounds())
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
	
};

#endif