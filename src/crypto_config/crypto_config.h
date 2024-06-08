#ifndef CRYPTO_CONFIG_G
#define CRYPTO_CONFIG_G
#include <openssl/evp.h>
#include "../cli_parser/cli_parser.h"
typedef const EVP_CIPHER * (* crypto_algo_strategy)();

typedef struct crypto_config* crypto_cfg;
typedef unsigned char * (* crypto_function) (unsigned char * ciphertext , uint32_t ciphertext_len, char * password, uint32_t * output_len, crypto_algo_strategy crypto_algo_fn);
crypto_cfg create_crypto_config(opts options);
void free_crypto_config(crypto_cfg config);
#endif