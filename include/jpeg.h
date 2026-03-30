#ifndef __H_JPEG__
#define __H_JPEG__

#include <stdint.h>
#include <stddef.h>

typedef struct {

  // brightness percentage
  int16_t brightness;

  // color code lookup table is initialized?
  int16_t color_table_initialized;
  
  // Static arrays instead of pointers to avoid malloc overhead
  // These will be placed wherever the JPEG instance is allocated (e.g., High Memory)
  uint16_t rgb555_r[256];
  uint16_t rgb555_g[256];
  uint16_t rgb555_b[256];

} JPEG;

void jpeg_crtmod_768x512_65536();
void jpeg_fill_text_masks();
void jpeg_open_text_masks();

int32_t jpeg_open(JPEG* jpeg, int16_t brightness);
void jpeg_close(JPEG* jpeg);
int32_t jpeg_draw(JPEG* jpeg, uint8_t* buffer, size_t size, int16_t scale_mode);

#endif