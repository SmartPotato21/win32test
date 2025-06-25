#pragma once
#include <string>
#include <vector>
#include <windows.h>
class Object
{
public:
    Object();

    std::string name;
    float posX = 0.0f;
    float posY = 0.0f;
    float scale = 1.0f;
    float rounded = 0.0f;
    virtual void draw(std::vector<float> &verts, RECT &rect);
    std::string getName();
};

class Circle : public Object
{
public:
    Circle();
    virtual void draw(std::vector<float> &verts, RECT &rect) override;

};

class Box : public Object
{
public: 
    Box();
    virtual void draw(std::vector<float> &verts, RECT &rect) override;
};
