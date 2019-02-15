#include "main.h"

#ifndef UTILS_H
#define UTILS_H

VAO *construct_circle(float x, float y, float z, float r);

VAO *construct_quad(float x1, float y1, float z1,
                        float x2, float y2, float z2,
                        float x3, float y3, float z3,
                        float x4, float y4, float z4);

VAO *construct_cylinder(float x1, float y1, float z1,
                        float x2, float y2, float z2,
                        float r);

VAO *construct_cone(float x1, float y1, float z1,
                    float x2, float y2, float z2,
                    float r);

VAO *construct_sphere(float x, float y, float z, float r);

#endif