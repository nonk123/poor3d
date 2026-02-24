#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <S_tructures.h>

#include "mesh.h"
#include "panic.h"

static StTinyMap* meshes = NULL;

static void put_mesh(const char* key, const Mesh value) {
	if (!meshes) {
		meshes = NewTinyMap();
		if (!meshes)
			panic();
	}
	StMapPut(meshes, StHashStr(key), &value, sizeof(value));
}

Mesh* find_mesh(const char* key) {
	return StMapGet(meshes, StHashStr(key));
}

static char* read_line(FILE* f) {
	static int c = '\n';
	if (c == EOF)
		return NULL;

	static char line[128] = {0};

	memset(line, 0, sizeof(line));
	char* buf = line;

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

	put_mesh(path, mesh);
}
