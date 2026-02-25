#pragma once

#include "vec3.h"

typedef struct {
	Vec3 pos, dir;
	float fov;
} Camera;

void look_at(Vec3 from, Vec3 target), look_dir(Vec3 from, Vec3 dir);
