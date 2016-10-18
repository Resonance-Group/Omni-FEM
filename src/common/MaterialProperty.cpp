#include "common/MaterialProperty.h"


void materialProperty::setName(string name)
{
    _propertyName = name;
}



string materialProperty::getName()
{
    return _propertyName;
}