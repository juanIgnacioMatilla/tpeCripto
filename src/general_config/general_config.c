#include "./general_config.h"
#include "../stego_config/stego_config.h"
#include "../crypto_config/crypto_config.h"
#include <endian.h>
#define BLOCK_SIZE 256
typedef struct general_config{
    stego_cfg stego;
    crypto_cfg crypto;
    char* input;
    char* carrier;
    char* output;
} general_config;
static uint8_t * get_hide_data(uint8_t * file_data, uint32_t file_data_size, char * file_extension, uint32_t * embed_size);
void read_data(FILE* input_file,uint32_t*input_data_size,uint8_t * output);
void write_output(char* output, uint8_t * data, size_t size, char * extension);

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

void run_config(general_cfg config, int mode){
    uint32_t input_data_size;
    uint8_t * input_data;
    uint32_t hide_data_size;
        uint8_t * hide_data;
    switch (mode)
    {
    case EMBED:
        input_data_size = 0;
        input_data = calloc(1, BLOCK_SIZE);
        FILE* input_file = fopen(config->input,"r");
        int read = -1;
        char * buffer[BLOCK_SIZE];
    
        while(read !=0){
            read = fread(buffer,1,BLOCK_SIZE,input_file);
            if(input_data_size % BLOCK_SIZE == 0){
                input_data = realloc(input_data,input_data_size+BLOCK_SIZE);
            }
           memcpy(input_data+input_data_size,buffer,read);
           input_data_size+=read;
        }
        input_data = realloc(input_data,input_data_size);
        fclose(input_file);
        hide_data_size = 0;
        hide_data = get_hide_data(input_data,input_data_size,strchr(config->input, '.'),&hide_data_size);
        run_stego_config(config->stego,hide_data,hide_data_size,config->output,config->carrier,config->crypto);
        free(input_data);
        break;
    
    case EXTRACT:
        hide_data = NULL;
        hide_data_size = 0;
        run_stego_config(config->stego,hide_data,hide_data_size,config->output,config->carrier,config->crypto);
        break;
    default:
        break;
    }
}


static uint8_t * get_hide_data(uint8_t * hide_data, uint32_t hide_data_size, char * hide_extension, uint32_t * embed_size) {
    *embed_size = sizeof(uint32_t) + hide_data_size + strlen(hide_extension) + 1;
    uint8_t * to_hide_data = calloc(1, *embed_size);

    uint32_t data_offset = sizeof(uint32_t);
    uint32_t extension_offset = data_offset + hide_data_size;
    
    uint32_t be_data_size = htobe32(hide_data_size);

    memcpy(to_hide_data, &be_data_size, sizeof(uint32_t));
    memcpy(to_hide_data + data_offset, hide_data, hide_data_size);
    memcpy(to_hide_data + extension_offset, hide_extension, strlen(hide_extension));

    return to_hide_data;
}
