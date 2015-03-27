#include <cmath>
#include <cstdlib>
#include <iostream>
#include "bmp_hdlr.h"

const double PI = std::acos(-1);

int canvas_r[bmp_size][bmp_size], canvas_g[bmp_size][bmp_size], canvas_b[bmp_size][bmp_size];

int main() {
  std::srand(1126);
  for (int t = 0; t < 100; ++t) {
    int oy = rand() % bmp_size, ox = rand() % bmp_size;
    int radius = rand() % 80, wave = rand() % 10 + 5;

    // amount of change for radius
    // int var = rand() % 10 + 1;
    int var = rand() % 12 + 8;

    // Color; `%50` will be brighter
    int r = rand() % 30, g = rand() % 30, b = rand() % 30;

    // Though these will cut the figure at edges, the result is fine
    for (int y = std::max(0, oy-radius); y <= std::min(bmp_size-1, oy+radius); ++y) {
      for (int x = std::max(0, ox-radius); x <= std::min(bmp_size-1, ox+radius); ++x) {
        double theta = std::atan2(y-oy, x-ox) * wave;
        double changed_radius = std::sin(theta)*radius/var + radius;

        int dist2 = (y-oy)*(y-oy) + (x-ox)*(x-ox);
        if (dist2 <= changed_radius*changed_radius) {
          canvas_r[y][x] += r;
          canvas_g[y][x] += g;
          canvas_b[y][x] += b;
        }
      }
    }
  }
  return 0;
}
