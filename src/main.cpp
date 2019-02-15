#include "main.h"
#include "timer.h"
#include "ball.h"
#include "sea.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Ball ball1;
Sea s;
int cam = 0;
int ticks_since_view_change = 0;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;

Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    ticks_since_view_change++;

    glm::vec3 eye, target;
    if (cam == 0) // Plane view
    {
        eye = glm::vec3(ball1.position.x + 0, ball1.position.y + 0, ball1.position.z - 1);
        target = glm::vec3(ball1.position.x + 0, ball1.position.y + 0, ball1.position.z - 2);
    }
    else if (cam == 1) // Top view
    {
        eye = glm::vec3(ball1.position.x + 0, ball1.position.y + 6, ball1.position.z + 0.001);
        target = glm::vec3(ball1.position.x + 0, ball1.position.y + 0, ball1.position.z + 0);
    }
    else if (cam == 2) // Tower view
    {
        eye = glm::vec3(ball1.position.x + 3, ball1.position.y + 3, ball1.position.z + 3);
        target = glm::vec3(ball1.position.x + 0, ball1.position.y + 0, ball1.position.z + 0);
    }
    else if (cam == 3) // Follow cam
    {
        eye = glm::vec3(ball1.position.x + 0, ball1.position.y + 2, ball1.position.z + 3);
        target = glm::vec3(ball1.position.x + 0, ball1.position.y + 0, ball1.position.z + 0);
    }

    glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    // if (cam)
    //     Matrices.view = glm::lookAt(glm::vec3(5, 5, 5), glm::vec3(0, 0, 0), up );
    // else
    //     Matrices.view = glm::lookAt(glm::vec3(0, 0, 0), glm::vec3(0, 0, 1), up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    Matrices.view = glm::lookAt(eye, target, up); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    ball1.draw(VP);
    s.draw(VP);
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int v = glfwGetKey(window, GLFW_KEY_V);
    if (v && ticks_since_view_change >= 20) {
        cam = (cam + 1) % 4;
        ticks_since_view_change = 0;
    }
}

void tick_elements() {
    ball1.tick();
    camera_rotation_angle += 1;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    ball1 = Ball(0, 0, COLOR_BLACK);
    s = Sea(0, 0);

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
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::perspective(
        glm::radians(90.0f), // The vertical Field of View, in radians: the amount of "zoom". Think "camera lens". Usually between 90° (extra wide) and 30° (quite zoomed in)
        4.0f / 3.0f,       // Aspect Ratio. Depends on the size of your window. Notice that 4/3 == 800/600 == 1280/960, sounds familiar ?
        0.1f,              // Near clipping plane. Keep as big as possible, or you'll get precision issues.
        100.0f             // Far clipping plane. Keep as little as possible.
    );
}
