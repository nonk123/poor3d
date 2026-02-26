#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <S_tructures.h>
#include <poormans.h>

#include "camera.h"
#include "coolmath.h"
#include "mesh.h"
#include "panic.h"

StTinyMap* meshes = NULL;

static void nuke_mesh(void* raw) {
	Mesh* mesh = raw;
	free(mesh->vertices), free(mesh->faces);
}

static void put_mesh(const char* key, const Mesh value) {
	if (!meshes) {
		meshes = NewTinyMap();
		if (!meshes)
			panic();
	}
	StMapPut(meshes, StHashStr(key), &value, sizeof(value))->cleanup = nuke_mesh;
}

Mesh* find_mesh(const char* key) {
	return StMapGet(meshes, StHashStr(key));
}

static char* read_line(FILE* f) {
	if (feof(f))
		return NULL;

	static char line[128] = {0};

	memset(line, 0, sizeof(line));
	char* buf = line;

	int c = EOF;
	while ((c = fgetc(f)) != EOF && c != '\n')
		*buf++ = (char)c;

	return line;
}

static void reset_pos(FILE* f) {
	fseek(f, 0, SEEK_SET);
}

void load_obj(const char* path) {
	Mesh mesh = {0};
	FILE* file = fopen(path, "rt");
	if (!file)
		panic();

	for (const char* line = NULL; (line = read_line(file));) {
		mesh.vcount += line[0] == 'v' && line[1] == ' ';
		mesh.fcount += line[0] == 'f' && line[1] == ' ';
	}

	reset_pos(file);

	mesh.pos = ORIGIN;

	mesh.vertices = malloc(sizeof(Vertex) * mesh.vcount);
	Vertex* v = mesh.vertices;

	mesh.faces = malloc(sizeof(Vertex) * mesh.fcount);
	Face* f = mesh.faces;

	for (const char* line = NULL; (line = read_line(file));) {
		if (line[0] == 'v' && line[1] == ' ') {
			sscanf(line, "v %f %f %f", &v->pos.x, &v->pos.y, &v->pos.z);
			v++;
		} else if (line[0] == 'f' && line[1] == ' ') {
			sscanf(line, "f %hu/%hu/%hu %hu/%hu/%hu %hu/%hu/%hu", &f->a, NULL, NULL, &f->b, NULL, NULL,
				&f->c, NULL, NULL);
			f++;
		}
	}

	put_mesh(path, mesh);
}

void draw_mesh(const Mesh* mesh) {
	extern Camera camera;

	const float znear = 0.5f, zfar = 128.f, zlen = zfar / (zfar - znear);
	const float w = (float)poor_width(), h = (float)poor_height();
	const float font_ar = 9.f / 16.f, ar = (w / h) * font_ar;
	const float tg = tanf(0.5f * camera.fov * DEG2RAD);

	for (size_t iv = 0; iv < mesh->vcount; iv++) {
		Vertex v = mesh->vertices[iv];
		v.pos = v3add(v.pos, mesh->pos);

		// FIXME: fucked up.
		const float yaw = atan2f(camera.dir.z, camera.dir.x);
		v.pos = rotate_y(v.pos, -yaw);
		v.pos = v3sub(v.pos, camera.pos);

		if (v.pos.z < znear || v.pos.z > zfar)
			continue;

		v.pos.x *= tg / v.pos.z / ar;
		v.pos.y *= tg / v.pos.z;
		v.pos.z = v.pos.z * zlen - znear * zlen;

		v.pos.x = (0.5f * v.pos.x + 0.5f) * w;
		v.pos.y = (1.f - (0.5f * v.pos.y + 0.5f)) * h;

		poor_fg((int)v.pos.x, (int)v.pos.y, POOR_BRIGHT_WHITE);
		poor_ch((int)v.pos.x, (int)v.pos.y, '@');
	}
}
