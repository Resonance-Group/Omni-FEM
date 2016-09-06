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
    // Use this site for reference: http://mymathforum.com/algebra/21368-find-equation-circle-given-two-points-arc-angle.html
    startNodeXCoordinate = arcNodeList[nodeIndex1].getCenterXCoordinate();
    endNodeXCoordinate = arcNodeList[nodeIndex2].getCenterXCoordinate();
    
    startNodeYCoordinate = arcNodeList[nodeIndex1].getCenterYCoordinate();
    endNodeYCoordinate = arcNodeList[nodeIndex2].getCenterYCoordinate();
    
    double distanceSquared = pow(startNodeXCoordinate - endNodeXCoordinate, 2) + pow(startNodeYCoordinate - endNodeYCoordinate, 2);
    double xCenter = 0;
    double yCenter = 0;
    double xMid = 0;
    double yMid = 0;
    double a = 0; // This variable does not have much significance. It is only used as a half-way point for easier calculation
    double midSlope = 0;
    
  /*  if(startNodeXCoordinate < endNodeXCoordinate)
    {
        double temp = startNodeXCoordinate;
        startNodeXCoordinate = endNodeXCoordinate;
        endNodeXCoordinate = temp;
        
        temp = startNodeYCoordinate;
        startNodeYCoordinate = endNodeYCoordinate;
        endNodeYCoordinate = startNodeYCoordinate;
    }*/
    
    radius = sqrt(distanceSquared / (2.0 * (1.0 - cos(arcAngle * PI / 180.0))));// Fun fact, the cosine function evaluates in radians
    
    xMid = (startNodeXCoordinate + endNodeXCoordinate) / 2.0;
    
    yMid = (startNodeYCoordinate + endNodeYCoordinate) / 2.0;
    
    midSlope = (startNodeXCoordinate - endNodeXCoordinate) / (endNodeYCoordinate - startNodeYCoordinate);
    
    a = sqrt(pow(radius, 2) - (distanceSquared / 4.0)); // This is just an intermediate varable to make calculations easier
    
    if(isCounterClockWise)
    {
        xCenterCoordinate = xMid + a / sqrt(pow(midSlope, 2) + 1);
        yCenterCoordinate = yMid + (midSlope * a) / sqrt(pow(midSlope, 2) + 1);
    }
    else
    {
        xCenterCoordinate = xMid - a / sqrt(pow(midSlope, 2) + 1);
        yCenterCoordinate = yMid - (midSlope * a) / sqrt(pow(midSlope, 2) + 1);
    }

}



void arcShape::draw()
{
 //   double startAngle = ((atan2(yCenterCoordinate - startNodeYCoordinate, xCenterCoordinate - startNodeXCoordinate) * 180.0) / PI)  - 180.0;
    /* Computes the start and stop angle for the arc. atan returns in radians. This gets converted to degrees */
    double startAngle = atan((startNodeYCoordinate - yCenterCoordinate) / (startNodeXCoordinate - xCenterCoordinate)) * (180.0 / PI);
    if(startAngle < 0)
        startAngle += 180.0;
        
    double endAngle = 180.0 - atan((endNodeYCoordinate - yCenterCoordinate) / (xCenterCoordinate - endNodeXCoordinate)) * (180.0 / PI);
    
    if(numSegments == -1)
    {
        if(arcAngle < 10)
            numSegments = 10;
        else
            numSegments = arcAngle / 3.0;
    }
    else if(numSegments < 2)
        numSegments = 2;
        
    double delta = ((endAngle - startAngle) * (PI / 180.0)) / (double)numSegments;
    
    glBegin(GL_LINE_STRIP);
        glVertex2d(startNodeXCoordinate, startNodeYCoordinate);
        
        for(int i = 1; i < numSegments; i++)
        {
            double arc = (i * delta);// this is in radians
            
            double xValue = xCenterCoordinate + (startNodeXCoordinate - xCenterCoordinate) * cos(arc) + (yCenterCoordinate - startNodeYCoordinate) * sin(arc);
            double yValue = yCenterCoordinate + (startNodeYCoordinate - yCenterCoordinate) * cos(arc) + (startNodeXCoordinate - xCenterCoordinate) * sin(arc);
            
            double x = radius * cos(arc);
            double y = radius * sin(arc);
            
            glVertex2d(xValue, yValue);
        }
        glVertex2d(endNodeXCoordinate, endNodeYCoordinate);
    glEnd();
}	
	
