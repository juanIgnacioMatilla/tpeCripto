#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define LSB1_MASK 0xFE
#define LSB1_SIZE 8
#define LSB1_OP 8

#define LSB4_MASK 0xF0 
#define LSB4_SIZE_FACTOR 2
#define LSB4_OPERATIONS 2

#define LSBI_PATTERNS 4
#define LSBI_MASK 0xFE
#define LSBI_PATTERN_MASK 0x03 
#define LSBI_SIZE_FACTOR 8
#define LSBI_OPERATIONS 8

typedef struct bit_modified{
  uint32_t changed;
  uint32_t not_changed;
} bit_modified;

//get the pattern of the byte
static uint8_t get_pattern_index(uint8_t byte) {
    return (byte & 0x06) >> 1;
}

// gets bit i from byte, beign 1 the less sig
static uint8_t get_i_bit(uint8_t byte, uint8_t i) {
    return (byte >> (i - 1)) & 1;
}
//sets less significant bit
static void set_ls_bit(uint8_t * byte, uint8_t value) {
    *byte = (*byte & LSB1_MASK) | value;
}

static uint8_t get_i_nibble(uint8_t byte, uint8_t i) {
    return (byte >> ((i - 1) * 4)) & 0xF;
}

static void set_ls_nibble(uint8_t * byte, uint8_t value) {
    *byte = (*byte & LSB4_MASK) | value;
}

void lsb1_embed(uint8_t * carrier, uint32_t carrier_size, uint8_t ** hide, uint32_t * hide_size) {
    // TODO: implement function
  
  if(*hide_size * LSB1_SIZE > carrier_size){
    printf("Error hide cannot fit in carrier\n");
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
    
    if(*hide_size * LSB4_SIZE_FACTOR > carrier_size){
    printf("Error cant fit hide in carrier\n");
  } 

    uint32_t i = 0;
    for(uint32_t j = 0; j < *hide_size; j++) {
        for(int k = LSB4_OPERATIONS; k > 0; k--) {
            uint8_t nibble = get_i_nibble((*hide)[j], k);
            set_ls_nibble(carrier + i++, nibble);
        }
    }
}

void lsb4_extract(uint8_t * carrier, uint32_t carrier_size, uint8_t ** hidden, uint32_t * hidden_size) {
    // TODO: implement function
    *hidden_size = carrier_size / LSB4_SIZE_FACTOR;

    *hidden = calloc(1, *hidden_size);

    uint8_t byte = 0;
    uint32_t hidden_iter = 0;
    for(uint32_t i = 0, j = 0; i < carrier_size; i++) {
        uint8_t nibble = get_i_nibble(carrier[i], 1);
        byte <<= 4;
        byte |= nibble;
        if(++j % LSB4_OPERATIONS == 0) {
            (*hidden)[hidden_iter++] = byte;
            byte = 0;
            j = 0;
        }
    }
}

void lsbi_embed(uint8_t * carrier, uint32_t carrier_size, uint8_t ** hide, uint32_t * hide_size) {
    // TODO: implement function
  bit_modified bits_modified[LSBI_PATTERNS];
  
  uint32_t carrier_index = 0;
    for(uint32_t j = 0; j < *hide_size; j++) {
      for(int k = LSBI_OPERATIONS; k > 0; k--) {
        if(carrier_index % 3 != 2){
          uint8_t hide_bit = get_i_bit((*hide)[j], k);
          uint8_t carrier_bit = get_i_bit(carrier[carrier_index], 1);
          uint8_t pattern_index = get_pattern_index(carrier[carrier_index++]);
          hide_bit == carrier_bit ? 
              bits_modified[pattern_index].not_changed++ : bits_modified[pattern_index].changed++; 
        }else{
            carrier_index++;
            k++;
        }
        
      }
    }

  uint8_t inversion_bits[LSBI_PATTERNS] = {0};
  //data to insert at the start of the image for bit inversion to then extract
  for(int i = 0; i < LSBI_PATTERNS;i++){
    inversion_bits[i] = bits_modified[i].changed > bits_modified[i].not_changed? 1:0; 
  }
  //setting the data of inversion
  uint32_t i = 0;
  for(uint32_t j = 0; j < LSBI_PATTERNS; j++) {
      set_ls_bit(carrier + i++, inversion_bits[j]);
  }

  for(uint32_t j = 0; j < *hide_size; j++) {
    for(int k = LSBI_OPERATIONS; k > 0; k--) {
        if( i % 3 != 2){
        uint8_t bit = get_i_bit((*hide)[j], k);
        uint8_t pattern_index = get_pattern_index(carrier[i]);
        set_ls_bit(carrier + i++, inversion_bits[pattern_index] == 1 ? !bit : bit);
      } else{
        //red byte
        i++;
        k++;
      }
    }
  }

}

void lsbi_extract(uint8_t * carrier, uint32_t carrier_size, uint8_t ** hidden, uint32_t * hidden_size) {
    // TODO: implement function
    *hidden_size = ((carrier_size - LSBI_PATTERNS) / LSBI_SIZE_FACTOR) * 2/3;
    *hidden = calloc(1, *hidden_size);

    uint8_t byte = 0;
    uint32_t hidden_iter = 0;
    uint32_t carrier_iter = 0;
    uint8_t patterns[LSBI_PATTERNS] = {0};

  for(carrier_iter = 0; carrier_iter < LSBI_PATTERNS; carrier_iter++) {
      uint8_t bit = get_i_bit(carrier[carrier_iter], 1);
      patterns[carrier_iter] = bit;
  }

  for(uint32_t j = 0; carrier_iter < carrier_size;) {
      if(carrier_iter % 3 != 2){
        uint8_t pattern_index = get_pattern_index(carrier[carrier_iter]);
        uint8_t bit = get_i_bit(carrier[carrier_iter], 1);
        if(patterns[pattern_index] == 1) {
            bit = bit == 1 ? 0 : 1;
        }
        byte <<= 1;
        byte |= bit;
        if(++j % LSBI_OPERATIONS == 0) {
            (*hidden)[hidden_iter++] = byte;
            byte = 0;
            j = 0;
        }
        carrier_iter++;
      }else{
        carrier_iter++;
      }
  }
}
