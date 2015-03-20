#include <ctime>
#include <cstdlib>
#include <iostream>
#include "bmp_hdlr.h"

int canvas_r[bmp_size][bmp_size], canvas_g[bmp_size][bmp_size], canvas_b[bmp_size][bmp_size];

int main() {
  std::srand(std::time(NULL));
  const int num = 20 + rand()%10;
  for (int i = 0; i < num; ++i) {
    const int radius = rand() % 80;
    const int radius2 = radius*radius;
    const int r = rand()%50 + 10, g = rand()%50 + 10, b = rand()%50 + 10;
    const int y = rand()%bmp_size, x = rand()%bmp_size;
    for (int j = -radius; j <= +radius; ++j) {
      for (int k = -radius; k <= +radius; ++k) {
        const int ty = y + j, tx = x + k, dist2 = j*j + k*k;
        if (dist2 < radius2) {
          if (0<=ty && ty<bmp_size && 0<=tx && tx<bmp_size) {
            canvas_r[ty][tx] += r*(radius2 - dist2)/radius2;
            canvas_g[ty][tx] += g*(radius2 - dist2)/radius2;
            canvas_b[ty][tx] += b*(radius2 - dist2)/radius2;
          }
        }
      }
    }
  }
  return 0;
}
