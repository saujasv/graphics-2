#include "compass.h"
#include "main.h"

#define N 10

Compass::Compass(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    static const GLfloat vertex_buffer_data[] = {
        -0.5, 0.0, 0.0,
        0.5, 0.0, 0.0,
        0.0, 0.5, 0.0
    };

    this->object = create3DObject(GL_TRIANGLES, 1*3, vertex_buffer_data, COLOR_RED, GL_FILL);
}

void Compass::draw(glm::mat4 VP, glm::vec4 plane_dir) {
    Matrices2.model = glm::mat4(1.0f);
    glm::vec3 v = glm::vec3(-plane_dir.x, plane_dir.z, 0);
    glm::mat4 rotate = glm::mat4(glm::vec4(glm::cross(v, glm::vec3(0, 0, 1)), 0.0),
                                glm::vec4(v, 0.0),
                                glm::vec4(0, 0, 1, 0.0),
                                glm::vec4(0, 0, 0, 1));
    //glm::rotate(glm::angle(v, glm::vec2(0, 1)), glm::vec3(0, 0, 1));
    glm::mat4 translate = glm::translate(this->position);
    // glm::mat4 scale = glm::scale(glm::vec3(this->speed * 3, 1.0, 1.0));
    Matrices2.model *= translate * rotate;
    glm::mat4 MVP = VP * Matrices2.model;
    glUniformMatrix4fv(Matrices2.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}