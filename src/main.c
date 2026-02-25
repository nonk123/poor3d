#include <math.h>

#define POOR_IMPLEMENTATION
#include <poormans.h>

#define S_TRUCTURES_IMPLEMENTATION
#include <S_tructures.h>

#include "mesh.h"
#include "camera.h"

int main(int argc, char* argv[]) {
	(void)argc, (void)argv;

	load_obj("assets/penger-no-hull.obj");
	float radius = 2.f, angle = 0.f;

	WHILE_POOR {
		Mesh* mesh = find_mesh("assets/penger-no-hull.obj");
		mesh->pos.y = -0.5f;

		poor_printf(0, 0, "V%d : F%d", mesh->vcount, mesh->fcount);
		look_at(XYZ(cosf(angle) * radius, 0.f, sinf(angle) * radius), ORIGIN);
		angle += 0.01f;

		draw_mesh(mesh);

		if (poor_key_down(POOR_ESC))
			poor_exit();
	}

	extern StTinyMap* meshes;
	FreeTinyMap(meshes);

	return EXIT_SUCCESS;
}
