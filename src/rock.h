#include"main.h"
#ifndef ROCK_H
#define ROCK_H


class Rock {
public:
    Rock() {}
    Rock(float x, float z, color_t color);
    void draw(glm::mat4 VP);
    glm::vec3 position;
private:
    VAO *rock;
};

#endif