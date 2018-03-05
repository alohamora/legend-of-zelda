#include"main.h"
#ifndef BACKGROUND_H
#define BACKGROUND_H


class Background {
public:
    Background() {}
    Background(color_t color);
    void draw(glm::mat4 VP);
private:
    VAO *background;
};

#endif
