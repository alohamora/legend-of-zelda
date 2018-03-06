#include"main.h"
#include"fireball.h"

Fireball::Fireball(color_t color){
    position = glm::vec3(0,-1,0);
    speed = 0.8;
    speed_up = 0;
    acc_y = 0;
    static const GLfloat vertex_buffer_data[] = {
        -0.5,-0.5,-0.5, // triangle 1 : begin
        -0.5,-0.5, 0.5,
        -0.5, 0.5, 0.5, // triangle 1 : end
        
        0.5, 0.5,-0.5, // triangle 2 : begin
        -0.5,-0.5,-0.5,
        -0.5, 0.5,-0.5, // triangle 2 : end
        
        0.5,-0.5, 0.5,
        -0.5,-0.5,-0.5,
        0.5,-0.5,-0.5,
        
        0.5, 0.5,-0.5,
        0.5,-0.5,-0.5,
        -0.5,-0.5,-0.5,
        
        -0.5,-0.5,-0.5,
        -0.5, 0.5, 0.5,
        -0.5, 0.5,-0.5,
        
        0.5,-0.5, 0.5,
        -0.5,-0.5, 0.5,
        -0.5,-0.5,-0.5,
        
        -0.5, 0.5, 0.5,
        -0.5,-0.5, 0.5,
        0.5,-0.5, 0.5,
        
        0.5, 0.5, 0.5,
        0.5,-0.5,-0.5,
        0.5, 0.5,-0.5,
        
        0.5,-0.5,-0.5,
        0.5, 0.5, 0.5,
        0.5,-0.5, 0.5,
        
        0.5, 0.5, 0.5,
        0.5, 0.5,-0.5,
        -0.5, 0.5,-0.5,
        
        0.5, 0.5, 0.5,
        -0.5, 0.5,-0.5,
        -0.5, 0.5, 0.5,
        
        0.5, 0.5, 0.5,
        -0.5, 0.5, 0.5,
        0.5,-0.5, 0.5      
    };
    this->fireball = create3DObject(GL_TRIANGLES, 36, vertex_buffer_data, color, GL_FILL);
}

void Fireball::draw(glm::mat4 VP){
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);
    Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;   
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->fireball);
}

void Fireball::tick() {
    this->position.x += speed*sin((rotation*M_PI)/180.0);
    this->position.z += speed*cos((rotation*M_PI)/180.0);
    this->position.y += speed_up;
    speed_up += acc_y;
    if(position.y < 0)  flag = 0;
}

void Fireball::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}