#include "basic_constructor.h"
#include <GL/gl.h>

// Object implementation
Object::Object()
{
    name = "made";
}

std::string Object::getName()
{
    return name;
}

// Box implementation
Box::Box(int x)
{
    // Optionally do something with x
}

void Box::draw()
{
    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(posX - 100.0f, posY- 100.0f);
        glVertex2f(posX + 200.0f, posY- 100.0f);
        glVertex2f(posX + 200.0f, posY + 200.0f);
        glVertex2f(posX- 100.0f, posY + 200.0f);
        
        
        
    glEnd();
}
