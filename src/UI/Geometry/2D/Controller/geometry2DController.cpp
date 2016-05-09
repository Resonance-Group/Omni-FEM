#include <UI/geometryEditor2D.h>



int geometryEditor2DController::getDrawingHeightAbstract()
{
	return abstraction.getDrawingSizeHeight();
}



void geometryEditor2DController::setDrawingHeightAbstract(int height)
{
	abstraction.setDrawingSizeHeight(height);
}



void geometryEditor2DController::setDrawingWidthAbstract(int width)
{
	abstraction.setDrawingSizeWidth(width);
}



int geometryEditor2DController::getDrawingWidthAbstract()
{
	return abstraction.getDrawingSizeWidth();
}