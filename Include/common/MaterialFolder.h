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
    //! This next section are the getters and setters for the private variables
    void setFolderName(string name)
    {
        _folderName = name;
    }
    
    string getFolderName()
    {
        return _folderName;
    }
    
    void setFolderURL(string url)
    {
        _folderURL = url;
    }
    
    string getFolderURL()
    {
        return _folderURL;
    }
    
    void setFolderVendor(string vendor)
    {
        _folderVendor = vendor;
    }
    
    string getFolderVendor()
    {
        return _folderVendor;
    }
};


#endif