#include <vector>

#include "main.h"
#include "timer.h"
#include "plane.h"
#include "sea.h"
#include "missile.h"
#include "display.h"
#include "volcano.h"
#include "checkpoint.h"
#include "bomb.h"
#include "rings.h"
#include "topup.h"
#include "parachute.h"
#include "compass.h"

using namespace std;

GLMatrices Matrices, Matrices2;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Plane plane;
Sea s;
vector<Missile> missiles;
vector<Missile> plane_missiles;
vector<Bomb> bombs;
Display disp;
vector<Volcano> volcanoes;
vector<Checkpoint> chkpts;
vector<Ring> rings;
vector<TopUp> topups;
vector<Parachute> chutes;
Compass compass;

int curr_chk = 0;

int cam = 3;
int points = 0;
int ticks_since_view_change = 0;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
bool mouse_pressed;

glm::vec4 helicopter;
double xpos, ypos, oldx, oldy, Y = 0.001, P = 0.0001, L = 1.0;

Timer t60(1.0 / 60);

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    L = fmax(L + yoffset * 0.1, 1.0);
}

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    ticks_since_view_change++;

    glm::vec3 eye, target, up;
    glm::vec4 look = glm::normalize(plane.z_axis);
    glm::vec4 vert = glm::normalize(plane.y_axis);
    glm::vec4 hor = glm::normalize(plane.x_axis);
    if (cam == 0) // Plane view
    {
        eye = glm::vec3(plane.position.x + look.x * -3.5, plane.position.y + look.y * -3.5, plane.position.z + look.z * -3.5);
        target = glm::vec3(plane.position.x + look.x * -5, plane.position.y + look.y * -5, plane.position.z + look.z * -5);
        up = glm::vec3(vert);
    }
    else if (cam == 1) // Top view
    {
        eye = glm::vec3(plane.position.x + 0, plane.position.y + 20, plane.position.z + 0.001);
        target = glm::vec3(plane.position.x + 0, plane.position.y + 0, plane.position.z + 0);
        up = glm::vec3(0, 1, 0);
    }
    else if (cam == 2) // Tower view
    {
        eye = glm::vec3(plane.position.x + 3, plane.position.y + 3, plane.position.z + 3);
        target = glm::vec3(plane.position.x + 0, plane.position.y + 0, plane.position.z + 0);
        up = glm::vec3(0, 1, 0);
    }
    else if (cam == 3) // Follow cam
    {
        eye = glm::vec3(plane.position.x + look.x * 3 + vert.x * 2.5, plane.position.y + look.y * 3 + vert.y * 2.5, plane.position.z + look.z * 3 + vert.z * 2.5);
        target = glm::vec3(plane.position.x, plane.position.y, plane.position.z);
        up = glm::vec3(vert);
    }
    else if (cam == 4)
    {
        glfwGetCursorPos(window, &xpos, &ypos);

        if (mouse_pressed) {
            Y += (xpos - oldx) * 0.005;
            P += (ypos - oldy) * 0.005;

            helicopter = glm::vec4(6.0, 0.0001, 0.0001, 0.0);
            glm::vec3 euler(0.0, Y, P);
            glm::quat q = glm::quat(euler);
            glm::mat4 rot = glm::toMat4(q);
            glm::mat4 scale = glm::scale(glm::vec3(L, L, L));
            helicopter = scale * rot * helicopter;
        }

        eye = glm::vec3(helicopter.x + plane.position.x, helicopter.y + plane.position.y, helicopter.z + plane.position.z);
        target = glm::vec3(plane.position.x, plane.position.y, plane.position.z);
        up = glm::vec3(0, 1, 0);
        oldx = xpos;
        oldy = ypos;
    }

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
    for (int i = 0; i < missiles.size(); i++) {
        missiles[i].draw(VP);
    }

    for (int i = 0; i < plane_missiles.size(); i++) {
        plane_missiles[i].draw(VP);
    }

    for (int i = 0; i < bombs.size(); i++) {
        bombs[i].draw(VP);
    }

    for (int i = 0; i < rings.size(); i++) {
        rings[i].draw(VP);
    }

    for (int i = 0; i < topups.size(); i++) {
        topups[i].draw(VP);
    }

    for (int i = 0; i < chutes.size(); i++) {
        chutes[i].draw(VP);
    }

    plane.draw(VP);
    s.draw(VP);
    chkpts[curr_chk].draw(VP);

    Matrices2.view = glm::lookAt(glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
    glm::mat4 VP2 = Matrices2.projection * Matrices2.view;
    disp.draw(VP2);
    compass.draw(VP2, glm::vec4(plane.z_axis.x, plane.z_axis.y, plane.z_axis.z, 0.0));
    for (int i = 0; i < volcanoes.size(); i++) {
        volcanoes[i].draw(VP);
    }
    // vol.draw(VP);
    // disp.draw(VP, eye, target, hor);
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int a = glfwGetKey(window, GLFW_KEY_A);
    int d = glfwGetKey(window, GLFW_KEY_D);
    int q = glfwGetKey(window, GLFW_KEY_Q);
    int e = glfwGetKey(window, GLFW_KEY_E);
    int v = glfwGetKey(window, GLFW_KEY_V);
    int w = glfwGetKey(window, GLFW_KEY_W);
    int s = glfwGetKey(window, GLFW_KEY_S);
    int b = glfwGetKey(window, GLFW_KEY_B);
    int enter = glfwGetKey(window, GLFW_KEY_ENTER);
    int shift = glfwGetKey(window, GLFW_KEY_T);
    int space = glfwGetKey(window, GLFW_KEY_SPACE);
    plane.tick_input(a, s, d, q, w, e, space, b);
    if (v && ticks_since_view_change >= 20) {
        cam = (cam + 1) % 5;
        ticks_since_view_change = 0;
    }

    glm::vec4 vert = glm::normalize(plane.y_axis);
    glm::vec4 look = glm::normalize(plane.z_axis);
    if (enter && ticks_since_view_change >= 20) {
        plane_missiles.push_back(Missile(glm::vec3(plane.position.x - 0.5 * vert.x, plane.position.y - 0.5 * vert.y, plane.position.z - 0.5 * vert.z), 
                                            glm::vec3(-look.x, -look.y, -look.z), plane.speed + 1.0));
        ticks_since_view_change = 0;
    }
    else if (shift && ticks_since_view_change >= 20) {
        bombs.push_back(Bomb(glm::vec3(plane.position.x - 1.0 * vert.x, plane.position.y - 1.0 * vert.y, plane.position.z - 1.0 * vert.z), 
                                            glm::vec3(-look.x, -look.y, -look.z), plane.speed));
        ticks_since_view_change = 0;
    }
}

