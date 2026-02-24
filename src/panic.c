#include <stdlib.h>

#include "panic.h"

void panic_(const char* file, int linum) {
	(void)file, (void)linum; // TODO: use
	exit(EXIT_FAILURE);
}
