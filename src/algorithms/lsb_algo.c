#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define LSB1_MASK 0xFE
#define LSB1_SIZE 8
#define LSB1_OP 8



// gets bit i from byte, beign 1 the less sig
static uint8_t get_i_bit(uint8_t byte, uint8_t i) {
    return (byte >> (i - 1)) & 1;
}
//sets less significant bit
static void set_ls_bit(uint8_t * byte, uint8_t value) {
    *byte = (*byte & LSB1_MASK) | value;
}

void lsb1_embed(uint8_t * carrier, uint32_t carrier_size, uint8_t ** hide, uint32_t * hide_size) {
    // TODO: implement function
  
  if(*hide_size * LSB1_SIZE > carrier_size){
    printf("error hide cannot fit in carrier\n");
  }

  uint32_t i = 0;

  for(uint32_t j =0; j < *hide_size; j++){
    for(int k = LSB1_OP; k > 0; k--){
      uint8_t bit = get_i_bit((*hide)[j],k);
      set_ls_bit(carrier + i++,bit);
    }
  }



}

void lsb1_extract(uint8_t * carrier, uint32_t carrier_size, uint8_t ** hidden, uint32_t * hidden_size) {
    *hidden_size = carrier_size/LSB1_SIZE;
    *hidden = calloc(1,*hidden_size);
    
    uint8_t byte = 0;
    uint32_t hidden_iter = 0;
    for(uint32_t i = 0, j = 0; i < carrier_size; i++){
    uint8_t bit = get_i_bit(carrier[i],1);
    //muevo 1 posicion para la izq todos los bits del byte
    byte <<= 1;
    //hago un or the ultimo bit para agregar el nuevo
    byte |= bit;
    if(++j % LSB1_OP == 0){
      (*hidden)[hidden_iter++] = byte;
      byte = 0;
      j = 0;
    }
  }
}

void lsb4_embed(uint8_t * carrier, uint32_t carrier_size, uint8_t ** hide, uint32_t * hide_size) {
    // TODO: implement function
}

void lsb4_extract(uint8_t * carrier, uint32_t carrier_size, uint8_t ** hidden, uint32_t * hidden_size) {
    // TODO: implement function
}

void lsbi_embed(uint8_t * carrier, uint32_t carrier_size, uint8_t ** hide, uint32_t * hide_size) {
    // TODO: implement function
}

void lsbi_extract(uint8_t * carrier, uint32_t carrier_size, uint8_t ** hidden, uint32_t * hidden_size) {
    // TODO: implement function
}
