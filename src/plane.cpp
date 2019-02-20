#include "plane.h"
#include "main.h"

#define N 100

Plane::Plane(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    x_axis = glm::vec4(1, 0, 0, 0);
    y_axis = glm::vec4(0, 1, 0, 0);
    z_axis = glm::vec4(0, 0, 1, 0);
    yaw = 0;
    pitch = 0;
    roll = 0;
    this->rotation = 0;
    speed = 0.2;
    fuel = 1.0;

    static GLfloat body_vertex_buffer[18 * N];
    static GLfloat nose_vertex_buffer[18 * N];
    static GLfloat tail_cone_vertex_buffer[18 * N];

    static GLfloat wings_vertex_buffer[] = {
        0.0, 0.3, -1.0,
        -3.5, 0.1, 0.7,
        0.0, 0.3, 0.0,
        -3.5, 0.1, 0.7,
        -3.5, 0.1, 1.0,
        0.0, 0.3, 0.0,
        0.0, 0.3, -1.0,
        3.5, 0.1, 0.7,
        0.0, 0.3, 0.0,
        3.5, 0.1, 0.7,
        3.5, 0.1, 1.0,
        0.0, 0.3, 0.0
    };

    static GLfloat fins_vertex_buffer[] = {
        0.0, 0.0, 2.0 - 0.3,
        0.0, 0.0, 2.6 - 0.3,
        -1.0, 0.0, 2.5 - 0.3,
        -1.0, 0.0, 2.5 - 0.3,
        0.0, 0.0, 2.6 - 0.3,
        -1.0, 0.0, 2.8 - 0.3,
        0.0, 0.0, 2.0 - 0.3,
        0.0, 0.0, 2.6 - 0.3,
        1.0, 0.0, 2.5 - 0.3,
        1.0, 0.0, 2.5 - 0.3,
        0.0, 0.0, 2.6 - 0.3,
        1.0, 0.0, 2.8 - 0.3
    };

    static GLfloat tail_vertex_buffer[] = {
        0.0, 0.0, 1.7,
        -0.2, 0.0, 2.2,
        0.0, 1.0, 2.2,
        -0.2, 0.0, 2.2,
        0.0, 1.0, 2.2,
        0.0, 1.0, 2.5,
        -0.2, 0.0, 2.2,
        0.0, 1.0, 2.5,
        0.0, 0.0, 2.4,
        0.0, 0.0, 1.7,
        0.2, 0.0, 2.2,
        0.0, 1.0, 2.2,
        0.2, 0.0, 2.2,
        0.0, 1.0, 2.2,
        0.0, 1.0, 2.5,
        0.2, 0.0, 2.2,
        0.0, 1.0, 2.5,
        0.0, 0.0, 2.4
    };

    float incr = 2 * M_PI / N;

	float angle = incr;
	GLfloat last_row[] = {0.3f, 0.0f, 0.0f};
	GLfloat curr_row[2];

	for (int i = 0; i < N; i++)
	{
		curr_row[0] = 0.3f * cos(angle);
		curr_row[1] = 0.3f * sin(angle);
		// curr_row[2] = 0.0f;

		body_vertex_buffer[18 * i] = last_row[0];
		body_vertex_buffer[18 * i + 1] = last_row[1];
		body_vertex_buffer[18 * i + 2] = last_row[2] - 2.0;

		body_vertex_buffer[18 * i + 3] = curr_row[0];
		body_vertex_buffer[18 * i + 4] = curr_row[1];
		body_vertex_buffer[18 * i + 5] = last_row[2] - 2.0;

		body_vertex_buffer[18 * i + 6] = curr_row[0];
		body_vertex_buffer[18 * i + 7] = curr_row[1];
		body_vertex_buffer[18 * i + 8] = last_row[2] + 2.0;

        body_vertex_buffer[18 * i + 9] = last_row[0];
		body_vertex_buffer[18 * i + 10] = last_row[1];
		body_vertex_buffer[18 * i + 11] = last_row[2] - 2.0;

		body_vertex_buffer[18 * i + 12] = last_row[0];
		body_vertex_buffer[18 * i + 13] = last_row[1];
		body_vertex_buffer[18 * i + 14] = last_row[2] + 2.0;

		body_vertex_buffer[18 * i + 15] = curr_row[0];
		body_vertex_buffer[18 * i + 16] = curr_row[1];
		body_vertex_buffer[18 * i + 17] = last_row[2] + 2.0;

		last_row[0] = curr_row[0];
		last_row[1] = curr_row[1];
		// last_row[2] = curr_row[2];
		angle += incr;
	}

    this->body = create3DObject(GL_TRIANGLES, 6 * N, body_vertex_buffer, COLOR_GREY, GL_FILL);

    angle = incr;
    last_row[0] = 0.3;
    last_row[1] = 0.0;
    last_row[2] = -2.0;

	for (int i = 0; i < N; i++)
	{
		curr_row[0] = 0.3f * cos(angle);
		curr_row[1] = 0.3f * sin(angle);
		// curr_row[2] = 0.0f;

		nose_vertex_buffer[18 * i] = last_row[0];
		nose_vertex_buffer[18 * i + 1] = last_row[1];
		nose_vertex_buffer[18 * i + 2] = last_row[2];

		nose_vertex_buffer[18 * i + 3] = curr_row[0];
		nose_vertex_buffer[18 * i + 4] = curr_row[1];
		nose_vertex_buffer[18 * i + 5] = last_row[2];

		nose_vertex_buffer[18 * i + 6] = 0.2 * curr_row[0];
		nose_vertex_buffer[18 * i + 7] = 0.2 * curr_row[1];
		nose_vertex_buffer[18 * i + 8] = last_row[2] - 0.6;

        nose_vertex_buffer[18 * i + 9] = last_row[0];
		nose_vertex_buffer[18 * i + 10] = last_row[1];
		nose_vertex_buffer[18 * i + 11] = last_row[2];

		nose_vertex_buffer[18 * i + 12] = 0.2 * last_row[0];
		nose_vertex_buffer[18 * i + 13] = 0.2 * last_row[1];
		nose_vertex_buffer[18 * i + 14] = last_row[2] - 0.6;

		nose_vertex_buffer[18 * i + 15] = 0.2 * curr_row[0];
		nose_vertex_buffer[18 * i + 16] = 0.2 * curr_row[1];
		nose_vertex_buffer[18 * i + 17] = last_row[2] - 0.6;

		last_row[0] = curr_row[0];
		last_row[1] = curr_row[1];
		// last_row[2] = curr_row[2];
		angle += incr;
	}

    this->nose = create3DObject(GL_TRIANGLES, 6 * N, nose_vertex_buffer, COLOR_GREY, GL_FILL);

    angle = incr;
    last_row[0] = 0.3;
    last_row[1] = 0.0;
    last_row[2] = 2.0;

	for (int i = 0; i < N; i++)
	{
		curr_row[0] = 0.3f * cos(angle);
		curr_row[1] = 0.3f * sin(angle);
		// curr_row[2] = 0.0f;

		tail_cone_vertex_buffer[18 * i] = last_row[0];
		tail_cone_vertex_buffer[18 * i + 1] = last_row[1];
		tail_cone_vertex_buffer[18 * i + 2] = last_row[2];

		tail_cone_vertex_buffer[18 * i + 3] = curr_row[0];
		tail_cone_vertex_buffer[18 * i + 4] = curr_row[1];
		tail_cone_vertex_buffer[18 * i + 5] = last_row[2];

		tail_cone_vertex_buffer[18 * i + 6] = 0.2 * curr_row[0];
		tail_cone_vertex_buffer[18 * i + 7] = 0.2 * curr_row[1];
		tail_cone_vertex_buffer[18 * i + 8] = last_row[2] + 0.8;

        tail_cone_vertex_buffer[18 * i + 9] = last_row[0];
		tail_cone_vertex_buffer[18 * i + 10] = last_row[1];
		tail_cone_vertex_buffer[18 * i + 11] = last_row[2];

		tail_cone_vertex_buffer[18 * i + 12] = 0.2 * last_row[0];
		tail_cone_vertex_buffer[18 * i + 13] = 0.2 * last_row[1];
		tail_cone_vertex_buffer[18 * i + 14] = last_row[2] + 0.8;

		tail_cone_vertex_buffer[18 * i + 15] = 0.2 * curr_row[0];
		tail_cone_vertex_buffer[18 * i + 16] = 0.2 * curr_row[1];
		tail_cone_vertex_buffer[18 * i + 17] = last_row[2] + 0.8;

		last_row[0] = curr_row[0];
		last_row[1] = curr_row[1];
		// last_row[2] = curr_row[2];
		angle += incr;
	}

    this->tail_cone = create3DObject(GL_TRIANGLES, 6 * N, tail_cone_vertex_buffer, COLOR_GREY, GL_FILL);

    static GLfloat engine_locations[] = {
        -1.2, 0.232 - 0.1, -0.2,
        -2.4, 0.163 - 0.1, 0.3,
        1.2, 0.232 - 0.1, -0.2,
        2.4, 0.163 - 0.1, 0.3
    };

    for (int j = 0; j < 4; j++) {
        GLfloat engine_vertex_buffer[18 * N];
        
        angle = incr;
        last_row[0] = engine_locations[j * 3] + 0.1;
        last_row[1] = engine_locations[j * 3 + 1];
        last_row[2] = engine_locations[j * 3 + 2];

        for (int i = 0; i < N; i++) {
            curr_row[0] = engine_locations[j * 3] + 0.1f * cos(angle);
            curr_row[1] = engine_locations[j * 3 + 1] + 0.1f * sin(angle);
            // curr_row[2] = 0.0f;

            engine_vertex_buffer[18 * i] = last_row[0];
            engine_vertex_buffer[18 * i + 1] = last_row[1];
            engine_vertex_buffer[18 * i + 2] = last_row[2] - 0.5;

            engine_vertex_buffer[18 * i + 3] = curr_row[0];
            engine_vertex_buffer[18 * i + 4] = curr_row[1];
            engine_vertex_buffer[18 * i + 5] = last_row[2] - 0.5;

            engine_vertex_buffer[18 * i + 6] = curr_row[0];
            engine_vertex_buffer[18 * i + 7] = curr_row[1];
            engine_vertex_buffer[18 * i + 8] = last_row[2] + 0.5;

            engine_vertex_buffer[18 * i + 9] = last_row[0];
            engine_vertex_buffer[18 * i + 10] = last_row[1];
            engine_vertex_buffer[18 * i + 11] = last_row[2] - 0.5;

            engine_vertex_buffer[18 * i + 12] = last_row[0];
            engine_vertex_buffer[18 * i + 13] = last_row[1];
            engine_vertex_buffer[18 * i + 14] = last_row[2] + 0.5;

            engine_vertex_buffer[18 * i + 15] = curr_row[0];
            engine_vertex_buffer[18 * i + 16] = curr_row[1];
            engine_vertex_buffer[18 * i + 17] = last_row[2] + 0.5;

            last_row[0] = curr_row[0];
            last_row[1] = curr_row[1];
            // last_row[2] = curr_row[2];
            angle += incr;
        }
        this->engines[j] = create3DObject(GL_TRIANGLES, 6 * N, engine_vertex_buffer, COLOR_GREY, GL_FILL);
    }

    this->wings = create3DObject(GL_TRIANGLES, 4 * 3, wings_vertex_buffer, COLOR_GREY, GL_FILL);
    this->fins = create3DObject(GL_TRIANGLES, 4 * 3, fins_vertex_buffer, COLOR_GREY, GL_FILL);
    this->tail = create3DObject(GL_TRIANGLES, 6 * 3, tail_vertex_buffer, COLOR_DARK_GREY, GL_FILL);

    this->spheres.push_back(std::make_pair(glm::vec4(0.0, 0.0, 0.3, 0.0), 0.3));
    this->spheres.push_back(std::make_pair(glm::vec4(0.0, 0.0, 0.6, 0.0), 0.3));
    this->spheres.push_back(std::make_pair(glm::vec4(0.0, 0.0, 0.9, 0.0), 0.3));
    this->spheres.push_back(std::make_pair(glm::vec4(0.0, 0.0, 1.2, 0.0), 0.3));
    this->spheres.push_back(std::make_pair(glm::vec4(0.0, 0.0, 1.5, 0.0), 0.3));
    this->spheres.push_back(std::make_pair(glm::vec4(0.0, 0.0, 1.8, 0.0), 0.3));
    this->spheres.push_back(std::make_pair(glm::vec4(0.0, 0.0, 2.1, 0.0), 0.3));
    this->spheres.push_back(std::make_pair(glm::vec4(0.0, 0.0, -0.3, 0.0), 0.3));
    this->spheres.push_back(std::make_pair(glm::vec4(0.0, 0.0, -0.6, 0.0), 0.3));
    this->spheres.push_back(std::make_pair(glm::vec4(0.0, 0.0, -0.9, 0.0), 0.3));
    this->spheres.push_back(std::make_pair(glm::vec4(0.0, 0.0, -1.2, 0.0), 0.3));
    this->spheres.push_back(std::make_pair(glm::vec4(0.0, 0.0, -1.5, 0.0), 0.3));
    this->spheres.push_back(std::make_pair(glm::vec4(0.0, 0.0, -1.8, 0.0), 0.3));
    this->spheres.push_back(std::make_pair(glm::vec4(0.0, 0.0, -2.1, 0.0), 0.3));
    this->spheres.push_back(std::make_pair(glm::vec4(-0.85, -0.5, -0.15, 0.0), 0.85));
    this->spheres.push_back(std::make_pair(glm::vec4(-2.3, -0.5, 0.0, 0.0), 0.6));
    this->spheres.push_back(std::make_pair(glm::vec4(-3.2,-0.5, 0.5, 0.0), 0.3));
    this->spheres.push_back(std::make_pair(glm::vec4(0.85, -0.5, -0.15, 0.0), 0.85));
    this->spheres.push_back(std::make_pair(glm::vec4(2.3, -0.5, 0.0, 0.0), 0.6));
    this->spheres.push_back(std::make_pair(glm::vec4(3.2,-0.5, 0.5, 0.0), 0.3));
}

