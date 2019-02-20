#include "checkpoint.h"
#include "main.h"

#define N 100

Arrow::Arrow(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;

    static GLfloat body_vertex_buffer[] = {
        -10.0, 0.0, 0.0,
        10.0, 0.0, 0.0,
        0.0, -5.0, 0.0,
        -5.0, 0.0, 0.0,
        -5.0, 10.0, 0.0,
        5.0, 0.0, 0.0,
        5.0, 0.0, 0.0,
        5.0, 10.0, 0.0,
        -5.0, 10.0, 0.0
    };

    this->object = create3DObject(GL_TRIANGLES, 3 * 3, body_vertex_buffer, COLOR_RED, GL_FILL);
}

void Arrow::tick() {
    this->rotation += 0.05;
}

void Arrow::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 rotate = glm::rotate(this->rotation, glm::vec3(0, 1, 0));
    glm::mat4 translate = glm::translate(this->position);    // glTranslatef
    Matrices.model *= translate * rotate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    // draw3DObject(this->lava);
}

Cannon::Cannon(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    float incr = 2 * M_PI / N;
    x_axis = glm::vec4(1, 0, 0, 0);
    y_axis = glm::vec4(0, 1, 0, 0);
    z_axis = glm::vec4(0, 0, 1, 0);

    static GLfloat body_vertex_buffer[20 * N];
    static GLfloat front_vertex_buffer[10 * N];
    static GLfloat back_vertex_buffer[10 * N];
	float angle = incr;
	GLfloat last_row[] = {5.0f, 0.0f, 0.0f};
	GLfloat curr_row[3];

	for (int i = 0; i <= N; i++)
	{
		curr_row[0] = 5.0f * cos(angle);
		curr_row[1] = 5.0f * sin(angle);
		// curr_row[2] = 0.0f;

		body_vertex_buffer[18 * i] = last_row[0];
		body_vertex_buffer[18 * i + 1] = last_row[1];
		body_vertex_buffer[18 * i + 2] = last_row[2] - 20.0;

		body_vertex_buffer[18 * i + 3] = curr_row[0];
		body_vertex_buffer[18 * i + 4] = curr_row[1];
		body_vertex_buffer[18 * i + 5] = last_row[2] - 20.0;

		body_vertex_buffer[18 * i + 6] = curr_row[0];
		body_vertex_buffer[18 * i + 7] = curr_row[1];
		body_vertex_buffer[18 * i + 8] = last_row[2] + 20.0;

        body_vertex_buffer[18 * i + 9] = last_row[0];
		body_vertex_buffer[18 * i + 10] = last_row[1];
		body_vertex_buffer[18 * i + 11] = last_row[2] - 20.0;

		body_vertex_buffer[18 * i + 12] = last_row[0];
		body_vertex_buffer[18 * i + 13] = last_row[1];
		body_vertex_buffer[18 * i + 14] = last_row[2] + 20.0;

		body_vertex_buffer[18 * i + 15] = curr_row[0];
		body_vertex_buffer[18 * i + 16] = curr_row[1];
		body_vertex_buffer[18 * i + 17] = last_row[2] + 20.0;

		last_row[0] = curr_row[0];
		last_row[1] = curr_row[1];
		// last_row[2] = curr_row[2];
		angle += incr;
	}

    this->cyl = create3DObject(GL_TRIANGLES, 6 * (N + 1), body_vertex_buffer, COLOR_BLACK, GL_FILL);

    angle = incr;
	last_row[0] = 5.0f;
    last_row[1] = 0.0f;
    last_row[2] = -20.0f;

	for (int i = 0; i < N; i++)
	{
		curr_row[0] = 5.0f * cos(angle);
		curr_row[1] = 5.0f * sin(angle);
		curr_row[2] = 0.0f;
		front_vertex_buffer[9 * i] = 0.0f;
		front_vertex_buffer[9 * i + 1] = 0.0f;
		front_vertex_buffer[9 * i + 2] = -20.0f;
		front_vertex_buffer[9 * i + 3] = last_row[0];
		front_vertex_buffer[9 * i + 4] = last_row[1];
		front_vertex_buffer[9 * i + 5] = last_row[2];
		front_vertex_buffer[9 * i + 6] = curr_row[0];
		front_vertex_buffer[9 * i + 7] = curr_row[1];
		front_vertex_buffer[9 * i + 8] = curr_row[2];
		last_row[0] = curr_row[0];
		last_row[1] = curr_row[1];
		last_row[2] = curr_row[2];
		angle += incr;
	}

    this->front = create3DObject(GL_TRIANGLES, (N) * 3, front_vertex_buffer, COLOR_DARK_GREY, GL_FILL);

    angle = incr;
	last_row[0] = 5.0f;
    last_row[1] = 0.0f;
    last_row[2] = 20.0f;

	for (int i = 0; i < N; i++)
	{
		curr_row[0] = 5.0f * cos(angle);
		curr_row[1] = 5.0f * sin(angle);
		curr_row[2] = 0.0f;
		back_vertex_buffer[9 * i] = 0.0f;
		back_vertex_buffer[9 * i + 1] = 0.0f;
		back_vertex_buffer[9 * i + 2] = 20.0f;
		back_vertex_buffer[9 * i + 3] = last_row[0];
		back_vertex_buffer[9 * i + 4] = last_row[1];
		back_vertex_buffer[9 * i + 5] = last_row[2];
		back_vertex_buffer[9 * i + 6] = curr_row[0];
		back_vertex_buffer[9 * i + 7] = curr_row[1];
		back_vertex_buffer[9 * i + 8] = curr_row[2];
		last_row[0] = curr_row[0];
		last_row[1] = curr_row[1];
		last_row[2] = curr_row[2];
		angle += incr;
	}

    this->back = create3DObject(GL_TRIANGLES, (N) * 3, back_vertex_buffer, COLOR_DARK_GREY, GL_FILL);
}

