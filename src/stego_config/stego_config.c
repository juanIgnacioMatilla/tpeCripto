#include "./stego_config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../algorithms/lsb_algo.h"
#include "../algorithms/mode_algo.h"

typedef struct stego_config {
    stego_mode_algo mode_fn;
    stego_lsb_algo lsb_fn;  
} stego_config;

void set_stego_lsb(stego_cfg cfg, char* lsb, int mode);
void set_stego_mode(stego_cfg cfg, int mode);

stego_cfg create_stego_config(opts options){
    stego_cfg config = calloc(1,sizeof(stego_config));
    set_stego_lsb(config,get_stego_algo(options),get_mode(options));
    set_stego_mode(config,get_mode(options));
    return config;
}

void run_stego_config(stego_cfg config, uint8_t *input,uint32_t input_size, char* output, char* carrier){
    config->mode_fn(input,input_size,carrier,output,config->lsb_fn);
}

void free_stego_config(stego_cfg config){
    free(config);
}

void set_stego_mode(stego_cfg cfg, int mode){
    switch (mode){
    case EMBED:
        cfg->mode_fn = embed;
        break;
    
    case EXTRACT:
        cfg->mode_fn = extract;
        break;
    
    default:
        printf("Invalid stego mode\n");
    }
}

void set_stego_lsb(stego_cfg cfg, char* lsb, int mode){
    switch (mode){
    case EMBED:
        if (strcmp(lsb, "LSB1") == 0) {
            cfg->lsb_fn = lsb1_embed;
        } else if (strcmp(lsb, "LSB4") == 0) {
            cfg->lsb_fn = lsb4_embed;
        } else if (strcmp(lsb, "LSBi") == 0) {
            cfg->lsb_fn = lsbi_embed;
        } else {
            printf("Invalid LSB\n");
        }
        break;
    case EXTRACT:
        if (strcmp(lsb, "LSB1") == 0) {
            cfg->lsb_fn = lsb1_extract;
        } else if (strcmp(lsb, "LSB4") == 0) {
            cfg->lsb_fn = lsb4_extract;
        } else if (strcmp(lsb, "LSBi") == 0) {
            cfg->lsb_fn = lsbi_extract;
        } else {
            printf("Invalid LSB\n");
        }
        break;
    
    default:
        printf("Invalid stego lsb\n");
    }
}