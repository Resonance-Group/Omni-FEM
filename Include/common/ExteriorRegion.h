#ifndef EXTERIOR_REGION_H_
#define EXTERIOR_REGION_H_

/**
 * @class exteriorRegion
 * @author phillip
 * @date 22/07/17
 * @file ExteriorRegion.h
 * @brief 	This class is used to handle the data for the exterior region. 
 * 			This class will only be used if the user selects the problem to be
 * 			Axisymetric.
 */
class exteriorRegion
{
private:
	//! The center of the exterior region
	double p_centerExterior = 0.0;
	
	//! The radius of the exterior part of the region
	double p_radiusExterior = 0.0;
	
	//! Radius of the interior part of the region
	double p_radiusInterior = 0.0;
public:
	/**
	 * @brief Function that is used to set the center of the exterior region
	 * @param value The location along the z-axis of the axisymetric problem where the center
	 * 				of the block representing the external region is located. The units are determined
	 * 				by the user setting located in the problem preferences.
	 */
	void setCenter(double value)
	{
		p_centerExterior = value;
	}
	
	/**
	 * @brief Retrieves the center of the exterior region
	 * @return Returns a value representing the center of the exterior region.
	 */
	double getCenter()
	{
		return p_centerExterior;
	}
	
	/**
	 * @brief This function will set the radius of the sphere representing the exterior region 
	 * @param value The radius of hte sphere. The units are determined by the problem preferences.
	 */
	void setExteriorRadius(double value)
	{
		p_radiusExterior = value;
	}
	
	/**
	 * @brief Function that will retrieve the radius of the exterior region
	 * @return 	Returns a value representing the radius of the sphere 
	 * 			representing the exterior region.
	 */
	double getRadiusExterior()
	{
		return p_radiusExterior;
	}
	
	/**
	 * @brief Function that will set the radius of the sphere representing the interior region
	 * @param value	The radius of the sphere for the interior region which is defined by 
	 * 				the region in which the items of interest are located.
	 */
	void setInteriorRadius(double value)
	{
		p_radiusInterior = value;
	}
	
	/**
	 * @brief Function that will return the radius of the interior sphere
	 * @return Returns a value representing the interior radius of the sphere
	 */
	double getRadiusInterior()
	{
		return p_radiusInterior;
	}
};


#endif