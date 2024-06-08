#ifndef LSB_ALGO_H
#define LSB_ALGO_H
#include <stdint.h>
void lsb1_embed(uint8_t * carrier, uint32_t carrier_size, uint8_t ** hide, uint32_t * hide_size);

void lsb1_extract(uint8_t * carrier, uint32_t carrier_size, uint8_t ** hidden, uint32_t * hidden_size);

void lsb4_embed(uint8_t * carrier, uint32_t carrier_size, uint8_t ** hide, uint32_t * hide_size);

void lsb4_extract(uint8_t * carrier, uint32_t carrier_size, uint8_t ** hidden, uint32_t * hidden_size);

void lsbi_embed(uint8_t * carrier, uint32_t carrier_size, uint8_t ** hide, uint32_t * hide_size);

void lsbi_extract(uint8_t * carrier, uint32_t carrier_size, uint8_t ** hidden, uint32_t* hidden_size);
#endif