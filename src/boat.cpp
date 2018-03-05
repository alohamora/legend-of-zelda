#include "boat.h"
#include "main.h"

Boat::Boat(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0;
    current = 0.02;
    speed_up = 0;
    flag_jump = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat base[] = {
       -2.0, 0.0, -6.0,
       -2.0, 0.0, 6.0,
       2.0, 0.0, 6.0,
       
       2.0, 0.0, 6.0,
       -2.0, 0.0, -6.0,
       2.0, 0.0, -6.0,
       
       -2.0, 0.0, -6.0,
       2.0, 0.0, -6.0,
       0.0, 0.0, -8.0,

       -2.0, 0.0, 6.0,
       2.0, 0.0, 6.0,
       0.0, 0.0, 8.0,
    };

    static const GLfloat sides[] ={
       -2.0, 0.0, -6.0,
       -2.0, 0.0, 6.0,
       -3.0, 2.0, 6.0, 

       -3.0, 2.0, 6.0, 
       -2.0, 0.0, -6.0,
       -3.0, 2.0, -6.0,

       2.0, 0.0, -6.0,
       2.0, 0.0, 6.0,
       3.0, 2.0, 6.0, 

       3.0, 2.0, 6.0, 
       2.0, 0.0, -6.0,
       3.0, 2.0, -6.0,
    };

    static const GLfloat front_back[] = {
        -2.0, 0.0, 6.0,
        0.0, 0.0, 8.0,
        0.0 ,2.0, 9.0,

        2.0, 0.0, 6.0,
        0.0, 0.0, 8.0,
        0.0 ,2.0, 9.0,
        
        -2.0, 0.0, 6.0,
        -3.0, 2.0, 6.0,
        0.0, 2.0, 9.0,
 
        2.0, 0.0, 6.0,
        3.0, 2.0, 6.0,
        0.0, 2.0, 9.0,        

        -2.0, 0.0, -6.0,
        0.0, 0.0, -8.0,
        0.0 ,2.0, -9.0,

        2.0, 0.0, -6.0,
        0.0, 0.0, -8.0,
        0.0 ,2.0, -9.0,
        
        -2.0, 0.0, -6.0,
        -3.0, 2.0, -6.0,
        0.0, 2.0, -9.0,
 
        2.0, 0.0, -6.0,
        3.0, 2.0, -6.0,
        0.0, 2.0, -9.0        
    };
    static const GLfloat pole[] = {
        0.2, 0.0, 0.2,
        -0.2, 0.0, 0.2,
        0.2, 7.0, 0.2,

        0.2, 7.0, 0.2,
        -0.2, 7.0, 0.2,
        -0.2, 0.0, 0.2,

        0.2, 0.0, -0.2,
        -0.2, 0.0, -0.2,
        0.2, 7.0, -0.2,

        0.2, 7.0, -0.2,
        -0.2, 7.0, -0.2,
        -0.2, 0.0, -0.2,

        0.2, 0.0, 0.2,
        0.2, 0.0, -0.2,
        0.2, 7.0, 0.2,

        0.2, 7.0, -0.2,
        0.2, 7.0, 0.2,
        0.2, 0.0, -0.2,

        -0.2, 0.0, 0.2,
        -0.2, 0.0, -0.2,
        -0.2, 7.0, 0.2,

        -0.2, 7.0, -0.2,
        -0.2, 7.0, 0.2,
        -0.2, 0.0, -0.2,

        0.2, 7.0, 0.2,
        0.2, 7.0, -0.2
        -0.2, 7.0, 0.2,

        0.2, 7.0, -0.2,
        -0.2, 7.0, -0.2,
        -0.2, 7.0, 0.2,

    };

    static const GLfloat sail[] = {
        0.2, 3.0, 0.0,
        0.2, 7.0, 0.0,
        3.0, 3.0, 0.0
    };
    this->base = create3DObject(GL_TRIANGLES, 12, base, COLOR_YELLOW, GL_FILL);
    this->sides = create3DObject(GL_TRIANGLES, 12, sides, COLOR_BROWN, GL_FILL);
    this->front_back = create3DObject(GL_TRIANGLES, 24, front_back, COLOR_BROWN, GL_FILL);
    this->pole = create3DObject(GL_TRIANGLES,24, pole, COLOR_BROWN, GL_FILL);
    this->sail  = create3DObject(GL_TRIANGLES, 6, sail, COLOR_YELLOW, GL_FILL);
}

void Boat::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->base);
    draw3DObject(this->sides);
    draw3DObject(this->front_back);
    draw3DObject(this->pole);
    draw3DObject(this->sail);
}

void Boat::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Boat::tick() {
    this->position.x += speed*sin((rotation*M_PI)/180.0);
    this->position.z += speed*cos((rotation*M_PI)/180.0);
    this->position.y += current + speed_up;
    speed_up += acc_y;
    if(this->position.y >= 1.0 && flag_jump == 0){
        position.y = 1.0;
        current = -current;
    }
    else if(this->position.y <= 0.0){
        position.y = 0.0;
        current = -current;
        acc_y = 0;
        speed_up = 0;
        flag_jump = 0;
    } 
}

