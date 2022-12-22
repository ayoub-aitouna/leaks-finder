#ifndef ALLOCATOR_H
#define ALLOCATOR_H
#include "leak_finder.h"
#include <stdio.h>

void    *my_malloc(size_t size, const char *file, const char *function, int line);
#  define malloc(size) my_malloc(size, __FILE__, __FUNCTION__, __LINE__)

#endif
