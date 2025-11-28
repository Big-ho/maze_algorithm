#pragma once

#pragma pack(push, 1)

typedef struct {
  unsigned short bf_type;
  unsigned int bf_size;
  unsigned short bf_reserved1;
  unsigned short bf_reserved2;
  unsigned int bf_offbits;
} bitmap_file_header_t;

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
} bitmap_info_header_t;

typedef struct {
  unsigned char blue;
  unsigned char green;
  unsigned char red;
  unsigned char reserved;
} rgb_quad_t;

#pragma pack(pop)

enum {
  MAX_MAZE_SIZE = 1000,
};

rgb_quad_t **load_bmp(const char *filename, int *out_height, int *out_width);
void free_bmp(rgb_quad_t **img);
rgb_quad_t **create_bmp(int height, int width);