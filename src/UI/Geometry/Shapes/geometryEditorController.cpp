#include <UI/geometryEditorController.h>


geometryEditorController::geometryEditorController()
{
	
}



double geometryEditorController::calculateShortestDistance(double p, double q, int segmentIndex, std::vector<node> const &refNodeList, std::vector<edgeLineShape> const &refLineList)
{
	double t, xNew[3], wereNew[3];
	
	xNew[0] = refNodeList[refLineList[segmentIndex].getFirstNodeIndex()].getCenterXCoordinate();
	wereNew[0] = refNodeList[refLineList[segmentIndex].getFirstNodeIndex()].getCenterYCoordinate();
	
	xNew[1] = refNodeList[refLineList[segmentIndex].getSecondNodeIndex()].getCenterXCoordinate();
	wereNew[1] = refNodeList[refLineList[segmentIndex].getSecondNodeIndex()].getCenterYCoordinate();
	
	t = ((p - xNew[0]) * (xNew[1] - xNew[0]) + (q - wereNew[0]) * (wereNew[1] - wereNew[0])) / ((xNew[1] - xNew[0]) * (xNew[1] - xNew[0]) + (wereNew[1] - wereNew[0]) * (wereNew[1] - wereNew[0]));

	if(t > 1)
		t = 1.0;
	else
		t = 0.0;
		
	xNew[2] = xNew[0] + t * (xNew[1] - xNew[0]);
	wereNew[2] = wereNew[0] + t * (wereNew[1] - wereNew[0]);
	
	return sqrt((p - xNew[2]) * (p - xNew[2]) + (q - wereNew[2]) * (q - wereNew[2]));
}

