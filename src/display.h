#include "main.h"

#ifndef DISPLAY_H
#define DISPLAY_H

class FuelBar {
public:
    FuelBar() {}
    FuelBar(float x, float y, float fuel);
    // float yaw, pitch, roll;
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    // void set_position(float x, float y);
    double fuel;
private:
    VAO *object;
};

class AltBar {
public:
    AltBar() {}
    AltBar(float x, float y, float alt);
    // float yaw, pitch, roll;
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    // void set_position(float x, float y);
    double alt;
private:
    VAO *object;
};

class SpeedBar {
public:
    SpeedBar() {}
    SpeedBar(float x, float y, float speed);
    // float yaw, pitch, roll;
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    // void set_position(float x, float y);
    double speed;
private:
    VAO *object;
};

class Display {
public:
    Display() {}
    Display(float speed, float alt, float fuel);
    // float yaw, pitch, roll;
    glm::vec3 position;
    FuelBar fuel;
    AltBar alt;
    SpeedBar speed;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
private:
    VAO *object;
};

#endif // BALL_H
