#ifndef STEGO_CONFIG_H
#define STEGO_CONFIG_H

#include <stdint.h>
#include "../cli_parser/cli_parser.h"


typedef void (*stego_lsb_algo) (uint8_t *, uint32_t, uint8_t **, uint32_t *);
typedef void (*stego_mode_algo) (char* input, char* carrier, char* output, stego_lsb_algo lsb_algo);

typedef struct stego_config * stego_cfg;

void set_stego_mode(stego_cfg cfg, int mode);
void set_stego_lsb(stego_cfg cfg, char* lsb, int mode);

#endif