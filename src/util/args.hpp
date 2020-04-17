#pragma once
#include <cstring>

#define ARG_EQ(A) (strcmp(argv[i], A) == 0)
#define ARG_EITHER(A,B) ((strcmp(argv[i], A) == 0) || (strcmp(argv[i], B) == 0))
