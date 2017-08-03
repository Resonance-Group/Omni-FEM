#ifndef ELECTROSTATICPREF_H_
#define ELECTROSTATICPREF_H_

#include <math.h>

#include <wx/string.h>

#include <common/enums.h>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

//! Class that is used to handle all of the prefences of simulation for electrostatic simulations
/*! 
    This class stores the solver/mesher preferences for electrostatic simulations.
    The precision of the problem, depth of the problem,comments, min angle,
    coordinate type, problem type, and length units can be found here
*/ 
class electroStaticPreference
{
private:
	friend class boost::serialization::access;

    //! Variable that specifies the length of the geometry into the page
    /*!
        This variable is only used if the the simulation is a planar problem.
        This variable is primarly used for scaling integral results in the post
        processor to the apprioate length. Caluclations such as force and 
        inductance use this variable. The units for the Depth are the same
        as the length units which is specified in _unitLength
    */ 
    double _depth = 1;
    
    //! The variable that specifies the stopping criteria for the solver.
    /*!
        The linear algebra solver can be represented by: 
        \f$ M*x=b \f$
        or M * x = b.
        Where M is a square matrix, b is a vector, and x is a vector of
        unknowns. The precision value determines the maximum allowable value
        for:
        \f[ \frac{\left \| b-Mx \right \|}{\left \| b \right \|} \f]
        or abs(b - M * x) / abs(b).
    */ 
    double _precision = powf(10, -8);
    
    //! A constraint that is used in the mesher to prevent convergence issues
    /*!
        This comment will need to be updated once the mesher is finished.
        The mesher adds points to the mesh in order to ensure that no angles 
        smaller then the value specified by this variable occur. If they do
        occur, then the need is to terminate the mesh and have the 
        user deal with the issue.
    */ 
    double _minAngle = 30;
    
    //! Variable that stores any user comments about the simulation problem
    wxString _comments = wxString("Add comments here");
    
    //! Variable that specifics what the 2-D problem will be like
    /*!
        This variable will specify if the problem is planar or axisymmetric
    */ 
    problemTypeEnum _probType = PLANAR;
    
    //! Variable that specifes what dimension is associated with the geometry model
    unitLengthEnum _unitLength = INCHES;
	
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version)
	{
		ar & _depth;
		ar & _precision;
		ar & _minAngle;
		std::string comments = _comments.ToStdString();
		ar & comments;
		_comments = wxString(comments);
		ar & _probType;
		ar & _unitLength;
	}
    
public:
    //! Sets the depth of the problem
    /*!
        The depth value is only used in planar problems
        \param depth The value of the depth of the problem.
                    The units for the depth are specified by the 
                    setter/getter for the units variable. The
                    units are the same as the selected length units
    */ 
    void setDepth(double &depth)
    {
        _depth = depth;
    }
    
    //! Retrieves the depth of the problem
    /*!
        \return Returns the value representing the depth of the problem
                The units for hte depth are the same as the selected
                length units
    */ 
    double getDepth()
    {
        return _depth;
    }
    
    //! Sets the solver precision for the problem
    /*!
        \param precision The solver precision value for the solver
    */ 
    void setPrecision(double &precision)
    {
        _precision = precision;
    }
    
    //! Retrieves the solver precision for the problem
    /*!
        \return Returns a value representing the solver precision
    */ 
    double getPrecision()
    {
        return _precision;
    }
    
    //! Sets the proble type for the simulation problem
    /*!
        Currently, there are only two types: planar
        and axisymmestric
        \param prob The problem type that the simulation will be
    */ 
    void setProblemType(problemTypeEnum prob)
    {
        _probType = prob;
    }
    
    //! Retrieves the problem type of the simulation
    /*!
        \return Returns a value representing the 
                problem type for the simulation
    */ 
    problemTypeEnum getProblemType()
    {
        return _probType;
    }
    
    //! Sets the dimensions for any length units in the simulation
    /*!
        Identifies what unit is associated with the dimension prescribed in
        the model's geometry
        \param unit The length unit that is associated with the simulation
    */ 
    void setUnitLength(unitLengthEnum unit)
    {
        _unitLength = unit;
    }
    
    //! Retreieves the length unit associated with the problem
    /*!
        \return Returns the unit that is associated with the dimension 
                prescribed in the model's geometry.
    */ 
    unitLengthEnum getUnitLength()
    {
        return _unitLength;
    }
    
    //! Sets the min angle constraint for the mesher
    /*!
        \sa _minAngle
        \param angle the min angle associated with the problem
    */ 
    void setMinAngle(double angle)
    {
        _minAngle = angle;
    }
    
    //! Retrieves the min angle for the mesher
    /*!
        \sa _minAngle
        \return Returns the value associated with the minimum angle
                constaint of the mesher
    */ 
    double getMinAngle()
    {
        return _minAngle;
    }
    
    //! Sets any user enter comments for the simulation
    /*!
        \param comment The comment(s)
    */ 
    void setComments(wxString comment)
    {
        _comments = comment;
    }
    
    //! Retrieves the comments for the simulation
    /*!
        \return Returns the comments that the user entered
    */ 
    wxString getComments()
    {
        return _comments;
    }
    
    //! Function that checks if the simulation type is axisymmetric
    /*!
        \return Returns true if the problem is an axisymetic.
                Return false if the problem is planar
    */ 
    bool isAxistmmetric()
    {
        if(_probType == AXISYMMETRIC)
            return true;
        else
            return false;
    }
 
};

#endif
