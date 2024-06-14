#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "./bmp.h"

#define HEADER_SIZE 54
#define BMP 0x4d42
#define NOT_COMPRESSED 0
#define BITS_PER_PIXEL 24

typedef struct __attribute__((packed)) bmp_header_struct  {             // Total: 54 bytes
  uint16_t  type;             // Magic identifier: 0x4d42
  uint32_t  size;             // File size in bytes
  uint16_t  reserved1;        // Not used
  uint16_t  reserved2;        // Not used
  uint32_t  offset;           // Offset to image data in bytes from beginning of file (54 bytes)
  uint32_t  dib_header_size;  // DIB Header size in bytes (40 bytes)
  int32_t   width_px;         // Width of the image
  int32_t   height_px;        // Height of image
  uint16_t  num_planes;       // Number of color planes
  uint16_t  bits_per_pixel;   // Bits per pixel
  uint32_t  compression;      // Compression type
  uint32_t  image_size_bytes; // Image size in bytes
  int32_t   x_resolution_ppm; // Pixels per meter
  int32_t   y_resolution_ppm; // Pixels per meter
  uint32_t  num_colors;       // Number of colors  
  uint32_t  important_colors; // Important colors 
} bmp_header_struct;

typedef struct bmp_image_struct {
    bmp_header_struct header;
    uint8_t * data;
} bmp_image_struct;


static void read_header(FILE * fp, bmp_image image);
static void read_image_data(FILE * fp, bmp_image image);
static void check_bmp_header(bmp_image image);
bmp_image read_image(FILE * fp) {    
    bmp_image image = calloc(1, sizeof(bmp_image_struct));
    if(NULL == image)
        printf("Missing bmp file\n");
    read_header(fp, image);
    check_bmp_header(image);
    read_image_data(fp, image);
    return image;
}

void free_image(bmp_image image) {
    free(image->data);
    free(image);
}

void write_image(bmp_image image, FILE * fp) {
  fwrite(&image->header, 1, HEADER_SIZE, fp);
  fwrite(image->data, 1, get_image_size(image), fp);
}

uint32_t get_image_size(bmp_image image) {
    return image->header.size - HEADER_SIZE;
}

uint8_t * get_image_data(bmp_image image) {
    return image->data;
}

static void read_header(FILE * fp, bmp_image image) {
    uint8_t raw_header[HEADER_SIZE];
    fread(&raw_header, 1, HEADER_SIZE, fp);
    memcpy(&image->header, raw_header, HEADER_SIZE);
}


static void read_image_data(FILE * fp, bmp_image image) {
    int data_size = image->header.size - HEADER_SIZE;
    image->data = malloc(data_size);
    fread(image->data, 1, data_size, fp);
}


static void check_bmp_header(bmp_image image) {
    if (BMP != image->header.type) {
        printf("Wrong image header\n");
    }
    if (NOT_COMPRESSED != image->header.compression) {
        printf("Compressed image is not valid\n");
    }
    if (BITS_PER_PIXEL != image->header.bits_per_pixel) {
        printf("Wrong pixel size per byte\n");
    }
}