#include "parachute.h"
#include "main.h"

#define N 100

Parachute::Parachute(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->velocity = glm::vec3(0, 0, 0);
    this->rotation = 0;
    this->claimed = false;

    static GLfloat mountain_vertex_buffer[18 * N];

    float incr = 2 * M_PI / N;

	float angle = incr;
	GLfloat last_row[] = {20.0f, 0.0f, 0.0f};
	GLfloat curr_row[3];

	for (int i = 0; i < N; i++)
	{
		curr_row[0] = 20.0f * cos(angle);
		curr_row[1] = 0.0f;
		curr_row[2] = 20.0f * sin(angle);

		mountain_vertex_buffer[18 * i] = last_row[0];
		mountain_vertex_buffer[18 * i + 1] = last_row[1] + 10.0;
		mountain_vertex_buffer[18 * i + 2] = last_row[2];

		mountain_vertex_buffer[18 * i + 3] = curr_row[0];
		mountain_vertex_buffer[18 * i + 4] = last_row[1] + 10.0;
		mountain_vertex_buffer[18 * i + 5] = curr_row[2];

		mountain_vertex_buffer[18 * i + 6] = 0.5 * curr_row[0];
		mountain_vertex_buffer[18 * i + 7] = last_row[1] - 10.0;
		mountain_vertex_buffer[18 * i + 8] = 0.5 * curr_row[2];

        mountain_vertex_buffer[18 * i + 9] = last_row[0];
		mountain_vertex_buffer[18 * i + 10] = last_row[1] + 10.0;
		mountain_vertex_buffer[18 * i + 11] = last_row[2];

		mountain_vertex_buffer[18 * i + 12] = 0.5 * last_row[0];
		mountain_vertex_buffer[18 * i + 13] = last_row[1] - 10.0;
		mountain_vertex_buffer[18 * i + 14] = 0.5 * last_row[2];

		mountain_vertex_buffer[18 * i + 15] = 0.5 * curr_row[0];
		mountain_vertex_buffer[18 * i + 16] = last_row[1] - 10.0;
		mountain_vertex_buffer[18 * i + 17] = 0.5 * curr_row[2];

		last_row[0] = curr_row[0];
		last_row[1] = curr_row[1];
		last_row[2] = curr_row[2];
		angle += incr;
	}

    this->object = create3DObject(GL_TRIANGLES, 6 * N, mountain_vertex_buffer, COLOR_YELLOW, GL_FILL);
}

void Parachute::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    // glm::mat4 rotate = glm::rotate(this->rotation, glm::vec3(0, 1, 0));
    glm::mat4 translate = glm::translate(this->position);    // glTranslatef
    // glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    if (!claimed) {
        draw3DObject(this->object);
    }
}

void Parachute::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

// void Parachute::tick_input(int a, int s, int d, int q, int w, int e, int space, int b) {
//     yaw = (a - d) * 0.01;
//     pitch = (w - s) * 0.01;
//     roll = (q - e) * 0.01;
//     speed += (space - b) * 0.05;
// }

void Parachute::tick() {
    this->velocity.y -= 2 * GRAVITY;
    this->position.y += this->velocity.y;
}

