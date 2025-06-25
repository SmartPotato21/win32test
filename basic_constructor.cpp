#include "basic_constructor.h"
#include <windows.h>
#include <GL/gl.h>
#include <math.h>

// Object implementation
Object::Object()
{
    name = "made";

}

void Object::draw(std::vector<float> &verts, RECT &rect)
{
    
}

std::string Object::getName()
{
    return name;
}



Circle::Circle()
{

}

void Circle::draw(std::vector<float> &verts, RECT &rect)
{
    float screenWidth = float(rect.right-rect.left);
    float screenHeight = float(rect.bottom-rect.top);

    float pxWidth = 100.0f;
    float ndcSize = pxWidth / (screenWidth / 2.0f); // size in NDC

    // Convert pixel position to NDC
    float centerX = (2.0f * posX / screenWidth) - 1.0f;
    float centerY = 1.0f - (2.0f * posY / screenHeight);

    // Now create triangle vertices relative to center
    float x1 = centerX - ndcSize / 2.0f;
    float y1 = centerY + ndcSize / 2.0f;

    float x2 = centerX + ndcSize / 2.0f;
    float y2 = centerY + ndcSize / 2.0f;

    float x3 = centerX + ndcSize / 2.0f;
    float y3 = centerY - ndcSize / 2.0f;

    

    std::vector<float> toadd = {
        
    };

    float degree = 2.0f;
    float increment = degree * 3.14159/180;

    float rad = degree * 3.14159/180;

    for (int i = 0; i < 360/degree; i++)
    {
        toadd.push_back(0.0f);
        toadd.push_back(0.0f);
        toadd.push_back(0.0f);

        if(i > 0)
        {
            toadd.push_back(cos(rad+(increment * (i-1))) * 0.1f );
            toadd.push_back(sin(rad+(increment * (i-1))) * 0.1f );
            toadd.push_back(0.0f);
        }
        else
        {
            toadd.push_back(0.1f);
            toadd.push_back(0.0f);
            toadd.push_back(0.0f);
        }


        toadd.push_back(cos(rad + (increment * i))*0.1f);
        toadd.push_back(sin(rad + (increment * i))*0.1f);
        toadd.push_back(0.0f);


    }
    
    
    


    for (float f : toadd)
    {
        verts.push_back(f);     
    }
}




// Box implementation
Box::Box()
{
    // Optionally do something with x
}

void Box::draw(std::vector<float> &verts, RECT &rect)
{
    float screenWidth = float(rect.right-rect.left);
    float screenHeight = float(rect.bottom-rect.top);

    float pxWidth = 100.0f;
    float ndcSize = pxWidth / (screenWidth / 2.0f); // size in NDC

    // Convert pixel position to NDC
    float centerX = (2.0f * posX / screenWidth) - 1.0f;
    float centerY = 1.0f - (2.0f * posY / screenHeight);

    // Now create triangle vertices relative to center
    float x1 = centerX - ndcSize / 2.0f;
    float y1 = centerY + ndcSize / 2.0f;

    float x2 = centerX + ndcSize / 2.0f;
    float y2 = centerY + ndcSize / 2.0f;

    float x3 = centerX + ndcSize / 2.0f;
    float y3 = centerY - ndcSize / 2.0f;

    float x4 = centerX - ndcSize / 2.0f;
    float y4 = centerY - ndcSize / 2.0f;

    float toadd[] = {
        x1, y1, 0.0f,
        x2, y2, 0.0f,
        x3, y3, 0.0f,

         x1, y1, 0.0f,
         x4, y4, 0.0f,
         x3, y3, 0.0f
    };


    for (float f : toadd)
    {
        verts.push_back(f);     
    }
    
    
}
