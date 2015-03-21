#include <iostream>
#include "bmp_hdlr.h"

int canvas_r[bmp_size][bmp_size], canvas_g[bmp_size][bmp_size], canvas_b[bmp_size][bmp_size];

// YCbCr http://en.wikipedia.org/wiki/YCbCr#JPEG_conversion
int main() {
  for (int i = 0; i < bmp_size; ++i) {
    for (int j = 0; j < bmp_size; ++j) {
      int y = (299*canvas_r[i][j] + 587*canvas_g[i][j] + 114*canvas_b[i][j])/1000;
      canvas_r[i][j] = canvas_g[i][j] = canvas_b[i][j] = y;
    }
  }
  return 0;
}
