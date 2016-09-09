#include <UI/geometryShapes.h>

arcShape::arcShape() : edgeLineShape()
{
	nodeIndex1 = 0;
	nodeIndex2 = 0;
	
	isHidden = false;
	
	arcAngle = 90.0d;
	maxSideLength = 10.0d;
	
	boundaryMarker = "<None>";
	inConductor = "<None>";
	
	isNormalDirection = true;
}



void arcShape::setArcAngle(double angleOfArc)
{
	arcAngle = abs(angleOfArc);
    if(angleOfArc > 0)
        isCounterClockWise = true;
    else
        isCounterClockWise = false;
}



double arcShape::getArcAngle()
{
    if(isCounterClockWise)
        return -arcAngle;
    else
        return arcAngle;
}



void arcShape::setNumSegments(double segments)
{
	numSegments = segments;
}


	
double arcShape::getnumSegments()
{
	return numSegments;
}
	

void arcShape::calculate(std::vector<node> &arcNodeList)
{
    double xCenter = 0;
    double yCenter = 0;
    double xMid = 0;
    double yMid = 0;
    double a = 0; // This variable is the distance from the midpoint of the two end points to the center of the arc
    double midSlope = 0;
    double slope = 0;
    double distanceSquared = 0;
    
    // Use this site for reference: http://mymathforum.com/algebra/21368-find-equation-circle-given-two-points-arc-angle.html
 /*   if(arcNodeList[nodeIndex2].getCenterXCoordinate() > arcNodeList[nodeIndex1].getCenterXCoordinate())
    {
        startNodeXCoordinate = arcNodeList[nodeIndex2].getCenterXCoordinate();
        endNodeXCoordinate = arcNodeList[nodeIndex1].getCenterXCoordinate();
        
        startNodeYCoordinate = arcNodeList[nodeIndex2].getCenterYCoordinate();
        endNodeYCoordinate =  arcNodeList[nodeIndex1].getCenterYCoordinate();
    }*/
 //   else
    {
        startNodeXCoordinate = arcNodeList[nodeIndex1].getCenterXCoordinate();
        endNodeXCoordinate = arcNodeList[nodeIndex2].getCenterXCoordinate();
        
        startNodeYCoordinate = arcNodeList[nodeIndex1].getCenterYCoordinate();
        endNodeYCoordinate = arcNodeList[nodeIndex2].getCenterYCoordinate();
    }
    
    distanceSquared = pow(startNodeXCoordinate - endNodeXCoordinate, 2) + pow(startNodeYCoordinate - endNodeYCoordinate, 2);
    
    radius = sqrt(distanceSquared / (2.0 * (1.0 - cos(arcAngle * PI / 180.0))));// Fun fact, the cosine function evaluates in radians
    
    xMid = (startNodeXCoordinate + endNodeXCoordinate) / 2.0;
    
    yMid = (startNodeYCoordinate + endNodeYCoordinate) / 2.0;
    
    slope = (startNodeYCoordinate - endNodeYCoordinate) / (startNodeXCoordinate - endNodeXCoordinate);
    
    midSlope = -1.0 / slope;
    
    a = sqrt(pow(radius, 2) - (distanceSquared / 4.0)); // This is just an intermediate varable to make calculations easier
    
    if((startNodeYCoordinate > endNodeYCoordinate && isCounterClockWise) || (startNodeYCoordinate < endNodeYCoordinate && !isCounterClockWise))
    {
        // This will calculate the center that is below the arc.
        // If the start node is lower then the end node, the logic is reversed. This potion will create
        // the center above the arc.
        xCenterCoordinate = xMid + a / sqrt(pow(midSlope, 2) + 1);
        yCenterCoordinate = yMid + (midSlope * a) / sqrt(pow(midSlope, 2) + 1);
    }
    else
    {
        // This will calculate the center above the arc
        xCenterCoordinate = xMid - a / sqrt(pow(midSlope, 2) + 1);
        yCenterCoordinate = yMid - (midSlope * a) / sqrt(pow(midSlope, 2) + 1);
    }

}



void arcShape::draw()
{
 //   double startAngle = ((atan2(yCenterCoordinate - startNodeYCoordinate, xCenterCoordinate - startNodeXCoordinate) * 180.0) / PI)  - 180.0;
    /* Computes the start and stop angle for the arc. atan returns in radians. This gets converted to degrees */
    
    if(numSegments == -1)
    {
        if(arcAngle < 10)
            numSegments = 10;
        else
            numSegments = arcAngle / 3.0;
    }
    else if(numSegments < 2)
        numSegments = 2;
    
    double theta = 0;
    if(isCounterClockWise)
        theta = (arcAngle) / (double)numSegments;
    else
        theta = (-arcAngle) / (double)numSegments;
        
    double startAngle = atan2(yCenterCoordinate - startNodeYCoordinate, xCenterCoordinate - startNodeXCoordinate) * (180.0 / PI) - 180.0;
    
    glBegin(GL_LINE_STRIP);
        glVertex2d(startNodeXCoordinate, startNodeYCoordinate);
        
        for(int i = 1; i < numSegments; i++)
        {
            double arc = (startAngle + i * theta) * (PI / 180); 
            double x = radius * cos(arc);
            double y = radius * sin(arc);
            
            glVertex2d(xCenterCoordinate + x, yCenterCoordinate + y);
        }
        glVertex2d(endNodeXCoordinate, endNodeYCoordinate);
    glEnd();
}	
	
