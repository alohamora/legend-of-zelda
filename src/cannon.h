#include"main.h"
#ifndef CANNON_H
#define CANNON_H


class Cannon {
public:
    Cannon() {}
    Cannon(color_t color);
    void draw();
private:
    VAO *cannon;
};

#endif