#include "main.h"

#ifndef BOAT_H
#define BOAT_H


class Boat {
public:
    Boat() {}
    Boat(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    float speed;
    float current;
    float acc_y;
    int flag_jump;
    float speed_up;
private:
    VAO *base;
    VAO *sides;
    VAO *front_back;
    VAO *pole;
    VAO *sail;
};

#endif // BALL_H
