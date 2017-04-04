#include <UI/ModelDefinition/glText.h>


glText::glText(physicProblems problem)
{
    _problem = problem;
    
    FT_Library font;
    
 //   if(FT_Init_FreeType(&font))
 //   {
        // Throw an error if there is something wrong
 //   }
    FT_Face face; 
    if(FT_New_Face(font, "fonts/arial.ttf", 0, &face))
    {
        // Error if something went wrong
    }
    
    FT_Set_Pixel_Sizes(face, 0, 5);
    
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    for(GLubyte c = 0; c < 128; c++)
    {
        if(FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            // Error if something happens
        }
        
       GLuint texture;
       glGenTextures(1, &texture);
       glBindTexture(GL_TEXTURE_23D, texture);
       glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
        
        character addChar = {
            texture, 
            wxSize(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            wxSize(face->glyph->bitmap_left, face->glyph->bitmap_top),
            face->glyph->advance.x
        };
        
        _characterList.insert(std::pair<GLchar, character>(c, addChar));
    }
        
    
    
}



void glText::renderBlockLabelText(blockProperty &labelproperty)
{
    
}
