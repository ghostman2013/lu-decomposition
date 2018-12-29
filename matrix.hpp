#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <algorithm>

#include <cstring>
#include <fstream>
#include <iostream>

namespace matrix {

typedef float col_t;
typedef col_t * row_t;
typedef row_t * mtx_t;

mtx_t generate(size_t size);
mtx_t alloc(size_t size);
void free(mtx_t mtx, size_t size);
mtx_t copy(mtx_t mtx, size_t size);
bool read(const char *filename, mtx_t &mtx, size_t &size);
void print(const char *title, mtx_t mtx, size_t size);

}

#endif // MATRIX_HPP
