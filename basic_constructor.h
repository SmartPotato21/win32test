#pragma once
#include <string>

class Object
{
public:
    Object();

    std::string name;
    float posX = 0.0f;
    float posY = 0.0f;
    float scale = 0.0f;
    virtual void draw();
    std::string getName();
};

class Box : public Object
{
public: 
    Box(int x);
    virtual void draw() override;
};
