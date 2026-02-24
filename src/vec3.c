#include "vec3.h"

Vec3 v3add(Vec3 a, Vec3 b) {
	a.x += b.x, a.y += b.y, a.z += b.z;
	return a;
}

Vec3 v3sub(Vec3 a, Vec3 b) {
	a.x -= b.x, a.y -= b.y, a.z -= b.z;
	return a;
}
