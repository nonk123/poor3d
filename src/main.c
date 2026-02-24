#define POOR_IMPLEMENTATION
#include <poormans.h>

#define S_TRUCTURES_IMPLEMENTATION
#include <S_tructures.h>

#include "mesh.h"

int main(int argc, char* argv[]) {
	(void)argc, (void)argv;

	load_obj("assets/penger-no-hull.obj");

	WHILE_POOR {
		const Mesh* mesh = find_mesh("assets/penger-no-hull.obj");
		poor_printf(0, 0, "V%d : F%d", mesh->vcount, mesh->fcount);
		if (poor_key_down(POOR_ESC))
			poor_exit();
	}

	return EXIT_SUCCESS;
}
