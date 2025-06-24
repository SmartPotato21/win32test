#include "basic_constructor.h"
#include <GL/gl.h>

// Object implementation
Object::Object()
{
    name = "made";

}

void Object::draw()
{
    
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
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
        glVertex2f(posX - 100.0f * scale, posY - 100.0f * scale);
        glVertex2f(posX + 100.0f * scale, posY - 100.0f * scale);
        glVertex2f(posX + 100.0f * scale, posY + 100.0f * scale);
        glVertex2f(posX - 100.0f * scale, posY + 100.0f * scale);
        
        
        
    glEnd();
}
