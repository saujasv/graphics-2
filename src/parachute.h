#include "main.h"

#ifndef CHUTES_H
#define CHUTES_H


class Parachute {
public:
    Parachute() {}
    Parachute(float x, float y, float z);
    glm::vec3 position, velocity;
    float rotation;
    bool claimed;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
private:
    VAO *object;
};

#endif // BALL_H
