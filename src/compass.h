#include "main.h"

#ifndef COMPASS_H
#define COMPASS_H

class Compass {
public:
    Compass() {}
    Compass(float x, float y);
    // float yaw, pitch, roll;
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP, glm::vec4 plane_dir);
    // void set_position(float x, float y);
    double speed;
private:
    VAO *object;
};

#endif