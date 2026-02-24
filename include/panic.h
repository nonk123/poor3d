#pragma once

void panic_(const char* file, int linum);
#define panic(...) panic_(__FILE__, __LINE__)
