#include "matrix.hpp"

using namespace matrix;

mtx_t matrix::generate(size_t size) {
    mtx_t mx = new row_t[size];
    int gen = 1;
    for (size_t i = 0; i < size; ++i) {
        mx[i] = new col_t[size];
        for (size_t j = 0; j < size; ++j) {
            mx[i][j] = gen++;
        }
    }
    return mx;
}

mtx_t matrix::alloc(size_t size) {
    mtx_t mtx = new row_t[size];
    for (size_t i = 0; i < size; ++i) {
        mtx[i] = new col_t[size];
        std::fill_n(mtx[i], size, 0);
    }
    return mtx;
}

void matrix::free(mtx_t mtx, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        delete[] mtx[i];
    }
    delete[] mtx;
}

mtx_t matrix::copy(mtx_t mtx, size_t size) {
    mtx_t copy = new row_t[size];
    for (size_t i = 0; i < size; ++i) {
        copy[i] = new col_t[size];
        std::memcpy(copy[i], mtx[i], size * sizeof(col_t));
    }
    return copy;
}

bool matrix::read(const char *filename, mtx_t &mtx, size_t &size) {
    std::ifstream is(filename);
    if (!is) {
        std::cout << "Can't open file" << std::endl;
        return false;
    }
    is >> size;
    mtx = new row_t[size];
    for (size_t i = 0; i < size; ++i) {
        mtx[i] = new col_t[size];
        for (size_t j = 0; j < size; ++j) {
            is >> mtx[i][j];
        }
    }
    is.close();
    return true;
}

void matrix::print(const char *title, mtx_t mtx, size_t size) {
    std::cout << title << std::endl;
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            std::cout << mtx[i][j] << '\t';
        }
        std::cout << std::endl;
    }
}
