#include <cmath>
#include <cstdlib>
#include <iostream>
#include "bmp_hdlr.h"

double PI = std::acos(-1);

int canvas_r[bmp_size][bmp_size], canvas_g[bmp_size][bmp_size], canvas_b[bmp_size][bmp_size];

int main() {
  std::srand(1126);

  for (int k = 0; k < 10; ++k) {
    int cy, cx;
    int radius = rand()%200 + 100;
    {
      int ty = std::rand() % bmp_size;
      int tx = std::rand() % bmp_size;
      double dir = (std::rand() % 360)*PI/180.0;
      cx = (int)(tx + std::cos(dir)*radius);
      cy = (int)(ty + std::sin(dir)*radius);
    }
    int r = std::rand()%50, g = std::rand()%50, b = std::rand()%50;
    for (int y = 0; y < bmp_size; ++y) {
      for (int x = 0; x < bmp_size; ++x) {
        int dist2 = (x-cx)*(x-cx) + (y-cy)*(y-cy);
        if (dist2 <= radius*radius) {
          canvas_r[y][x] += r;
          canvas_g[y][x] += g;
          canvas_b[y][x] += b;
        }
      }
    }
  }
  return 0;
}
