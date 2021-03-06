#include "main.h"
#include "timer.h"
#include "boat.h"
#include"background.h"
#include"ocean.h"
#include"rock.h"
#include"cannon.h"
#include"fireball.h"
using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Boat boat;
Cannon cannon;
Background background;
Ocean ocean;
Fireball fireball;
Rock rocks[100];
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
int v_count;
Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    // glm::vec3 eye ( 30*sin(camera_rotation_angle*M_PI/180.0f), 10, 30*cos(camera_rotation_angle*M_PI/180.0f) );
    glm::vec3 eye,target,up;
    if(v_count == 0){
        eye  = glm::vec3(boat.position.x, 4+boat.position.y, boat.position.z);
        target = glm::vec3(boat.position.x + 10*sin((boat.rotation*M_PI)/180.0),4+boat.position.y,boat.position.z + 10*cos((boat.rotation*M_PI)/180.0));
        up = glm::vec3(0, 1, 0);
    }
    else if(v_count == 1){
        eye  = glm::vec3(boat.position.x - 20*sin((boat.rotation*M_PI)/180.0), 6, boat.position.z - 20*cos((boat.rotation*M_PI)/180.0));
        target = glm::vec3(boat.position.x ,6,boat.position.z);
        up = glm::vec3(0, 1, 0);        
    }
    else if(v_count == 2){
        eye = glm::vec3(boat.position.x, 100, boat.position.z);
        target = glm::vec3(boat.position.x, 0, boat.position.z);
        up = glm::vec3(0,0,1);
    }
    else{
        eye = glm::vec3(10, 50, 0);
        // Target - Where is the camera looking at.  Don't change unless you are sure!!
        target = glm::vec3(boat.position.x, 0, boat.position.z);
        // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
        up = glm::vec3(0, 1, 0);
    }

    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model
    background.draw(VP);
    ocean.draw(VP);
    fireball.draw(VP);
    // Scene render
    for(int i=0;i<100;i++)  rocks[i].draw(VP);
    boat.draw(VP);
    cannon.draw();
    // Compute Camera matrix (view)
}   

void tick_input(GLFWwindow *window) {
    int x,y,z;
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int space = glfwGetKey(window, GLFW_KEY_SPACE);
    int view1 = glfwGetKey(window, GLFW_KEY_1);
    int view2 = glfwGetKey(window, GLFW_KEY_2);
    int view3 = glfwGetKey(window, GLFW_KEY_3);
    int view4 = glfwGetKey(window, GLFW_KEY_4);
    int view5 = glfwGetKey(window, GLFW_KEY_5);
    int f = glfwGetKey(window, GLFW_KEY_F);
    if (left) {
        boat.rotation += 2;
    }
    else if (right) {
        boat.rotation -= 2;
    }
    else if(up){
        boat.speed = 0.3;
    }
    else if(down) {
        boat.speed = -0.3;
    }
    else{
        boat.speed  = 0;
    }

    if (space && boat.flag_jump == 0) {
        boat.speed_up = 0.5;
        boat.acc_y = -0.03;
        boat.flag_jump = 1;
    }

    if(f && fireball.flag == 0){
        fireball.set_position(boat.position.x + 11*sin((boat.rotation*M_PI)/180.0),4.2,boat.position.z + 11*cos((boat.rotation*M_PI)/180.0));
        fireball.rotation = boat.rotation;
        fireball.speed_up = 0.8;
        fireball.acc_y = -0.03;
        fireball.flag = 1;
    }
    
    if(view1){
        v_count = 0;
    }
    else if(view2){
        v_count = 1;
    }
    else if(view3){
        v_count = 2;
    }
    else if(view4){
        v_count = 3;
    }
    else if(view5){
        v_count = 4;
    }

    if(boat.flag_jump==0){
        boat.position.y = ocean.position.y + 0.02;
        boat.current = ocean.current;
        boat.acc_y = 0;
        boat.speed_up = 0;
    }

}
void detect_collision(int i){
    float a,b,angle,dis;
    a = boat.position.x - rocks[i].position.x;
    b = boat.position.z - rocks[i].position.z;
    angle = atan(a/b);
    angle -= boat.rotation;
    angle = (angle*M_PI)/180.0;
    dis = sqrt((a*a) + (b*b));
    if(fabs(dis*cos(angle)) < 7.0  && fabs(dis*sin(angle)) < 3.0){
        rocks[i].position.y = -10;
    }
}

void tick_elements() {
    for(int i=0;i<100;i++){
        detect_collision(i);
    }
    boat.tick();
    ocean.tick();
    fireball.tick();
    camera_rotation_angle = 0;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    int x,z;
    boat = Boat(0, 0, COLOR_RED);
    cannon = Cannon(CANNON);
    background = Background(COLOR_BACKGROUND);
    ocean = Ocean(COLOR_BLUE);
    fireball = Fireball(FIREBALL);
    for(int i=0;i<100;i++){
        x = rand()%581 + 20;
        z = rand()%581 + 20;        
        rocks[i] = Rock(x,z,COLOR_RED);
    }
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 600;
    int height = 600;
    v_count = 0;
    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen() {
    float top    = screen_center_y + 20 / screen_zoom;
    float bottom = screen_center_y - 20 / screen_zoom;
    float left   = screen_center_x - 20 / screen_zoom;
    float right  = screen_center_x + 20 / screen_zoom;
    Matrices.projection = glm::perspective(1.0f, 1.0f, 1.0f, 500.0f);
    // Matrices.projection = glm::perspective(1.0f, 1.0f, 0.1f, 500.0f);
}
