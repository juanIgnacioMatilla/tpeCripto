#ifndef CRYPTO_ALGO_G
#define CRYPTO_ALGO_G
#include "../crypto_config/crypto_config.h"
unsigned char * encrypt(unsigned char * plaintext, uint32_t plaintext_len, char * password, uint32_t * output_len, crypto_algo_strategy crypto_algo_fn);
unsigned char * decrypt(unsigned char * ciphertext , uint32_t ciphertext_len, char * password, uint32_t * output_len, crypto_algo_strategy crypto_algo_fn);
#endif