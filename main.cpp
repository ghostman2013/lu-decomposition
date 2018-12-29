#include "matrix.hpp"
#include "lud.hpp"

#include <chrono>
#include <type_traits>

using namespace matrix;
using namespace std;

using lud_func_t = std::add_pointer<void(mtx_t, mtx_t, mtx_t, size_t)>::type;

// const static char *c_filename = "matrix.txt";
const static int c_repeats = 10;
const static size_t c_matrix_size = 1000;

void exec(const char *, mtx_t, mtx_t, mtx_t, size_t, lud_func_t);
void proccess(mtx_t, mtx_t, mtx_t, size_t);

int main() {
    mtx_t mx, lmx, umx;
    size_t size = c_matrix_size;

    // Prepare matrices
    //if (!matrix::read(c_filename, mx, size)) { return 1; }
    mx = matrix::generate(size);
    lmx = matrix::alloc(size);
    umx = matrix::alloc(size);

    proccess(mx, lmx, umx, size);

    // Delete matrices
    matrix::free(mx, size);
    matrix::free(lmx, size);
    matrix::free(umx, size);

    return 0;
}

void exec(const char *title, mtx_t mx, mtx_t lmx, mtx_t umx,
          size_t size, lud_func_t func) {
    double count = 0;
    for (int i = 0; i < c_repeats; ++i) {
        mtx_t cmx = matrix::copy(mx, size);
        auto start = chrono::steady_clock::now();
        func(cmx, lmx, umx, size);
        auto end = chrono::steady_clock::now();
        std::chrono::duration<double> diff = end - start;
        count += diff.count();
    }
    std::cout << title << " time " << (count / c_repeats) << " s\n";
}

void proccess(mtx_t mx, mtx_t lmx, mtx_t umx, size_t size) {
    //matrix::print("Source matrix:", mx, size);
    exec("Single process", mx, lmx, umx, size, lud::doolittle);
    exec("Multiprocess", mx, lmx, umx, size, lud::crout_mp);
    //matrix::print("L-matrix:", lmx, size);
    //matrix::print("U-matrix:", umx, size);
}
