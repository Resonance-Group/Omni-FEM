#ifndef BLOCKPROPERTY_H_
#define BLOCKPROPERTY_H_

#include <string>

#include <common/ElectroStaticMaterial.h>
#include <common/MagneticMaterial.h>
#include <common/CircuitProperty.h>
#include <common/enums.h>

//! Class that handles all properties that are related to the block label
/*!
    Any of the block label properties that the user
    is able to change or set is handled by this class.
    It was decided to abstract the properties out from the class
    that handles the geometic portion of the class in order to keep
    the properties and the geometry seperated
*/ 
class blockProperty
{
private:
    //! Datatype used to store if the mesh is extremely fine->extremely Coarse or a custom mesh size
    /*!
        This datatype is looked at when the program create the mesh.
        An extremely fine value will tell the mesher that the 
        element size needs to be as small as possible for the domain.
        An extremely coarse value will tell the mesher that the
        element size needs to be as large as possible in the domain.
        And a custom value tells the mesher to look at the meshSize
        value for the size of the mesh element. Note that the name
        No Mesh and None are reserved for Omni-FEM use
    */ 
    meshSize _meshSizeType = meshSize::MESH_NORMAL;
    
    //! The material name that is associated with the block label
    /*!
        This is the name that is displayed on the canvas. This is considered
        as the block label name since the material name is required
        for all simulations
    */ 
    std::string _materialName = "None";
    
    //! The circuit name that is associated with the block label
    /*!
        This only pertains to magnetic simualtions.
        With magnetic simulations, a circuit can be created 
        in order to simulate current going through a coil or 
        a cross-section of some sort
    */ 
    std::string _circuitName = "None";
    
    //! Boolean that is used to determine if the mesher should auto zise
    /*!
        Currently, it is unknown how the mesher will handle an auto size. However
        if this boolean is set to true, the mesher will the mesh with a pre-determined value
    */ 
    bool _meshSizeIsAuto = true;
    
    //! How large of an area tthat each element takes up
    /*!
        This parameters descirbes how mcuh area each element is when creating the mesh.
        A lower mesh size equates to a higher density since a lower area allows the mesher to
        fit in more elements in a subdomain
    */ 
    double _meshSize = 0;
    
    //! If the block label is to be associated with a coil, then this is the number of turns of wire around the coil
    /*!
        This parameter only pertains to magnetic simulations. This represets the number of turns that the wire takes
        within the subdomain. The region will be treated as a stranded conductor. In order for proper operation,
        the accomying circuit property must be set to series as each strand within the coil is connected as 
        a series circuit
    */ 
    double _numberOfTurns = 1;
    
    //! This is an angle that describes the direction of magnetization.
    /*!
        This parameter only pertains to magnetic simulations. The parameter is actually an 
        angle whose reference line is parallel to the x-axis. A value of 0 means that the 
        direction is parallel to the x-axis and pointing to the right. A value of 90 means that the
        direction is parallel to the y-axis and pointing upwards. All positive angles are in the 
        counter-clockwise direction while all negative angles are in the clockwise direction.
        Alternatively, this can be a function (hence the string part) of the block label position.
        Some keywords for the function is as follows:
        
        theta - denotes the angle (in degree) of line connecting the center of each block label
                with the position (0,0).
      
        R - denotes the length of the line connecting the center of each block label with the 
            poition (0,0)
      
        x - denotes the x position of the center of the block label in cartesian
      
        y - denotes the y position of the center of the block label in cartesian
      
        r - denotes the r position of the center of the block label. Only use if the problem is
            an axisymmeteric problem
      
        z - denotes the z position of the center of the block label. ONly use if the problem is
            and axisymmetric problem
    */ 
    wxString _magnetization = 0;
    
    unsigned int _groupNumber = 0;
    
    bool _isExternalRegion = false;
    
    bool _isDefault = false;
    
public:
    //! Sets the Mesh Size Type
    /*!
        \param type This is an enum that specifies what the mesh size type should be
    */ 
    void setMeshSizeType(meshSize type)
    {
        _meshSizeType = type;
    }
    
    //! Returns that Mesh Size Type
    /*!
        \return Returns an enum that describes what the mesh size type is
    */ 
    meshSize getMeshsizeType()
    {
        return _meshSizeType;
    }
    
