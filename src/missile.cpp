#include "missile.h"
#include "main.h"

#define N 10

Missile::Missile(glm::vec3 pos, glm::vec3 dir, float speed) {
    this->position = glm::vec3(pos);
    this->velocity = glm::vec3(dir.x * (speed + 0.8), dir.y * (speed + 0.8), dir.z * (speed + 0.8));
    x_axis = glm::vec4(1, 0, 0, 0);
    y_axis = glm::vec4(0, 1, 0, 0);
    z_axis = glm::vec4(0, 0, 1, 0);
	hit = false;
	sphere = std::make_pair(glm::vec4(0.0, 0.0, -2.0, 0.0), 0.3);
    yaw = 0;
    pitch = 0;
    roll = 0;
    this->rotation = 0;
    speed = 1;

    static GLfloat body_vertex_buffer[18 * N];
    static GLfloat nose_vertex_buffer[18 * N];
    static GLfloat trail_vertex_buffer[18 * N];

    float incr = 2 * M_PI / N;

	float angle = incr;
	GLfloat last_row[] = {0.03f, 0.0f, 0.0f};
	GLfloat curr_row[2];

	for (int i = 0; i < N; i++)
	{
		curr_row[0] = 0.03f * cos(angle);
		curr_row[1] = 0.03f * sin(angle);
		// curr_row[2] = 0.0f;

		body_vertex_buffer[18 * i] = last_row[0];
		body_vertex_buffer[18 * i + 1] = last_row[1];
		body_vertex_buffer[18 * i + 2] = last_row[2] - 0.20;

		body_vertex_buffer[18 * i + 3] = curr_row[0];
		body_vertex_buffer[18 * i + 4] = curr_row[1];
		body_vertex_buffer[18 * i + 5] = last_row[2] - 0.20;

		body_vertex_buffer[18 * i + 6] = curr_row[0];
		body_vertex_buffer[18 * i + 7] = curr_row[1];
		body_vertex_buffer[18 * i + 8] = last_row[2] + 0.20;

        body_vertex_buffer[18 * i + 9] = last_row[0];
		body_vertex_buffer[18 * i + 10] = last_row[1];
		body_vertex_buffer[18 * i + 11] = last_row[2] - 0.20;

		body_vertex_buffer[18 * i + 12] = last_row[0];
		body_vertex_buffer[18 * i + 13] = last_row[1];
		body_vertex_buffer[18 * i + 14] = last_row[2] + 0.20;

		body_vertex_buffer[18 * i + 15] = curr_row[0];
		body_vertex_buffer[18 * i + 16] = curr_row[1];
		body_vertex_buffer[18 * i + 17] = last_row[2] + 0.20;

		last_row[0] = curr_row[0];
		last_row[1] = curr_row[1];
		// last_row[2] = curr_row[2];
		angle += incr;
	}

    this->body = create3DObject(GL_TRIANGLES, 6 * N, body_vertex_buffer, COLOR_BLACK, GL_FILL);

    angle = incr;
    last_row[0] = 0.03;
    last_row[1] = 0.0;
    last_row[2] = -0.20;

	for (int i = 0; i < N; i++)
	{
		curr_row[0] = 0.03f * cos(angle);
		curr_row[1] = 0.03f * sin(angle);
		// curr_row[2] = 0.0f;

		nose_vertex_buffer[18 * i] = last_row[0];
		nose_vertex_buffer[18 * i + 1] = last_row[1];
		nose_vertex_buffer[18 * i + 2] = last_row[2];

		nose_vertex_buffer[18 * i + 3] = curr_row[0];
		nose_vertex_buffer[18 * i + 4] = curr_row[1];
		nose_vertex_buffer[18 * i + 5] = last_row[2];

		nose_vertex_buffer[18 * i + 6] = 0.2 * curr_row[0];
		nose_vertex_buffer[18 * i + 7] = 0.2 * curr_row[1];
		nose_vertex_buffer[18 * i + 8] = last_row[2] - 0.06;

        nose_vertex_buffer[18 * i + 9] = last_row[0];
		nose_vertex_buffer[18 * i + 10] = last_row[1];
		nose_vertex_buffer[18 * i + 11] = last_row[2];

		nose_vertex_buffer[18 * i + 12] = 0.2 * last_row[0];
		nose_vertex_buffer[18 * i + 13] = 0.2 * last_row[1];
		nose_vertex_buffer[18 * i + 14] = last_row[2] - 0.06;

		nose_vertex_buffer[18 * i + 15] = 0.2 * curr_row[0];
		nose_vertex_buffer[18 * i + 16] = 0.2 * curr_row[1];
		nose_vertex_buffer[18 * i + 17] = last_row[2] - 0.06;

		last_row[0] = curr_row[0];
		last_row[1] = curr_row[1];
		// last_row[2] = curr_row[2];
		angle += incr;
	}

    this->nose = create3DObject(GL_TRIANGLES, 6 * N, nose_vertex_buffer, COLOR_BLACK, GL_FILL);

    angle = incr;
    last_row[0] = 0.03;
    last_row[1] = 0.0;
    last_row[2] = 0.20;

	for (int i = 0; i < N; i++)
	{
		curr_row[0] = 0.03f * cos(angle);
		curr_row[1] = 0.03f * sin(angle);
		// curr_row[2] = 0.0f;

		trail_vertex_buffer[18 * i] = last_row[0];
		trail_vertex_buffer[18 * i + 1] = last_row[1];
		trail_vertex_buffer[18 * i + 2] = last_row[2];

		trail_vertex_buffer[18 * i + 3] = curr_row[0];
		trail_vertex_buffer[18 * i + 4] = curr_row[1];
		trail_vertex_buffer[18 * i + 5] = last_row[2];

		trail_vertex_buffer[18 * i + 6] = curr_row[0];
		trail_vertex_buffer[18 * i + 7] = curr_row[1];
		trail_vertex_buffer[18 * i + 8] = last_row[2] + 0.08;

        trail_vertex_buffer[18 * i + 9] = last_row[0];
		trail_vertex_buffer[18 * i + 10] = last_row[1];
		trail_vertex_buffer[18 * i + 11] = last_row[2];

		trail_vertex_buffer[18 * i + 12] = last_row[0];
		trail_vertex_buffer[18 * i + 13] = last_row[1];
		trail_vertex_buffer[18 * i + 14] = last_row[2] + 0.08;

		trail_vertex_buffer[18 * i + 15] = curr_row[0];
		trail_vertex_buffer[18 * i + 16] = curr_row[1];
		trail_vertex_buffer[18 * i + 17] = last_row[2] + 0.08;

		last_row[0] = curr_row[0];
		last_row[1] = curr_row[1];
		// last_row[2] = curr_row[2];
		angle += incr;
	}

    this->trail = create3DObject(GL_TRIANGLES, 6 * N, trail_vertex_buffer, COLOR_ORANGE, GL_FILL);
}

