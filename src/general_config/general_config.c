#include "./general_config.h"
#include "../stego_config/stego_config.h"
#include "../crypto_config/crypto_config.h"
typedef struct general_config{
    stego_cfg stego;
    crypto_cfg crypto;
    char* input;
    char* carrier;
    char* output;
} general_config;

general_cfg create_general_config(opts options){
    general_cfg config = calloc(1,sizeof(general_config));
    config->input = get_input_file(options);
    config->output = get_output_file(options);
    config->carrier = get_carrier_file(options);
    config->stego = create_stego_config(options);
    config->crypto = create_crypto_config(options);
    return config;
}

void free_general_config(general_cfg config){
    free_stego_config(config->stego);
    free_crypto_config(config->crypto);
    free(config);
}