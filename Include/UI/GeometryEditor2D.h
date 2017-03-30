#ifndef GEOMETRYEDITOR2D_H_
#define GEOMETRYEDITOR2D_H_

#include <vector>
#include <list>
#include <deque>
#include <math.h>

#include <gl.h>
#include <glu.h>

#include <common/Vector.h>
#include <common/plfcolony.h>
#include <common/wxGLString.h>

#include <UI/geometryShapes.h>

class geometryEditor2D
{
private:
    
    /*! /brief
     *  This custom class was choosen because the list is much slower and this 
     *  class has been proven to be mcuh faster. It functions similiar to a list
     *  and you have many of the benefits of using a list but with the added speed bonus
     */ 
    plf::colony<node> _nodeList;
    
   /*! /brief
     *  So you might be thinking, why use a deque instead of a vector or a list?
     *  It is simple, a for a vector, when something is added or removed, the vector
     *  copies all of of the contents from one memory location to another. In some datatypes,
     *  we are storing the address of the node. If the address changes everytime we add or remove soemthing from
     *  the vector, this can create a number of issues.
     *  For a list, everything was already coded using vectors when the vector issue was discover. The
     *  deque contains many functions similiar to that of the vector and so the deque datatype was 
     *  the prefered choice. It has also bee researched that the list is very much slower compared
     *  to the deque. However, the speed is noticeable after 10,000 elements are present.
     *  Still, deque was choosen due to its overall speed.
     */ 
    
	std::deque<blockLabel> _blockLabelList;
    
	std::deque<edgeLineShape> _lineList;
    
	std::deque<arcShape> _arcList;
    
    wxGLStringArray _blockLabelNameArray;
    
    node *_nodeInterator1;// This is the index of the first selected node
    
    node *_nodeInterator2;// This is the index of the second selected node
    
    int _tolerance = 2;
    
    double *_zoomFactorPointer;
    
    /*! This function will check to see if there is an intersection between two lines. If so, get the node of intersection and return true
     * node0 is the first node that the user selects
     * node1 is the second node that the user selects
     * lineSegment is the line segment index that will be checked for an intersection
     * intersectionXPoint and YPoint are the (X, Y) intercetion points of the two lines
     */
	bool getIntersection(edgeLineShape prospectiveLine, edgeLineShape intersectionLine, double &intersectionXPoint, double &intersectionYPoint);
    
    /*! This function will calculate the shortest distance from a point to an arc */
	double shortestDistanceFromArc(Vector point, arcShape &arcSegment);
	
	/*! This function will get the number of instersection points where a line and an arc intersect */
	int getLineToArcIntersection(edgeLineShape &lineSegment, arcShape &arcSegment, Vector *pointVec);
	
	/*! This function will calculate the number of intersection points where two arcs intersect */
	int getArcToArcIntersection(arcShape& arcSegment1, arcShape &arcSegment2, Vector *point);
    
    

public:

    /*! This function is used to calcualte if the shortest distance between a line a node */
	double calculateShortestDistance(double p, double q, edgeLineShape segment);
    
    double calculateShortestDistanceFromArc(arcShape arcSegment, double xPoint, double yPoint)
    {
        Vector newVector;
        
        newVector.Set(xPoint, yPoint);
        return shortestDistanceFromArc(newVector, arcSegment);
    }
    
    bool setNodeIndex(node &iterator)
    {
        if(_nodeInterator1 == nullptr)
        {
            _nodeInterator1 = &iterator;
            return false;
        }
        else if(_nodeInterator2 == nullptr)
        {
            _nodeInterator2 = &iterator;
            return true;
        }
        
        return false;
    }

    plf::colony<node> *getNodeList()
    {
        return &_nodeList;
    }
    
    void setNodeList(plf::colony<node> list)
    {
        _nodeList = list;
    }
    
    std::deque<blockLabel> *getBlockLabelList()
    {
        return &_blockLabelList;
    }
    
    void setBlockLabelList(std::deque<blockLabel> list)
    {
        _blockLabelList = list;
    }
    
