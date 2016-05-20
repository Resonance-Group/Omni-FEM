#ifndef GEOMETRYEDITORCONTROLLER_H_
#define GEOMETRYEDITORCONTROLLER_H_

#include <wx/wx.h>
#include <wx/glcanvas.h>
#include <UI/common.h>
#include <freeglut.h>
#include <gl.h>
#include <glu.h>
#include <UI/geometryShapes.h>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <UI/wxGLString.h>
#include <common/Vector.h>
#include <math.h>



class geometryEditorController
{
public:
	geometryEditorController();
	
	/*! This function is used to calcualte if the shortest distance between a line a node */
	double calculateShortestDistance(double p, double q, int segmentIndex, std::vector<node> const &refNodeList, std::vector<edgeLineShape> const &refLineList);
	
private:
	
	
};

#endif