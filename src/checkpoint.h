#include "main.h"

#ifndef CHECKPOINT_H
#define CHECKPOINT_H

class Arrow {
public:
    Arrow() {}
    Arrow(float x, float y, float z);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
private:
    VAO *object;
};

class Cannon {
public:
    Cannon() {}
    Cannon(float x, float y, float z);
    glm::vec3 position;
    glm::vec4 x_axis, y_axis, z_axis;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(glm::vec3 plane_pos);
private:
    VAO *cyl, *front, *back;
};

class Checkpoint {
public:
    Checkpoint() {}
    Checkpoint(float x, float z);
    glm::vec3 position;
    float rotation;
    int life;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(glm::vec3 plane_pos);
    double speed;
    Cannon cannon;
    Arrow arrow;
private:
    VAO *base, *top;
};

#endif // BALL_H
