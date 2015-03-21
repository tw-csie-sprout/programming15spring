#include <cstring>
#include <iostream>
#include "bmp_hdlr.h"

int canvas_r[bmp_size][bmp_size], canvas_g[bmp_size][bmp_size], canvas_b[bmp_size][bmp_size];
int buf_r[bmp_size][bmp_size], buf_g[bmp_size][bmp_size], buf_b[bmp_size][bmp_size];

int main() {
  const int radius = 75;
  const int radius2 = radius*radius;
  const int cy = bmp_size/2, cx = bmp_size/2;
  for (int i = 0; i < bmp_size; ++i) {
    for (int j = 0; j < bmp_size; ++j) {
      const int dist2 = (i-cy)*(i-cy) + (j-cx)*(j-cx);
      const int diff = dist2/radius2;
      int cnt = 0;
      for (int ti = -diff; ti <= diff; ++ti) {
        for (int tj = -diff; tj <= diff; ++tj) {
          if (0 <= i+ti && i+ti < bmp_size && 0 <= j+tj && j+tj < bmp_size) {
            buf_r[i][j] += canvas_r[i+ti][j+tj];
            buf_g[i][j] += canvas_g[i+ti][j+tj];
            buf_b[i][j] += canvas_b[i+ti][j+tj];
            ++cnt;
          }
        }
      }
      buf_r[i][j] /= cnt;
      buf_g[i][j] /= cnt;
      buf_b[i][j] /= cnt;
    }
  }
  std::memcpy(canvas_r, buf_r, sizeof buf_r);
  std::memcpy(canvas_g, buf_g, sizeof buf_g);
  std::memcpy(canvas_b, buf_b, sizeof buf_b);
  return 0;
}