void Missile::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    x_axis = glm::rotate(x_axis, yaw, glm::vec3(y_axis[0], y_axis[1], y_axis[2]));
    z_axis = glm::rotate(z_axis, yaw, glm::vec3(y_axis[0], y_axis[1], y_axis[2]));

    y_axis = glm::rotate(y_axis, pitch, glm::vec3(x_axis[0], x_axis[1], x_axis[2]));
    z_axis = glm::rotate(z_axis, pitch, glm::vec3(x_axis[0], x_axis[1], x_axis[2]));

    x_axis = glm::rotate(x_axis, roll, glm::vec3(z_axis[0], z_axis[1], z_axis[2]));
    y_axis = glm::rotate(y_axis, roll, glm::vec3(z_axis[0], z_axis[1], z_axis[2]));

    glm::mat4 rotate = glm::mat4(x_axis, y_axis, z_axis, glm::vec4(0, 0, 0, 1));
	this->sphere.first = rotate * this->sphere.first;
    glm::mat4 translate = glm::translate(this->position);    // glTranslatef
	glm::mat4 scale = glm::scale(glm::vec3(10.0, 10.0, 10.0));
    // glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= translate * rotate * scale;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);

	if (!hit) {
		draw3DObject(this->body);
		draw3DObject(this->nose);
		draw3DObject(this->trail);
	}
}

void Missile::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Missile::tick() {
    this->position.x += this->velocity.x;
    this->position.y += this->velocity.y;
    this->position.z += this->velocity.z;

    this->velocity.y -= GRAVITY;

	this->z_axis = glm::normalize(glm::vec4(-velocity.x, -velocity.y, -velocity.z, 0.0));
    this->x_axis = glm::vec4(glm::cross(glm::vec3(0, 1, 0), glm::vec3(z_axis.x, z_axis.y, z_axis.z)), 0.0);
    this->y_axis = glm::vec4(glm::cross(glm::vec3(x_axis.x, x_axis.y, x_axis.z), 
                                        glm::vec3(z_axis.x, z_axis.y, z_axis.z)), 
                                        0.0);
}

