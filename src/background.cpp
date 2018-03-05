#include"background.h"
#include"main.h"

Background::Background(color_t color){
    static const GLfloat background[] = {
        -300.0f,-300.0f,-300.0f, // triangle 1 : begin
        -300.0f,-300.0f, 300.0f,
        -300.0f, 300.0f, 300.0f, // triangle 1 : end
        
        300.0f, 300.0f,-300.0f, // triangle 2 : begin
        -300.0f,-300.0f,-300.0f,
        -300.0f, 300.0f,-300.0f, // triangle 2 : end
        
        300.0f,-300.0f, 300.0f,
        -300.0f,-300.0f,-300.0f,
        300.0f,-300.0f,-300.0f,
        
        300.0f, 300.0f,-300.0f,
        300.0f,-300.0f,-300.0f,
        -300.0f,-300.0f,-300.0f,
        
        -300.0f,-300.0f,-300.0f,
        -300.0f, 300.0f, 300.0f,
        -300.0f, 300.0f,-300.0f,
        
        300.0f,-300.0f, 300.0f,
        -300.0f,-300.0f, 300.0f,
        -300.0f,-300.0f,-300.0f,
        
        -300.0f, 300.0f, 300.0f,
        -300.0f,-300.0f, 300.0f,
        300.0f,-300.0f, 300.0f,
        
        300.0f, 300.0f, 300.0f,
        300.0f,-300.0f,-300.0f,
        300.0f, 300.0f,-300.0f,
        
        300.0f,-300.0f,-300.0f,
        300.0f, 300.0f, 300.0f,
        300.0f,-300.0f, 300.0f,
        
        300.0f, 300.0f, 300.0f,
        300.0f, 300.0f,-300.0f,
        -300.0f, 300.0f,-300.0f,
        
        300.0f, 300.0f, 300.0f,
        -300.0f, 300.0f,-300.0f,
        -300.0f, 300.0f, 300.0f,
        
        300.0f, 300.0f, 300.0f,
        -300.0f, 300.0f, 300.0f,
        300.0f,-300.0f, 300.0f
    };
    this->background = create3DObject(GL_TRIANGLES, 36, background, color, GL_FILL);
}

void Background::draw(glm::mat4 VP){
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &VP[0][0]);
    draw3DObject(this->background);
}