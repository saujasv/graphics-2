#include "main.h"

#ifndef RINGS_H
#define RINGS_H


class Ring {
public:
    Ring() {}
    Ring(float x, float y, float z);
    glm::vec3 position;
    float rotation;
    bool claimed;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
private:
    VAO *object;
};

#endif // BALL_H
