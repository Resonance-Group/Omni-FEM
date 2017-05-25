#ifndef BLOCKPROPERTY_H_
#define BLOCKPROPERTY_H_

#include <string>

#include <common/ElectroStaticMaterial.h>
#include <common/MagneticMaterial.h>
#include <common/CircuitProperty.h>
#include <common/enums.h>


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
    
    std::string _materialName = "None";
    
    std::string _circuitName = "None";
    
    bool _meshSizeIsAuto = true;
    
    double _meshSize = 0;
    
    double _numberOfTurns = 1;
    
    double _magnetization = 0;
    
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
    
    void setMagnetization(double value)
    {
        _magnetization = value;
    }
    
    double getMagnetization()
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