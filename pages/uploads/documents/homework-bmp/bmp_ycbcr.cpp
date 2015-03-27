#include <iostream>
#include "bmp_hdlr.h"

int canvas_r[bmp_size][bmp_size], canvas_g[bmp_size][bmp_size], canvas_b[bmp_size][bmp_size];

int y[bmp_size][bmp_size], cb[bmp_size][bmp_size], cr[bmp_size][bmp_size];

int main() {
  // Convert RGB to YCbCr
  for (int i = 0; i < bmp_size; ++i) {
    for (int j = 0; j < bmp_size; ++j) {
      int r = canvas_r[i][j], g = canvas_g[i][j], b = canvas_b[i][j];

      y[i][j] = (299*r + 587*g + 114*b)/1000;
      cb[i][j] = 128 + (-168736*r - 331264*g + 500000*b)/1000000;
      cr[i][j] = 128 + ( 500000*r - 418688*g -  81312*b)/1000000;
    }
  }

  // First part: only show Y
  for (int i = 0; i < bmp_size; ++i) {
    for (int j = 0; j < bmp_size/3; ++j) {
      cr[i][j] = 128;
      cb[i][j] = 128;
    }
  }

  // Second part: only show Cb
  for (int i = 0; i < bmp_size; ++i) {
    for (int j = bmp_size/3; j < bmp_size - bmp_size/3; ++j) {
      y[i][j] = 0;
      cr[i][j] = 128;
    }
  }

  // Third part: only show Cr
  for (int i = 0; i < bmp_size; ++i) {
    for (int j = bmp_size - bmp_size/3; j < bmp_size; ++j) {
      y[i][j] = 0;
      cb[i][j] = 128;
    }
  }

  // Convert YCbCr back to RGB

  for (int i = 0; i < bmp_size; ++i) {
    for (int j = 0; j < bmp_size; ++j) {
      canvas_r[i][j] = y[i][j] + 1402*(cr[i][j] - 128)/1000;
      canvas_g[i][j] = y[i][j] + (-34414*(cb[i][j] - 128) - 71414*(cr[i][j] - 128))/100000;
      canvas_b[i][j] = y[i][j] + 1772*(cb[i][j] - 128)/1000;
    }
  }
  return 0;
}
