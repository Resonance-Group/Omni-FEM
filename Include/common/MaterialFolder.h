#ifndef MATERIALFOLDER_H_
#define MATERIALFOLDER_H_

#include <string>

using namespace std;


/*! /brief  In the materials library, folders will be implemented for orginzation purposes
 *          This class contains all things needed for specifing a folder
 *          Please note that the class does not contain a data type for the materials that are stored
 *          within in, that is because,
 * 
 */ 
class materialFolder
{
private:
    //! The name of the folder
    string _folderName;
    
    //! The URL that belongs to the vendor
    string _folderURL;
    
    //! The vendor that the folder is associated with
    string _folderVendor;
public:

    //! Sets the folder name
    /*!
        \param name The name of the folder
    */ 
    void setFolderName(string name)
    {
        _folderName = name;
    }
    
    //! Retrieves the name of the folder
    /*!
        \return Returns a string representing the name 
                of the folder
    */ 
    string getFolderName()
    {
        return _folderName;
    }
    
    //! Sets the URL that can be associated with the folder
    /*!
        \param url The url that the folder is associated with
    */ 
    void setFolderURL(string url)
    {
        _folderURL = url;
    }
    
    //! Retrieves the url of the folder
    /*!
        \return Returns a string representing the url 
                associated to the folder
    */ 
    string getFolderURL()
    {
        return _folderURL;
    }
    
    //! Sets the vendor that is associated with the folder
    /*!
        \param vendor The vendor name that is associated with the folder
    */ 
    void setFolderVendor(string vendor)
    {
        _folderVendor = vendor;
    }
    
    //! Retrieves the vendor associated with the folder
    /*!
        \return Returns a string representing the vendor 
                associated to the folder
    */ 
    string getFolderVendor()
    {
        return _folderVendor;
    }
};


#endif