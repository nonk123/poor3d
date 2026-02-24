#pragma once

#include <stdint.h>

#include "vec3.h"

typedef struct {
	Vec3 pos;
} Vertex;

typedef struct {
	uint16_t a, b, c;
} Face;

typedef struct {
	Vertex* vertices;
	size_t vcount;

	Face* faces;
	uint16_t fcount;
} Mesh;

Mesh* find_mesh(const char* key);
void load_obj(const char* path);
