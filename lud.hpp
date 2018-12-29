#ifndef LUD_HPP
#define LUD_HPP

#include "matrix.hpp"

#include <cstddef>

namespace lud {

using namespace matrix;

void doolittle(mtx_t mx, mtx_t lmx, mtx_t umx, size_t size);
void crout(mtx_t mx, mtx_t lmx, mtx_t umx, size_t size);
void crout_mp(mtx_t mx, mtx_t lmx, mtx_t umx, size_t size);

}

#endif // LUD_HPP
