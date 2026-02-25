#pragma once

#define XYZ(_x, _y, _z) ((Vec3){.x = (_x), .y = (_y), .z = (_z)})
#define ORIGIN XYZ(0.f, 0.f, 0.f)
#define UP XYZ(0.f, 1.f, 0.f)

typedef struct {
	float x, y, z;
} Vec3;

Vec3 v3add(Vec3, Vec3), v3sub(Vec3, Vec3);
Vec3 v3norm(Vec3);

void rotate(float* x, float* y, float angle);
Vec3 rotate_x(Vec3, float), rotate_y(Vec3, float), rotate_z(Vec3, float);
