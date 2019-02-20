#include <vector>
#include <utility>
#include "main.h"

#ifndef BALL_H
#define BALL_H


class Plane {
public:
    Plane() {}
    Plane(float x, float y, color_t color);
    float yaw, pitch, roll;
    glm::vec3 position;
    glm::vec4 x_axis, y_axis, z_axis;
    std::vector< std::pair<glm::vec4, float> > spheres;
    float rotation;
    float fuel;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    void tick_input(int a, int s, int d, int q, int w, int e, int space, int b);
    double speed;
private:
    VAO *body, *nose, *tail_cone, *wings, *fins, *tail;
    VAO *engines[4];
};

#endif // BALL_H