    std::deque<edgeLineShape> *getLineList()
    {
        return &_lineList;
    }
    
    void setLineList(std::deque<edgeLineShape> list)
    {
        _lineList = list;
    }
    
    std::deque<arcShape> *getArcList()
    {
        return &_arcList;
    }
    
    void setArcList(std::deque<arcShape> list)
    {
        _arcList = list;
    }

    void addNode(double xPoint, double yPoint);
    
    void addDragNode(double xPoint, double yPoint)
    {
        node newNode;
        newNode.setCenter(xPoint, yPoint);
        newNode.setDraggingState(true);
        _nodeList.insert(newNode);
    }
    
    void addBlockLabel(double xPoint, double yPoint);
    
    void addDragBlockLabel(double xPoint, double yPoint)
    {
        blockLabel newLabel;
        newLabel.setCenter(xPoint, yPoint);
        newLabel.setDraggingState(true);
        _blockLabelList.push_back(newLabel);
    }
    
    void addLine(node *firstNode, node *secondNode);
    
    void addLine(node &firstNode, node *secondNode)
    {
        addLine(&firstNode, secondNode);
    }
    
    void addLine(node *firstNode, node &secondNode)
    {
        addLine(firstNode, &secondNode);
    }
    
    void addLine()
    {
        addLine(nullptr, nullptr);
    }
    
    void addArc(arcShape &arcSeg, double tolerance, bool nodesAreSelected);
    
    void setZoomFactorAddress(double &address)
    {
        _zoomFactorPointer = &address;
    }
    
    void resetIndexs()
    {
        _nodeInterator1 = nullptr;
        _nodeInterator2 = nullptr;
    }
    
    void renderBlockNames(wxPaintDC *dc, double zoomFactor)
    {
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_COLOR_MATERIAL);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
        
        static wxGLString my_message;
        static wxGLStringArray my_messages;
        static wxGLNumberRenderer number;
        static bool first_time = true;
        // init them the first time only
        if(first_time)
        {
            my_message = wxString( wxT("Hello world !!!") );
            my_message.setFont( wxFont( 8.5, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL) );
            

            my_messages.addString( wxT("wxGLString can") );
            my_messages.addString( wxT("render strings in") );
            my_messages.addString( wxT("OpenGL easily!! ") );
            my_messages.addString( wxT("And with Unicode : \x1414 \x1562 \x1593") );
            my_messages.consolidate(dc);

            number.consolidate(dc);
            first_time = false;
        }
        my_message.scale(zoomFactor);
        my_message.consolidate(dc);


        // render string everytime
        my_message.bind();
        my_message.rotate(0);
        my_message.setFlip(false, true);
        
        glColor3f(1,0,0);
        my_message.render(0,0);

        my_messages.bind();
        my_messages.get(0).setFlip(false, true);
        my_messages.get(1).setFlip(false, true);
        my_messages.get(2).setFlip(false, true);
        my_messages.get(3).setFlip(false, true);
        
        glColor3f(0,0.6,0);     my_messages.get(0).render(5,200);
        glColor3f(0,0,0.6);     my_messages.get(1).render(55,225);
        glColor3f(0,0.6,0.6);   my_messages.get(2).render(105,250);
        glColor3f(0.6,0.6,0);   my_messages.get(3).render(155,275);

        number.bind();
        glColor3f(0,0,0);
        number.setFlip(false, true);
        number.renderNumber( -3.141591f, 250, 50 );
        
        glDisable(GL_BLEND);
        
      /*  for(int i = 0; i < _blockLabelNameArray.getNameArraySize(); i++)
        {
            _blockLabelNameArray.get(i).render(10 + 0.5, 10 + 0.5);
        }
         */ 
    }
    
    wxGLStringArray *getBlockNameArray()
    {
        return &_blockLabelNameArray;
    }
    
    void setLabelNameArray(wxGLStringArray stringArray)
    {
        _blockLabelNameArray = stringArray;
    }
	
};

#endif