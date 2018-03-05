#include"ocean.h"
#include"main.h"

Ocean::Ocean(color_t color){
    current = 0.02;
    position.x = 0.0;
    position.z = 0.0;
    position.y = 0.0;
    static const GLfloat ocean[] = {
        300.0, 0.0, 300.0,
        -300.0, 0.0, -300.0,
        300.0, 0.0, -300.0,

        300.0, 0.0, 300.0,
        -300.0, 0.0, 300.0,
        -300.0, 0.0, -300.0
    };
    this->ocean = create3DObject(GL_TRIANGLES, 6, ocean, color, GL_FILL);
}

void Ocean::draw(glm::mat4 VP){
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);
    Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;   
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->ocean);
}

void Ocean::tick(){
    position.y += current;
    if(this->position.y >= 1.0){
        position.y = 1.0;
        current = -current;
    }
    else if(this->position.y <= 0.0){
        position.y = 0.0;
        current = -current;
    }
}