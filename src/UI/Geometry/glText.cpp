#include <UI/ModelDefinition/glText.h>


glText::glText(physicProblems problem)
{
    _problem = problem;
    
    FT_Library font;
    
 //   if(FT_Init_FreeType(&font))
 //   {
        // Throw an error if there is something wrong
 //   }
    
    
}



void glText::renderBlockLabelText(blockProperty &labelproperty)
{
    
}