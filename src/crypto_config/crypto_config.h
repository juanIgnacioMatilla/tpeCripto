#ifndef CRYPTO_CONFIG_G
#define CRYPTO_CONFIG_G
#include <openssl/evp.h>
#include "../cli_parser/cli_parser.h"
typedef const EVP_CIPHER * (* crypto_algo_strategy)();

typedef struct crypto_config* crypto_cfg;
typedef unsigned char * (* crypto_function) (unsigned char *, uint32_t, char *, uint32_t *, crypto_algo_strategy, uint32_t);

#endif