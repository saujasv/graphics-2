#include "display.h"
#include "main.h"

#define N 10

SpeedBar::SpeedBar(float x, float y, float speed) {
    this->position = glm::vec3(x, y, 0);
    this->speed = speed;
    static const GLfloat vertex_buffer_data[] = {
        -0.25, -0.25, 0.0,
        -0.25, 0.25, 0.0,
        0.25, 0.25, 0.0,
        -0.25, -0.25, 0.0,
        0.25, -0.25, 0.0,
        0.25, 0.25, 0.0
    };

    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, COLOR_BLUE, GL_FILL);
}

void SpeedBar::draw(glm::mat4 VP) {
    Matrices2.model = glm::mat4(1.0f);
    this->position.x = this->speed * 3 / 2 - 3;
    glm::mat4 translate = glm::translate(this->position);
    glm::mat4 scale = glm::scale(glm::vec3(this->speed * 3, 1.0, 1.0));
    Matrices2.model *= translate * scale;
    glm::mat4 MVP = VP * Matrices2.model;
    glUniformMatrix4fv(Matrices2.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

FuelBar::FuelBar(float x, float y, float fuel) {
    this->position = glm::vec3(x, y, 0);
    this->fuel = fuel;
    static const GLfloat vertex_buffer_data[] = {
        -0.25, -0.25, 0.0,
        -0.25, 0.25, 0.0,
        0.25, 0.25, 0.0,
        -0.25, -0.25, 0.0,
        0.25, -0.25, 0.0,
        0.25, 0.25, 0.0
    };

    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, COLOR_RED, GL_FILL);
}

void FuelBar::draw(glm::mat4 VP) {
    Matrices2.model = glm::mat4(1.0f);
    this->position.x = this->fuel * 3 / 2 - 3;
    glm::mat4 translate = glm::translate(this->position);
    glm::mat4 scale = glm::scale(glm::vec3(this->fuel * 3, 1.0, 1.0));
    Matrices2.model *= translate * scale;
    glm::mat4 MVP = VP * Matrices2.model;
    glUniformMatrix4fv(Matrices2.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

AltBar::AltBar(float x, float y, float alt) {
    this->position = glm::vec3(x, y, 0);
    this->alt = alt;
    static const GLfloat vertex_buffer_data[] = {
        -0.25, -0.25, 0.0,
        -0.25, 0.25, 0.0,
        0.25, 0.25, 0.0,
        -0.25, -0.25, 0.0,
        0.25, -0.25, 0.0,
        0.25, 0.25, 0.0
    };

    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, COLOR_GREEN, GL_FILL);
}

void AltBar::draw(glm::mat4 VP) {
    Matrices2.model = glm::mat4(1.0f);
    this->position.y = this->alt / 200.0 - 3;
    glm::mat4 translate = glm::translate(this->position);
    glm::mat4 scale = glm::scale(glm::vec3(1.0, this->alt / 100.0, 1.0));
    Matrices2.model *= translate * scale;
    glm::mat4 MVP = VP * Matrices2.model;
    glUniformMatrix4fv(Matrices2.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

Display::Display(float speed, float alt, float fuel) {
    this->position = glm::vec3(0, 0, 0);
    this->rotation = 0;
    this->fuel = FuelBar(-3, -3, fuel);
    this->speed = SpeedBar(-3, 3, speed);
    this->alt = AltBar(3, -3, alt);
}

void Display::draw(glm::mat4 VP) {
    this->fuel.draw(VP);
    this->speed.draw(VP);
    this->alt.draw(VP);
}

void Display::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Display::tick() {
    // this->position.x += this->velocity.x;
    // this->position.y += this->velocity.y;
    // this->position.z += this->velocity.z;

    // this->velocity.y -= GRAVITY;
}