void Cannon::tick(glm::vec3 plane_pos) {
    this->z_axis = glm::normalize(glm::vec4(plane_pos.x + 2 - this->position.x,
                                                plane_pos.y + 2 - this->position.y,
                                                plane_pos.z + 2 - this->position.z, 
                                                0.0));
    this->x_axis = glm::vec4(glm::cross(glm::vec3(0, 1, 0), glm::vec3(z_axis.x, z_axis.y, z_axis.z)), 0.0);
    this->y_axis = glm::vec4(glm::cross(glm::vec3(x_axis.x, x_axis.y, x_axis.z), 
                                        glm::vec3(z_axis.x, z_axis.y, z_axis.z)), 
                                        0.0);
}

void Cannon::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 rotate = glm::mat4(x_axis, y_axis, z_axis, glm::vec4(0, 0, 0, 1));
    glm::mat4 translate = glm::translate(this->position);    // glTranslatef
    Matrices.model *= translate * rotate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->cyl);
    draw3DObject(this->front);
    draw3DObject(this->back);
    // draw3DObject(this->lava);
}

Checkpoint::Checkpoint(float x, float z) {
    this->position = glm::vec3(x, -200.0, z);
    this->rotation = 0;
    this->life = 10;

    this->cannon = Cannon(x, -200 + 40.0, z);
    this->arrow = Arrow(x, 0, z);

    static GLfloat mountain_vertex_buffer[18 * N];
    static GLfloat g_vertex_buffer_data[10 * N];

    float incr = 2 * M_PI / N;

	float angle = incr;
	GLfloat last_row[] = {100.0f, 0.0f, 0.0f};
	GLfloat curr_row[3];

	for (int i = 0; i < N; i++)
	{
		curr_row[0] = 100.0f * cos(angle);
		curr_row[1] = 0.0f;
		curr_row[2] = 100.0f * sin(angle);

		mountain_vertex_buffer[18 * i] = last_row[0];
		mountain_vertex_buffer[18 * i + 1] = last_row[1];
		mountain_vertex_buffer[18 * i + 2] = last_row[2];

		mountain_vertex_buffer[18 * i + 3] = curr_row[0];
		mountain_vertex_buffer[18 * i + 4] = last_row[1];
		mountain_vertex_buffer[18 * i + 5] = curr_row[2];

		mountain_vertex_buffer[18 * i + 6] = curr_row[0];
		mountain_vertex_buffer[18 * i + 7] = last_row[1] + 25.0;
		mountain_vertex_buffer[18 * i + 8] = curr_row[2];

        mountain_vertex_buffer[18 * i + 9] = last_row[0];
		mountain_vertex_buffer[18 * i + 10] = last_row[1];
		mountain_vertex_buffer[18 * i + 11] = last_row[2];

		mountain_vertex_buffer[18 * i + 12] = last_row[0];
		mountain_vertex_buffer[18 * i + 13] = last_row[1] + 25.0;
		mountain_vertex_buffer[18 * i + 14] = last_row[2];

		mountain_vertex_buffer[18 * i + 15] = curr_row[0];
		mountain_vertex_buffer[18 * i + 16] = last_row[1] + 25.0;
		mountain_vertex_buffer[18 * i + 17] = curr_row[2];

		last_row[0] = curr_row[0];
		last_row[1] = curr_row[1];
		last_row[2] = curr_row[2];
		angle += incr;
	}

    this->base = create3DObject(GL_TRIANGLES, 6 * N, mountain_vertex_buffer, COLOR_BROWN, GL_FILL);

    angle = incr;
	last_row[0] = 100.0f;
    last_row[1] = 25.0f;
    last_row[2] = 0.0f;
	// GLfloat curr_row[3];

	for (int i = 0; i < N; i++)
	{
		curr_row[0] = 100.0f * cos(angle);
		curr_row[1] = 25.0f;
		curr_row[2] = 100.0f * sin(angle);
		g_vertex_buffer_data[9 * i] = 0.0f;
		g_vertex_buffer_data[9 * i + 1] = 25.0f;
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

    this->top = create3DObject(GL_TRIANGLES, (N) * 3, g_vertex_buffer_data, COLOR_GREEN, GL_FILL);
}

void Checkpoint::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position);    // glTranslatef
    // glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->base);
    draw3DObject(this->top);
    this->cannon.draw(VP);
    this->arrow.draw(VP);
}

void Checkpoint::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

// void Checkpoint::tick_input(int a, int s, int d, int q, int w, int e, int space, int b) {
//     yaw = (a - d) * 0.01;
//     pitch = (w - s) * 0.01;
//     roll = (q - e) * 0.01;
//     speed += (space - b) * 0.05;
// }

void Checkpoint::tick(glm::vec3 plane_pos) {
    this->cannon.tick(plane_pos);
    this->arrow.tick();
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
    // glm::vec4 dir = glm::normalize(z_axis);
    // this->position.x += -speed * dir.x;
    // this->position.y += -speed * dir.y;
    // this->position.z += -speed * dir.z;
}