void print_matrix(glm::mat4 &m) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            std::cout << m[j][i] << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Plane::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    x_axis = glm::rotate(x_axis, yaw, glm::vec3(y_axis[0], y_axis[1], y_axis[2]));
    z_axis = glm::rotate(z_axis, yaw, glm::vec3(y_axis[0], y_axis[1], y_axis[2]));

    y_axis = glm::rotate(y_axis, pitch, glm::vec3(x_axis[0], x_axis[1], x_axis[2]));
    z_axis = glm::rotate(z_axis, pitch, glm::vec3(x_axis[0], x_axis[1], x_axis[2]));

    x_axis = glm::rotate(x_axis, roll, glm::vec3(z_axis[0], z_axis[1], z_axis[2]));
    y_axis = glm::rotate(y_axis, roll, glm::vec3(z_axis[0], z_axis[1], z_axis[2]));

    glm::mat4 rotate = glm::mat4(x_axis, y_axis, z_axis, glm::vec4(0, 0, 0, 1));
    for (int i = 0; i < this->spheres.size(); i++) {
        this->spheres[i].first = rotate * this->spheres[i].first;
    }
    glm::mat4 translate = glm::translate(this->position);    // glTranslatef
    // glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= translate * rotate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->wings);
    draw3DObject(this->body);
    draw3DObject(this->nose);
    draw3DObject(this->tail_cone);
    draw3DObject(this->tail);
    draw3DObject(this->fins);
    for (int i = 0; i < 4; i++) {
        draw3DObject(this->engines[i]);
    }
}

void Plane::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Plane::tick_input(int a, int s, int d, int q, int w, int e, int space, int b) {
    yaw = (a - d) * 0.01;
    pitch = (w - s) * 0.01;
    roll = (q - e) * 0.01;
    speed = fmax(0, speed + (space - b) * 0.001);
    speed = fmin(1.0, speed);
}

void Plane::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
    glm::vec4 dir = glm::normalize(z_axis);
    this->position.x += -speed * dir.x;
    this->position.y += -speed * dir.y;
    this->position.z += -speed * dir.z;
    this->fuel -= this->speed * 0.0005;
}