    //! Sets the name of the block label
    /*!
        \param name The name that the block label will be. This name will be displayed on the canvas if the user wants it
    */ 
    void setMaterialName(std::string name)
    {
        _materialName = name;
    }
    
    //! Gets the name of the block label
    /*!
        \return Returns the name to the block label
    */ 
    std::string getMaterialName()
    {
        return _materialName;
    }
    
    //! Sets the circuit name of the block label
    /*!
        This only applies to magnetic simulations.
        \param name The name of the circuit that the block label belongs to. 
                    This name will be displayed on the canvas if the user needs to
    */ 
    void setCircuitName(std::string name)
    {
        _circuitName = name;
    }
    
    //! Gets the circuit name of the block label
    /*!
        This only applies to magnetic simulations
        \return Returns the name of the circuit
    */ 
    std::string getCircuitName()
    {
        return _circuitName;
    }
    
    //! Sets the state of the auto mesh
    /*!
        \param state Boolean that states whether or not the mesh size should be
                     automatically caluclated. True for auto on, False for
                     auto off
    */ 
    void setAutoMeshState(bool state)
    {
        _meshSizeIsAuto = state;
    }
    
    //! Gets the state of the auto mesh variable
    /*!
        \return Returns True if the user selected for the mesher to automatically set
                        the mesh size. False otherwise
    */ 
    bool getAutoMeshState()
    {
        return _meshSizeIsAuto;
    }
    
    // TODO: needs a better commenting
    //! Sets the mesh size of the elements.
    /*!
        \param size The size that the elements should be equal to
                    in the mesher
    */ 
    void setMeshSize(double size)
    {
        _meshSize = size;
    }
    
    // TODO: needs a better commenting
    //! Gets the mesh size of the elements
    /*!
        \return Returns the mesh size that the user set to the 
                the block label
    */ 
    double getMeshSize()
    {
        return _meshSize;
    }

    //! Sets the number of turns on the block label
    /*!
        This only applies to magnetic simulations
        \param turnCount The number of turns that the wire is wrapped around the section 
                        that belongs to the block label
    */ 
    void setNumberOfTurns(double turnCount)
    {
        _numberOfTurns = turnCount;
    }
    
    //! Returns the number of turns belonging to the label
    /*!
        This only applies to magnetic simulations
        \return Returns the number of turns that belong to the block label
    */ 
    double getNumberOfTurns()
    {
        return _numberOfTurns;
    }
    
    //! Sets the direction of magnetiation (in degrees) of the block label
    /*!
        This function only pertains to magnetic simulations. The reference line
        for the angle is parallel to the x-axis. All positive angles are a counter-clockwise direction
        and negative angles are clockwise direction. Alternatively, a function can be used instead of 
        a hard coded value. For keywords to the function, see the documentation of the private variable
        that this function accesses
        \sa _magnetization
        \param value The magnetization direction of the block label
    */ 
    void setMagnetization(wxString value)
    {
        _magnetization = value;
    }
    
    //! Gets the magnetization direction that is associated with the block label
    /*!
        This function only pertains to magnetic simulations.
        \sa _magnetization
        \return Returns the string of the magnetization direction
    */ 
    wxString getMagnetization()
    {
        return _magnetization;
    }
    
    //! Sets the group number that the block label belongs to
    /*!
        \param number The group number that the block label will belong to
    */ 
    void setGroupNumber(unsigned int number)
    {
        _groupNumber = number;
    }
    
    //! Returns the group number that the block label belongs to
    /*!
        \return Returns the group number that the block label belongs to
    */ 
    unsigned int getGroupNumber()
    {
        return _groupNumber;
    }
    
    void setIsExternalState(bool state)
    {
        _isExternalRegion = state;
    }
    
    bool getIsExternalState()
    {
        return _isExternalRegion;
    }
    
    //! Sets if the block label is the default label or not
    /*!
        \param state Boolean that specifies if the block label is default (T) or
                    not the default (F)
    */ 
    void setDefaultState(bool state)
    {
        _isDefault = state;
    }
    
    //! Returns if the block label is default
    /*!
        \return Returns True if the block label is default. Otherwise, returns False.
    */ 
    bool getDefaultState()
    {
        return _isDefault;
    }
};

#endif