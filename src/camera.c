#include "camera.h"

Camera camera = {.fov = 90.f};

void look_at(Vec3 from, Vec3 target) {
	look_dir(from, v3sub(target, from));
}

void look_dir(Vec3 from, Vec3 dir) {
	camera.pos = from;
	camera.dir = v3norm(dir);
}
