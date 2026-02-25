#include <math.h>

#include "vec3.h"

Vec3 v3add(Vec3 a, Vec3 b) {
	a.x += b.x, a.y += b.y, a.z += b.z;
	return a;
}

Vec3 v3sub(Vec3 a, Vec3 b) {
	a.x -= b.x, a.y -= b.y, a.z -= b.z;
	return a;
}

float v3dot(Vec3 a, Vec3 b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

float v3length(Vec3 v) {
	return sqrtf(v3dot(v, v));
}

Vec3 v3norm(Vec3 v) {
	const float l = v3length(v);
	v.x /= l, v.y /= l, v.z /= l;
	return v;
}

void rotate(float* x, float* y, float angle) {
	const float s = sinf(angle), c = cosf(angle);
	const float x1 = *x * c - *y * s;
	const float y1 = *x * s + *y * c;
	*x = x1, *y = y1;
}

Vec3 rotate_x(Vec3 v, float angle) {
	rotate(&v.y, &v.z, angle);
	return v;
}

Vec3 rotate_y(Vec3 v, float angle) {
	rotate(&v.x, &v.z, angle);
	return v;
}

Vec3 rotate_z(Vec3 v, float angle) {
	rotate(&v.y, &v.x, angle);
	return v;
}
