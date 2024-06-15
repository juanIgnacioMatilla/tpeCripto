#ifndef MODE_ALGO_H
#define MODE_ALGO_H
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "../stego_config/stego_config.h"
#include "../crypto_config/crypto_config.h"
void embed(uint8_t* input,uint32_t input_data_size,char* carrier,char* output, stego_lsb_algo stego_strategy_fn,crypto_cfg crypto_conf);
void extract(uint8_t* input,uint32_t input_data_size,char* carrier,char* output, stego_lsb_algo stego_strategy_fn,crypto_cfg crypto_conf);
#endif
