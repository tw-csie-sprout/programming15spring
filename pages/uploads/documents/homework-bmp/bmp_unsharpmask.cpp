#include <cstring>
#include <iostream>
#include "bmp_hdlr.h"

int canvas_r[bmp_size][bmp_size], canvas_g[bmp_size][bmp_size], canvas_b[bmp_size][bmp_size];

int y[bmp_size][bmp_size], cb[bmp_size][bmp_size], cr[bmp_size][bmp_size];
double buf_y[bmp_size][bmp_size];

int main() {
  int diff = 5;
  double scale = 0.5;

  // Only apply unsharp mask to the luminance component
  for (int i = 0; i < bmp_size; ++i) {
    for (int j = 0; j < bmp_size; ++j) {
      y[i][j] = (299*canvas_r[i][j] + 587*canvas_g[i][j] + 114*canvas_b[i][j])/1000;
      cb[i][j] = 128 + (-168736*canvas_r[i][j] - 331264*canvas_g[i][j] + 500000*canvas_b[i][j])/1000000;
      cr[i][j] = 128 + ( 500000*canvas_r[i][j] - 418688*canvas_g[i][j] -  81312*canvas_b[i][j])/1000000;
    }
  }

  // blur the image (y => buf_y)
  for (int i = 0; i < bmp_size; ++i) {
    for (int j = 0; j < bmp_size; ++j) {
      int cnt = 0;
      for (int di = -diff; di <= diff; ++di) {
        for (int dj = -diff; dj <= diff; ++dj) {
          int ti = i + di, tj = j + dj;
          if (0<=ti && ti<bmp_size && 0<=tj && tj<bmp_size) {
            buf_y[i][j] += y[ti][tj];
            ++cnt;
          }
        }
      }
      buf_y[i][j] /= cnt;
    }
  }

  // Calculate the originate 'brightness' (just simply use its energy..)
  double energy_in = 0;
  for (int i = 0; i < bmp_size; ++i)
    for (int j = 0; j < bmp_size; ++j)
      energy_in += y[i][j];

  // Mask the blurred image (buf_y => buf_y)
  for (int i = 0; i < bmp_size; ++i)
    for (int j = 0; j < bmp_size; ++j)
      buf_y[i][j] = y[i][j] - buf_y[i][j]*scale;

  // Calculate the remaining energy in `buf_y`
  double energy_out = 0;
  for (int i = 0; i < bmp_size; ++i)
    for (int j = 0; j < bmp_size; ++j)
      energy_out += buf_y[i][j];

  // Scale the 'brightness' back (buf_y => y)
  for (int i = 0; i < bmp_size; ++i)
    for (int j = 0; j < bmp_size; ++j)
      y[i][j] = (int)(buf_y[i][j]*energy_in/energy_out);

  // Converting YCbCr back to RGB
  for (int i = 0; i < bmp_size; ++i) {
    for (int j = 0; j < bmp_size; ++j) {
      canvas_r[i][j] = y[i][j] + 1402*(cr[i][j] - 128)/1000;
      canvas_g[i][j] = y[i][j] + (-34414*(cb[i][j] - 128) - 71414*(cr[i][j] - 128))/100000;
      canvas_b[i][j] = y[i][j] + 1772*(cb[i][j] - 128)/1000;
    }
  }
  return 0;
}
