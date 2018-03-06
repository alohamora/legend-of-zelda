#include"cannon.h"
#include"main.h"

Cannon::Cannon(color_t color){
    static const GLfloat vertex_buffer_data[] = {
        -0.5, 1, 8.5,
        0.5, 1, 8.5,
        -0.5, 4, 11,

        -0.5, 4, 11,
        0.5, 1, 8.5,
        0.5, 4, 11,

        -0.5, 1.25, 8.5,
        0.5, 1.25, 8.5,
        -0.5, 4.25, 11,

        -0.5, 4.25, 11,
        0.5, 1.25, 8.5,
        0.5, 4.25, 11,

        0.5, 1, 8.5,
        0.5, 4, 11,
        0.5, 1.25, 8.5,

        0.5, 1.25, 8.5,
        0.5, 4.25, 11,
        0.5, 4, 11,

        -0.5, 1, 8.5,
        -0.5, 4, 11,
        -0.5, 1.25, 8.5,

        -0.5, 1.25, 8.5,
        -0.5, 4.25, 11,
        -0.5, 4, 11,
    };
    this->cannon = create3DObject(GL_TRIANGLES, 24, vertex_buffer_data, color, GL_FILL);
}

void Cannon::draw() {
    draw3DObject(this->cannon);
}