#include <utility>

#include "main.h"

#ifndef MISSILE_H
#define MISSILE_H


class Missile {
public:
    Missile() {}
    Missile(glm::vec3 pos, glm::vec3 dir, float speed);
    float yaw, pitch, roll;
    glm::vec3 position;
    bool hit;
    glm::vec3 velocity;
    std::pair<glm::vec4, float> sphere;
    glm::vec4 x_axis, y_axis, z_axis;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *body, *nose, *trail;
};

#endif // BALL_H
