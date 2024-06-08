#ifndef MODE_ALGO_H
#define MODE_ALGO_H
#include <stdint.h>
#include "../stego_config/stego_config.h"
void embed(char* input,char* carrier,char* output, stego_lsb_algo stego_strategy_fn);
void extract(char* input,char* carrier,char* output, stego_lsb_algo stego_strategy_fn);
#endif