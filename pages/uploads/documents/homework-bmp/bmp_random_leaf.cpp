#include <cmath>
#include <cstdlib>
#include <iostream>
#include "bmp_hdlr.h"

double PI = std::acos(-1);

int canvas_r[bmp_size][bmp_size], canvas_g[bmp_size][bmp_size], canvas_b[bmp_size][bmp_size];

int leaf_r[40][50], leaf_g[40][50], leaf_b[40][50];
int diag_max = 50 * 3 / 2; // roughly 50\sqrt{2}

int main() {
  std::srand(514);

  // Retain a copy of the leaf picture
  for (int y = 0; y < 40; ++y) {
    for (int x = 0; x < 50; ++x) {
      leaf_r[y][x] = canvas_r[y][x];
      leaf_g[y][x] = canvas_g[y][x];
      leaf_b[y][x] = canvas_b[y][x];
    }
  }

  // Clear canvas for the output
  for (int y = 0; y < bmp_size; ++y) {
    for (int x = 0; x < bmp_size; ++x) {
      canvas_r[y][x] = 0;
      canvas_g[y][x] = 0;
      canvas_b[y][x] = 0;
    }
  }

  for (int rnd = 0; rnd < 50; ++rnd) {
    // Darken the result from the previous round
    for (int y = 0; y < bmp_size; ++y) {
      for (int x = 0; x < bmp_size; ++x) {
        canvas_r[y][x] = canvas_r[y][x] * 2 / 3;
        canvas_g[y][x] = canvas_g[y][x] * 2 / 3;
        canvas_b[y][x] = canvas_b[y][x] * 2 / 3;
      }
    }

    // Randomly paint 15~64 leaves
    int leaves = 15 + std::rand()%50;
    for (int n = 0; n < leaves; ++n) {
      int y0 = std::rand()%bmp_size, x0 = std::rand()%bmp_size;

      // Rotate the image
      double deg = std::rand()%360*PI/180.0, scale = (std::rand()%8 + 8)/15.0;
      for (int dy = -diag_max/2; dy <= diag_max/2; ++dy) {
        for (int dx = -diag_max/2; dx < diag_max/2; ++dx) {

          // So (dx,dy) on the canvas corresponds to (x,y) of on the leaf image
          int x = 25 + static_cast<int>(( dx*std::cos(deg) + dy*std::sin(deg))/scale + 0.5);
          int y = 20 + static_cast<int>((-dx*std::sin(deg) + dy*std::cos(deg))/scale + 0.5);
          if (0<=x && x<50 && 0<=y && y<40 && 0<=y0+dy && y0+dy<bmp_size && 0<=x0+dx && x0+dx<bmp_size) {
            // Making the black background transparent
            if (leaf_r[y][x] && leaf_g[y][x] && leaf_b[y][x]) {
              canvas_r[y0+dy][x0+dx] = leaf_r[y][x];
              canvas_g[y0+dy][x0+dx] = leaf_g[y][x];
              canvas_b[y0+dy][x0+dx] = leaf_b[y][x];
            }
          }
        }
      }
    }
  }
  return 0;
}
