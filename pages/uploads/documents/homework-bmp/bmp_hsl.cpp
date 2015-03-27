#include <cmath>
#include <iostream>
#include "bmp_hdlr.h"

int canvas_r[bmp_size][bmp_size], canvas_g[bmp_size][bmp_size], canvas_b[bmp_size][bmp_size];

int H[bmp_size][bmp_size], S[bmp_size][bmp_size], L[bmp_size][bmp_size];

int main() {
  // convert RGB to HSL
  for (int i = 0; i < bmp_size; ++i) {
    for (int j = 0; j < bmp_size; ++j) {
      int r = canvas_r[i][j], g = canvas_g[i][j], b = canvas_b[i][j];

      double rf = r/255.0, gf = g/255.0, bf = b/255.0;
      double cmax = std::max(std::max(r, g), b)/255.0;
      double cmin = std::min(std::min(r, g), b)/255.0;
      double C = cmax - cmin;
      double Lf = (cmax + cmin)/2.0;
      double Sf = (r==g && g==b)? 0 : C/(1 - std::abs(2*Lf - 1));
      double Hf;
      if (r==g && g==b) Hf = 0;
      else if (r>=g && r>=b) Hf = 60*((gf-bf)/C - std::floor((gf-bf)/C/6.0)*6.0); // x mod n = x - floor(x/n)*n
      else if (g>=r && g>=b) Hf = 60*((bf-rf)/C + 2);
      else if (b>=r && b>=g) Hf = 60*((rf-gf)/C + 4);

      H[i][j] = (int)Hf;
      L[i][j] = (int)(Lf*100.0);
      S[i][j] = (int)(Sf*100.0);
    }
  }

  // the first part: change to the opposite color
  for (int i = 0; i < bmp_size; ++i)
    for (int j = 0; j < bmp_size/3; ++j)
      H[i][j] = (H[i][j]+180)%360;

  // the second part: increase lightness
  for (int i = 0; i < bmp_size; ++i)
    for (int j = bmp_size/3; j < bmp_size - bmp_size/3; ++j)
      L[i][j] = std::min(L[i][j]*3/2, 100);

  // the third part: increase saturation
  for (int i = 0; i < bmp_size; ++i)
    for (int j = bmp_size - bmp_size/3; j < bmp_size; ++j)
      S[i][j] = std::min(100, S[i][j]*3);

  // convert HSL back to RGB
  for (int i = 0; i < bmp_size; ++i) {
    for (int j = 0; j < bmp_size; ++j) {
      double Sf = S[i][j]/100.0, Lf = L[i][j]/100.0;
      double C = Sf*(1 - std::abs(2*Lf - 1));
      double X = C*(1 - std::abs(((H[i][j]/60.0) - std::floor(H[i][j]/60.0/2)*2) - 1));
      double m = Lf - C/2;
      double rf = 0.0, gf = 0.0, bf = 0.0;
      if      (0<=H[i][j] && H[i][j]<60)    { rf = C; gf = X; }
      else if (60<=H[i][j] && H[i][j]<120)  { rf = X; gf = C; }
      else if (120<=H[i][j] && H[i][j]<180) { gf = C; bf = X; }
      else if (180<=H[i][j] && H[i][j]<240) { gf = X; bf = C; }
      else if (240<=H[i][j] && H[i][j]<300) { rf = X; bf = C; }
      else if (300<=H[i][j] && H[i][j]<360) { rf = C; bf = X; }

      canvas_r[i][j] = (int)(256.0*(rf + m));
      canvas_g[i][j] = (int)(256.0*(gf + m));
      canvas_b[i][j] = (int)(256.0*(bf + m));
    }
  }
  return 0;
}
