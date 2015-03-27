#include <iostream>
#include "bmp_hdlr.h"

int canvas_r[bmp_size][bmp_size], canvas_g[bmp_size][bmp_size], canvas_b[bmp_size][bmp_size];

int quant = 64;

int ys[bmp_size][bmp_size];

// http://en.wikipedia.org/wiki/Error_diffusion
int diffuse_div = 48, diffuse[3][5] = {
  {0, 0, 0, 7, 5},
  {3, 5, 7, 5, 3},
  {1, 3, 5, 3, 1}
};

int main() {
  // Process only the 'y' component
  for (int i = 0; i < bmp_size; ++i) {
    for (int j = 0; j < bmp_size; ++j) {
      int r = canvas_r[i][j], g = canvas_g[i][j], b = canvas_b[i][j];
      ys[i][j] = (299*r + 587*g + 114*b)/1000;
    }
  }

  // Quantization and error duffusion
  for (int i = 0; i < bmp_size; ++i) {
    for (int j = 0; j < bmp_size; ++j) {
      int base = ys[i][j]/quant * quant;
      int res = ys[i][j] - base; // Remainder

      ys[i][j] = base;

      // Diffuse the error
      for (int di = 0; di < 2; ++di) {
        for (int dj = -2; dj <= 2; ++dj) {
          int ti = i + di, tj = j + dj;
          if (0<=ti && ti<bmp_size && 0<=tj && tj<bmp_size) {
            ys[ti][tj] = (ys[ti][tj]*diffuse_div + res*diffuse[di][dj+2])/diffuse_div;
          }
        }
      }
    }
  }

  // Output the result
  for (int i = 0; i < bmp_size; ++i) {
    for (int j = 0; j < bmp_size; ++j) {
      canvas_r[i][j] = ys[i][j];
      canvas_g[i][j] = ys[i][j];
      canvas_b[i][j] = ys[i][j];
    }
  }
  return 0;
}
