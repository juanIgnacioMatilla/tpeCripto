#include "./crypto_algo.h"
#include <string.h>

#define MAX_SIZE 64 * 1024 * 1024

void ustrncpy(unsigned char *dest, const unsigned char *src, size_t n) {
  for (size_t i = 0; i < n; i++) {
      dest[i] = src[i];
      if (src[i] == '\0')
          break;  // Stop copying if null terminator encountered
  }
}


unsigned char * encrypt(unsigned char * plaintext, uint32_t plaintext_len, char * password, uint32_t * output_len, crypto_algo_strategy crypto_algo_fn){
    unsigned char * key;
    unsigned char * iv;
    int len;
    
    EVP_CIPHER_CTX * ctx = EVP_CIPHER_CTX_new();
    unsigned char keylen = EVP_CIPHER_key_length(crypto_algo_fn());
    unsigned char ivlen = EVP_CIPHER_iv_length(crypto_algo_fn());
    unsigned char out[keylen+ivlen];
    PKCS5_PBKDF2_HMAC(password,strlen(password),NULL,0,10000, EVP_sha256(), keylen+ivlen, out);
    key = malloc(keylen);
    ustrncpy(key,out,keylen);
    if(ivlen != 0){
      iv = malloc(ivlen);
      ustrncpy(iv,out+keylen,ivlen);
    }
    
    if(EVP_EncryptInit_ex(ctx,crypto_algo_fn(),NULL,key,iv) != 1){
      printf("Error during encryption init\n");
    }

    unsigned char * output = calloc(1,MAX_SIZE);
    
    if(EVP_EncryptUpdate(ctx,output,&len,plaintext,plaintext_len) != 1){
      printf("EVP Encrypt Update failed\n");
    }
    
    *output_len = len;
    
    if(EVP_EncryptFinal_ex(ctx,output+len,&len) != 1){
      printf("Error EVP FInal Encrypt\n");
    }

    *output_len =+ len;
    EVP_CIPHER_CTX_free(ctx);
    free(key); 
    free(iv);
    return output;
}

unsigned char * decrypt(unsigned char * ciphertext , uint32_t ciphertext_len, char * password, uint32_t * output_len, crypto_algo_strategy crypto_algo_fn){
    unsigned char  * key;
    unsigned char * iv;
    int len;
    
    EVP_CIPHER_CTX * ctx = EVP_CIPHER_CTX_new();
    unsigned char keylen = EVP_CIPHER_key_length(crypto_algo_fn());
    unsigned char ivlen = EVP_CIPHER_iv_length(crypto_algo_fn());
    unsigned char out[keylen+ivlen];
    PKCS5_PBKDF2_HMAC(password,strlen(password),NULL,0,10000, EVP_sha256(), keylen+ivlen, out);
    key = malloc(keylen);
    ustrncpy(key,out,keylen);
    if(ivlen != 0){
      iv = malloc(ivlen);
      ustrncpy(iv,out+keylen,ivlen);
    }
    
    if(EVP_DecryptInit_ex(ctx,crypto_algo_fn(),NULL,key,iv) != 1){
      printf("Error during Decryption init\n");
    }

    unsigned char * output = calloc(1,MAX_SIZE);
    
    if(EVP_DecryptUpdate(ctx,output,&len,ciphertext,ciphertext_len) != 1){
      printf("EVP Encrypt Update failed\n");
    }
    
    *output_len = len;
    
    if(EVP_DecryptFinal_ex(ctx,output+len,&len) != 1){
      printf("Error EVP FInal Encrypt\n");
    }

    *output_len =+ len;
    EVP_CIPHER_CTX_free(ctx);
    return output;
}
