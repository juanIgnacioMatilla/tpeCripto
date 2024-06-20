#include "./crypto_config.h"
#include <openssl/evp.h>
#include "../algorithms/crypto_algo.h"
#include <string.h>

typedef struct crypto_config{
    crypto_algo_strategy strategy;
    crypto_function fn;
    char * password;
} crypto_config;

static crypto_algo_strategy evp_cypto_fns[4][4] = {
    {EVP_aes_128_ecb,   EVP_aes_128_cfb8,   EVP_aes_128_ofb,    EVP_aes_128_cbc},
    {EVP_aes_192_ecb,   EVP_aes_192_cfb8,   EVP_aes_192_ofb,    EVP_aes_192_cbc},
    {EVP_aes_256_ecb,   EVP_aes_256_cfb8,   EVP_aes_256_ofb,    EVP_aes_256_cbc},
    {EVP_des_ede3_ecb,  EVP_des_ede3_cfb8,  EVP_des_ede3_ofb,   EVP_des_ede3_cbc}
};

typedef enum {
    aes128 = 0,
    aes192,
    aes256,
    des
} CRYPTO_ALGO;

typedef enum {
    ecb = 0,
    cfb,
    ofb,
    cbc
} CRYPTO_ALGO_MODE;

void set_crypto_function(crypto_cfg config, int mode);
void set_crypto_strategy(crypto_cfg config,char *algo_crypto, char*algo_mode);

crypto_cfg create_crypto_config(opts options){
    if(get_password(options) == NULL){
        return NULL;
    }
    crypto_cfg config = calloc(1,sizeof(crypto_config));
    config->password = get_password(options);
    set_crypto_strategy(config,get_enc_algo(options),get_enc_mode(options));
    set_crypto_function(config,get_mode(options));
    return config;
}

unsigned char* run_cripto_config(crypto_cfg config, unsigned char* input,uint32_t input_size , uint32_t * output_size ){
    return config->fn(input,input_size,config->password,output_size,config->strategy);
}

void free_crypto_config(crypto_cfg config){
    free(config);
}

void set_crypto_function(crypto_cfg config, int mode){
    switch (mode){
        case EMBED:
            config->fn = encrypt;
            break;
        case EXTRACT:
            config->fn = decrypt;
            break;
        default:
            printf("Invalid encryption mode\n");
    }
}

void set_crypto_strategy(crypto_cfg config,char *algo_crypto, char*algo_mode){
    CRYPTO_ALGO crypto_algo;
    CRYPTO_ALGO_MODE crypto_algo_mode;
    if(algo_crypto == NULL){
        crypto_algo = aes128;
    }else if (strcmp(algo_crypto, "aes128") == 0) {
        crypto_algo = aes128;
    }  else if (strcmp(algo_crypto, "aes192") == 0) {
        crypto_algo = aes192;
    } else if (strcmp(algo_crypto, "aes256") == 0) {
        crypto_algo = aes256;
    } else if (strcmp(algo_crypto, "des") == 0) {
        crypto_algo = des;
    } else {
        printf("Not valid cryptography algorithm. Using default AES128.\n");
        crypto_algo = aes128;
    }

    if(algo_mode == NULL){
        crypto_algo_mode = cbc;
    }else if (strcmp(algo_mode, "ecb") == 0) {
        crypto_algo_mode = ecb;
    } else if (strcmp(algo_mode, "cfb") == 0) {
        crypto_algo_mode = cfb;
    } else if (strcmp(algo_mode, "ofb") == 0) {
        crypto_algo_mode = ofb;
    } else if (strcmp(algo_mode, "cbc") == 0) {
        crypto_algo_mode = cbc;
    } else {
        printf("Not valid cryptography mode. Using default CBC.\n");
        crypto_algo = cbc;
    }

    config->strategy = evp_cypto_fns[crypto_algo][crypto_algo_mode];

}