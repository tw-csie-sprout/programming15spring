#pragma once

// avoid dependency of C++11 (cstdint)
#include <stdint.h>

#include <vector>
#include <iterator>
#include <fstream>
#include <algorithm>
#include <iostream>

static const int bmp_size = 300;

static const int width = bmp_size, height = bmp_size; // should use 'size_t' though
static const char *bmp_out = "sprout03_out.bmp", *bmp_in = "sprout03_in.bmp";
extern int canvas_r[height][width], canvas_g[height][width], canvas_b[height][width];

namespace {

static inline int padding4(int n) { return (n + 3)/4*4; } // should use 'size_t' instead

class Bitmap {
  // The header specialized for 24-bit BI_RGB bmp reading/writing,
  // have all uninteresting fields left blank. For complete information,
  // please see the BITMAPFILEHEADER and BITMAPINFOHEADER in windows.h
  // or consult Wikipedia.
  struct __attribute__ ((packed)) bmp_io_t {
    uint32_t size;              // total file size
    uint32_t reserveds;         // 2 2-byte reserved fields
    uint32_t offset;            // offset to the bmp data
    uint32_t header_size;       // BITMAPINFOHEADER header size, assumed to be 40
    int32_t width;
    int32_t height;
    uint16_t color_plane;       // # of color planes (must be 1)
    uint16_t bits_per_pixel;    // assumed to be 24
    uint32_t compress_method;   // must be BI_RGB, 0
    uint32_t image_size;        // the size of the raw bitmap data
    uint32_t zeroes[4];         // 4 uninteresting field, set to 0
  };
  std::fstream fout;
public:
  Bitmap() : fout(bmp_out, std::ios::out|std::ios::binary) {
    if (!fout.good()) {
      std::cerr << "Open output file '" << bmp_out << "' failed.\n";
      return;
    }
    std::fstream fin(bmp_in, std::ios::in|std::ios::binary);
    if (!fin.good()) {
      std::cerr << "Open input file '" << bmp_in << "' failed.\n";
      return;
    }

    // Ignore  error handling for now
    char B, M;
    bmp_io_t bmp_hdr;
    fin >> B >> M;
    fin.read(reinterpret_cast<char*>(&bmp_hdr), sizeof bmp_hdr);

    // handle file of size at most 50MB
    if (bmp_hdr.image_size > 50*1024*1024) {
      std::cerr << "Input file size too large: " << bmp_hdr.image_size << "\n";
      return;
    }

    fin.seekg(bmp_hdr.offset);

    const int bytes_per_pixel = bmp_hdr.bits_per_pixel/8;
    const int padded_width = padding4(bmp_hdr.width*bytes_per_pixel);

    // C++03 23.2.4.1 (continuous storage)
    std::vector<unsigned char> buf(padded_width*bmp_hdr.height);
    fin.read(reinterpret_cast<char*>(&buf.front()), padded_width*bmp_hdr.height);

    for (int i = std::max(0, height - bmp_hdr.height); i != height; ++i) {
      for (int j = 0; j != width && j != bmp_hdr.width; ++j) {
        const int pos = (height - i - 1)*padded_width + j*bytes_per_pixel; // flip the coordinate system vertically
        canvas_b[i][j] = buf[pos+0];
        canvas_g[i][j] = buf[pos+1];
        canvas_r[i][j] = buf[pos+2];
      }
    }
  }
  ~Bitmap() {
    if (!fout.good())
      return;
    const int padded_width = padding4(width*3);
    std::vector<unsigned char> buf(padded_width*height);
    for (int i = 0; i != height; ++i) {
      for (int j = 0; j != width; ++j) {
        const int pos = (height - i - 1)*padded_width + j*3; // flip the coordinate system vertically
        buf[pos+0] = static_cast<unsigned char>(std::min(255, canvas_b[i][j]));
        buf[pos+1] = static_cast<unsigned char>(std::min(255, canvas_g[i][j]));
        buf[pos+2] = static_cast<unsigned char>(std::min(255, canvas_r[i][j]));
      }
    }
    bmp_io_t bmp_hdr = {
      2 + sizeof(bmp_io_t) + height*padded_width, // file size
      0,                                          // reserved
      2 + sizeof(bmp_io_t),                       // offset
      40,                                         // header size
      width,
      height,
      1,                                          // # of color planes
      24,                                         // bits per pixel
      0,                                          // BI_RGP
      static_cast<uint32_t>(height*padded_width), // image size
      {0,0,0,0}                                   // resrerved
    };
    fout << "BM";
    fout.write(reinterpret_cast<char*>(&bmp_hdr), sizeof bmp_hdr);
    fout.write(reinterpret_cast<char*>(&buf.front()), bmp_hdr.image_size);
  }
};

static Bitmap bmp;

}
