#include "lud.hpp"

using namespace lud;

void lud::doolittle(mtx_t mx, mtx_t lmx, mtx_t umx, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        // Upper Triangular
        for (size_t k = i; k < size; ++k) {
            // Summation of L(i, j) * U(j, k)
            int sum = 0;
            for (size_t j = 0; j < i; ++j) {
                sum += (lmx[i][j] * umx[j][k]);
            }
            // Evaluating U(i, k)
            umx[i][k] = mx[i][k] - sum;
        }
        // Lower Triangular
        for (size_t k = i; k < size; ++k) {
            if (i == k) {
                lmx[i][i] = 1; // Diagonal as 1
            } else {
                // Summation of L(k, j) * U(j, i)
                int sum = 0;
                for (size_t j = 0; j < i; ++j) {
                    sum += (lmx[k][j] * umx[j][i]);
                }
                // Evaluating L(k, i)
                lmx[k][i] = (mx[k][i] - sum) / umx[i][i];
            }
        }
    }
}

void lud::crout(mtx_t mx, mtx_t lmx, mtx_t umx, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        lmx[i][i] = 1;
    }
    for (size_t k = 0; k < size; ++k) {
        umx[k][k] = mx[k][k];
        for (size_t i = k + 1; i < size; ++i) {
            lmx[i][k] = mx[i][k] / umx[k][k];
            umx[k][i] = mx[k][i];
        }
        for (size_t i = k + 1; i < size; ++i) {
            for (size_t j = k + 1; j < size; ++j) {
                mx[i][j] = mx[i][j] - lmx[i][k] * umx[k][j];
            }
        }
    }
}

void lud::crout_mp(mtx_t mx, mtx_t lmx, mtx_t umx, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        lmx[i][i] = 1;
    }
    for (size_t k = 0; k < size; ++k) {
        umx[k][k] = mx[k][k];
        for (size_t i = k + 1; i < size; ++i) {
            lmx[i][k] = mx[i][k] / umx[k][k];
            umx[k][i] = mx[k][i];
        }
        #pragma omp parallel for
        for (size_t i = k + 1; i < size; ++i) {
            for (size_t j = k + 1; j < size; ++j) {
                mx[i][j] = mx[i][j] - lmx[i][k] * umx[k][j];
            }
        }
    }
}
