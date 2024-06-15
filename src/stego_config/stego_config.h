#ifndef STEGO_CONFIG_H
#define STEGO_CONFIG_H

#include <stdint.h>
#include "../cli_parser/cli_parser.h"
#include "../crypto_config/crypto_config.h"

typedef void (*stego_lsb_algo) (uint8_t *, uint32_t, uint8_t **, uint32_t *);
typedef void (*stego_mode_algo) (uint8_t* input,uint32_t input_data_size, char* carrier, char* output, stego_lsb_algo lsb_algo, crypto_cfg crypto_cfg);

typedef struct stego_config * stego_cfg;
stego_cfg create_stego_config(opts options);
void free_stego_config(stego_cfg config);
void set_stego_mode(stego_cfg cfg, int mode);
void set_stego_lsb(stego_cfg cfg, char* lsb, int mode);
void run_stego_config(stego_cfg config, uint8_t *input,uint32_t input_size, char* output, char* carrier,crypto_cfg crypto_conf);
#endif
