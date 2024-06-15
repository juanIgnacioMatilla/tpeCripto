#include "./mode_algo.h"
#include "../bmp_manager/bmp.h"
#include <stdint.h>

bmp_image open_carrier(char * carrier);

void write_output(char* output, uint8_t * data, size_t size, char * extension){
    // char * filename = calloc(1,strlen(output)+1));
    // strcat(filename,strtok(output,"."));
    // strcat(filename,extension);
    FILE * output_file = fopen(output,"w");
    fwrite(data,1,size,output_file);
    fclose(output_file);
}


void embed(uint8_t* input,uint32_t input_data_size,char* carrier,char* output, stego_lsb_algo stego_strategy_fn){
    bmp_image image_carrier = open_carrier(carrier);
    uint8_t * image_data = get_image_data(image_carrier);
    uint32_t image_data_size = get_image_size(image_carrier);
    stego_strategy_fn(image_data,image_data_size,(uint8_t**)&input,&input_data_size);
    FILE* output_file = fopen(output,"w");
    write_image(image_carrier,output_file);
    fclose(output_file);
    free_image(image_carrier);
}
void extract(uint8_t* input, uint32_t input_data_size,char* carrier,char* output, stego_lsb_algo stego_strategy_fn){
    bmp_image image_carrier = open_carrier(carrier);
    uint8_t * image_data = get_image_data(image_carrier);
    uint32_t image_data_size = get_image_size(image_carrier);
    uint8_t * hide_data = NULL;
    uint32_t hide_size =0;
    stego_strategy_fn(image_data,image_data_size,(uint8_t **)&hide_data,&hide_size);
    uint32_t data_size = be32toh(((uint32_t*)hide_data)[0]);
    uint8_t*data = hide_data + sizeof(uint32_t);
    char * extension = (char *) hide_data + sizeof(uint32_t) + data_size;
    write_output(output,data,data_size,extension);
    free(hide_data);
    free_image(image_carrier);
}




bmp_image open_carrier(char * carrier){
    FILE * carrier_file = fopen(carrier,"r");
    bmp_image image = read_image(carrier_file);
    fclose(carrier_file);
    return image;
}


