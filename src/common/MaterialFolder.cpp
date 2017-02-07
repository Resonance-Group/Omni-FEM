#include "common/MaterialFolder.h"


void materialFolder::setFolderName(string name)
{
    _folderName = name;
}



string materialFolder::getFolderName()
{
    return _folderName;
}



void materialFolder::setFolderURL(string url)
{
    _folderURL = url;
}



string materialFolder::getFolderURL()
{
    return _folderURL;
}



void materialFolder::setFolderVendor(string vendor)
{
    _folderVendor = vendor;
}



string materialFolder::getFolderVendor()
{
    return _folderVendor;
}