double get_random(double min, double max) {
    return min + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(max - min)));
}

bool tick_elements() {
    plane.tick();
    chkpts[curr_chk].tick(plane.position);
    if (get_random(0, 1) < 0.001) {
        float coeff = -glm::distance(chkpts[curr_chk].position, plane.position) / 2;
        missiles.push_back(Missile(chkpts[curr_chk].cannon.position,
                                    glm::normalize(glm::vec3(plane.position.x + coeff * plane.speed * plane.z_axis.x - chkpts[curr_chk].cannon.position.x,
                                                                plane.position.y + coeff * plane.speed * plane.z_axis.y- chkpts[curr_chk].cannon.position.y,
                                                                plane.position.z + coeff * plane.speed * plane.z_axis.z - chkpts[curr_chk].cannon.position.z)),
                                    1.0));
        // cout << "FIRED" << endl;
    }

    for (int i = 0; i < volcanoes.size(); i++) {
        if (pow(volcanoes[i].position.x - plane.position.x, 2) + pow(volcanoes[i].position.z - plane.position.z, 2) < 100 * 100)
            return true;
    }

    for (int i = 0; i < missiles.size(); i++) {
        missiles[i].tick();
        if (glm::distance(glm::vec3(missiles[i].position.x + missiles[i].sphere.first.x,
                                    missiles[i].position.y + missiles[i].sphere.first.y,
                                    missiles[i].position.z + missiles[i].sphere.first.z), 
                                    plane.position) <= missiles[i].sphere.second + 4.0)
        {   
            for (int j = 0; j < plane.spheres.size(); j++) {
                if (glm::distance(plane.spheres[j].first, missiles[i].sphere.first) 
                                    <= plane.spheres[j].second + missiles[i].sphere.second) {
                                        return true;
                }
            }
        }
    }

    for (int i = 0; i < plane_missiles.size(); i++) {
        plane_missiles[i].tick();
        if (!plane_missiles[i].hit && glm::distance(glm::vec2(plane_missiles[i].position.x, plane_missiles[i].position.z), 
                            glm::vec2(chkpts[curr_chk].position.x, chkpts[curr_chk].position.z)) <= 100.0)
        {
            if (plane_missiles[i].position.y < -160) {
                chkpts[curr_chk].life--;
                plane_missiles[i].hit = true;
                points += 20;
            }
        }
        
        for (int j = 0; j < chutes.size(); j++) {
            if (!plane_missiles[i].hit && !chutes[j].claimed && glm::distance(plane_missiles[i].position, chutes[j].position) <= 10.0) {
                chutes[j].claimed = true;
                plane_missiles[i].hit = true;
                points += 50;
            }
        }
    }

    if (get_random(0, 1) < 0.001) {
        chutes.push_back(Parachute(chkpts[curr_chk].position.x + get_random(-100, 100),
                                    get_random(0, 50),
                                    chkpts[curr_chk].position.z + get_random(-100, 100)));
    }

    for (int i = 0; i < bombs.size(); i++) {
        bombs[i].tick();
        if (!bombs[i].hit && glm::distance(glm::vec2(bombs[i].position.x, bombs[i].position.z), 
                            glm::vec2(chkpts[curr_chk].position.x, chkpts[curr_chk].position.z)) <= 100.0)
        {
            if (bombs[i].position.y < -160) {
                chkpts[curr_chk].life -= 10;
                bombs[i].hit = true;
                points += 200;
            }
        }
    }

    for (int i = 0; i < rings.size(); i++) {
        if (!rings[i].claimed && glm::distance(plane.position, rings[i].position) < 10) {
            rings[i].claimed = true;
            points += 10;
        }
    }

    for (int i = 0; i < topups.size(); i++) {
        if (!topups[i].claimed && glm::distance(plane.position, topups[i].position) < 10) {
            topups[i].claimed = true;
            plane.fuel = 1.0;
        }
    }

    if (chkpts[curr_chk].life <= 0) {
        points += 10;
        curr_chk++;
    }
    
    if (curr_chk > 3)
        return true;

    if (plane.position.y < -200)
        return true;

    chkpts[curr_chk].arrow.position.y = plane.position.y;

    disp.fuel.fuel = plane.fuel;
    disp.speed.speed = plane.speed;
    disp.alt.alt = plane.position.y + 200.0;
    return false;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    plane = Plane(0, 0, COLOR_BLACK);
    s = Sea(0, 0);
    disp = Display(plane.speed, plane.position.y + 200.0, plane.fuel);
    compass = Compass(3, 3);
    // vol = Volcano(0, -200.0);
    chkpts.push_back(Checkpoint(-200.0, -750.0));
    chkpts.push_back(Checkpoint(300.0, -1500.0));
    chkpts.push_back(Checkpoint(200.0, -2250.0));
    chkpts.push_back(Checkpoint(-100.0, -3000.0));

    volcanoes.push_back(Volcano(0.0, -500.0));
    volcanoes.push_back(Volcano(0.0, -1050.0));
    volcanoes.push_back(Volcano(250.0, -1875.0));
    volcanoes.push_back(Volcano(0.0, -2000.0));
    volcanoes.push_back(Volcano(0.0, -2750.0));

    for (int i = 0; i < 10; i++) {
        rings.push_back(Ring(get_random(-300, 300), get_random(-100, 0), get_random(-3000, 0)));
    }

    for (int i = 0; i < 10; i++) {
        topups.push_back(TopUp(get_random(-300, 300), get_random(-100, 0), get_random(-3000, 0)));
    }

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");
    Matrices2.MatrixID = glGetUniformLocation(programID, "MVP");


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
    char title[100];

    window = initGLFW(width, height);
    glfwSetScrollCallback(window, scroll_callback);
    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        sprintf(title, "Score = %d", points);
        glfwSetWindowTitle(window, title);

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            if (tick_elements())
                break;
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
    // Matrices.projection = glm::perspective(
    //     glm::radians(90.0f), // The vertical Field of View, in radians: the amount of "zoom". Think "camera lens". Usually between 90° (extra wide) and 30° (quite zoomed in)
    //     4.0f / 3.0f,       // Aspect Ratio. Depends on the size of your window. Notice that 4/3 == 800/600 == 1280/960, sounds familiar ?
    //     0.1f,              // Near clipping plane. Keep as big as possible, or you'll get precision issues.
    //     100.0f             // Far clipping plane. Keep as little as possible.
    // );
    Matrices2.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
