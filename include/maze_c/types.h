#pragma once

typedef struct {
  int x;
  int y;
} Point;

typedef struct {
  int **grid;
  int width;
  int height;

  Point player;
  Point tracker;
  Point start;
  Point exit;
} Map;

#pragma pack(push, 1)

typedef struct {
  unsigned short bf_type;
  unsigned int bf_size;
  unsigned short bf_reserved1;
  unsigned short bf_reserved2;
  unsigned int bf_offbits;
} BitmapFileHeader;

typedef struct {
  unsigned int bi_size;
  int bi_width;
  int bi_height;
  unsigned short bi_planes;
  unsigned short bi_bit_count;
  unsigned int bi_compression;
  unsigned int bi_size_image;
  int bi_xpels_per_meter;
  int bi_ypels_per_meter;
  unsigned int bi_clr_used;
  unsigned int bi_clr_important;
} BitmapInfoHeader;

typedef struct {
  unsigned char blue;
  unsigned char green;
  unsigned char red;
  unsigned char reserved;
} ColorRGB;

#pragma pack(pop)