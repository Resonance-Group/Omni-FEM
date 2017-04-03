#ifndef GLTEXT_H_
#define GLTEXT_H_

#include <string>
#include <map>

#include <common/enums.h>
#include <common/GeometryProperties/BlockProperty.h>

#include <freeglut.h>
#include <gl.h>
#include <glu.h>

#include <wx/wx.h>

#include <ft2build.h>
#include FT_FREETYPE_H

/* For reference only. Texture functions that appear in OpenGL 2.0
 * glTextParameterf
 * glTextParameterfv
 * glTextParameteri
 * glTextParameteriv
 * 
 * glPixelStorei
 * glPixelStoref
 */ 
 
 // This code as adapted from https://learnopengl.com/code_viewer.php?code=in-practice/text_rendering

struct character
{
    GLuint textureID; // ID Handle of th textrue
    wxSize glyphSize; // Size of the glyph
    wxSize glyphBearing; // Offset from baseline to the left/top of glyph
    GLuint advance; // Horizontol offset to advance to next glyph
};



class glText
{
private:
    physicProblems _problem = physicProblems::NO_PHYSICS_DEFINED;
    
    std::map<GLchar, character> _characterList;
    
    GLuint _VAO, _VBO;
    
public:
    glText(physicProblems problem);

    void renderBlockLabelText(blockProperty &labelproperty);

};

#endif