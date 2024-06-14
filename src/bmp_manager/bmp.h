#ifndef BMP_H
#define BMP_H

#include <stdio.h>
#include <stdint.h>


typedef struct bmp_image_struct * bmp_image;


bmp_image read_image(FILE * fp);

void free_image(bmp_image image);

void write_image(bmp_image image, FILE * fp);

uint32_t get_image_size(bmp_image image);

uint8_t * get_image_data(bmp_image image);

#endif