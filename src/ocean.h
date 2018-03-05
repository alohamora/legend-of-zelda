#include"main.h"
#ifndef OCEAN_H
#define OCEAN_H


class Ocean {
public:
    Ocean() {}
    Ocean(color_t color);
    void draw(glm::mat4 VP);
    void tick();
    float current;
    glm::vec3 position;
private:
    VAO *ocean;
};

#endif