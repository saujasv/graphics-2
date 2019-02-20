#include "volcano.h"
#include "main.h"

#define N 100

Volcano::Volcano(float x, float z) {
    this->position = glm::vec3(x, -200.0, z);
    this->rotation = 0;

    static GLfloat mountain_vertex_buffer[18 * N];
    static GLfloat g_vertex_buffer_data[10 * N];

    float incr = 2 * M_PI / N;

	float angle = incr;
	GLfloat last_row[] = {200.0f, 0.0f, 0.0f};
	GLfloat curr_row[3];

	for (int i = 0; i < N; i++)
	{
		curr_row[0] = 200.0f * cos(angle);
		curr_row[1] = 0.0f;
		curr_row[2] = 200.0f * sin(angle);

		mountain_vertex_buffer[18 * i] = last_row[0];
		mountain_vertex_buffer[18 * i + 1] = last_row[1];
		mountain_vertex_buffer[18 * i + 2] = last_row[2];

		mountain_vertex_buffer[18 * i + 3] = curr_row[0];
		mountain_vertex_buffer[18 * i + 4] = last_row[1];
		mountain_vertex_buffer[18 * i + 5] = curr_row[2];

		mountain_vertex_buffer[18 * i + 6] = 0.5 * curr_row[0];
		mountain_vertex_buffer[18 * i + 7] = last_row[1] + 100.0;
		mountain_vertex_buffer[18 * i + 8] = 0.5 * curr_row[2];

        mountain_vertex_buffer[18 * i + 9] = last_row[0];
		mountain_vertex_buffer[18 * i + 10] = last_row[1];
		mountain_vertex_buffer[18 * i + 11] = last_row[2];

		mountain_vertex_buffer[18 * i + 12] = 0.5 * last_row[0];
		mountain_vertex_buffer[18 * i + 13] = last_row[1] + 100.0;
		mountain_vertex_buffer[18 * i + 14] = 0.5 * last_row[2];

		mountain_vertex_buffer[18 * i + 15] = 0.5 * curr_row[0];
		mountain_vertex_buffer[18 * i + 16] = last_row[1] + 100.0;
		mountain_vertex_buffer[18 * i + 17] = 0.5 * curr_row[2];

		last_row[0] = curr_row[0];
		last_row[1] = curr_row[1];
		last_row[2] = curr_row[2];
		angle += incr;
	}

    this->mountain = create3DObject(GL_TRIANGLES, 6 * N, mountain_vertex_buffer, COLOR_BROWN, GL_FILL);

    angle = incr;
	last_row[0] = 100.0f;
    last_row[1] = 100.0f;
    last_row[2] = 0.0f;
	// GLfloat curr_row[3];

	for (int i = 0; i < N; i++)
	{
		curr_row[0] = 100.0f * cos(angle);
		curr_row[1] = 100.0f;
		curr_row[2] = 100.0f * sin(angle);
		g_vertex_buffer_data[9 * i] = 0.0f;
		g_vertex_buffer_data[9 * i + 1] = 100.0f;
		g_vertex_buffer_data[9 * i + 2] = 0.0f;
		g_vertex_buffer_data[9 * i + 3] = last_row[0];
		g_vertex_buffer_data[9 * i + 4] = last_row[1];
		g_vertex_buffer_data[9 * i + 5] = last_row[2];
		g_vertex_buffer_data[9 * i + 6] = curr_row[0];
		g_vertex_buffer_data[9 * i + 7] = curr_row[1];
		g_vertex_buffer_data[9 * i + 8] = curr_row[2];
		last_row[0] = curr_row[0];
		last_row[1] = curr_row[1];
		last_row[2] = curr_row[2];
		angle += incr;
	}

    this->lava = create3DObject(GL_TRIANGLES, (N) * 3, g_vertex_buffer_data, COLOR_ORANGE, GL_FILL);
}

void Volcano::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position);    // glTranslatef
    // glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->mountain);
    draw3DObject(this->lava);
}

void Volcano::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

// void Volcano::tick_input(int a, int s, int d, int q, int w, int e, int space, int b) {
//     yaw = (a - d) * 0.01;
//     pitch = (w - s) * 0.01;
//     roll = (q - e) * 0.01;
//     speed += (space - b) * 0.05;
// }

void Volcano::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
    // glm::vec4 dir = glm::normalize(z_axis);
    // this->position.x += -speed * dir.x;
    // this->position.y += -speed * dir.y;
    // this->position.z += -speed * dir.z;
}

