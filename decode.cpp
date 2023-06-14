#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <inttypes.h>
#include <vector>
#include "decode.h"

using namespace std;

//test passed
void inverseSubBytes(uint8_t (&cypher)[16]){
   for(int i = 0 ; i < 16 ; i++){
      cypher[i] = InverseSbox[cypher[i]]; //find the corresponding value of original data in s box
   }
   return;
}

//test passed
void inverseShiftRows(uint8_t (&cypher)[16]){
   uint8_t temp[4];
   for(int i = 0 ; i < 4 ; i++){
      for(int j = 0 ; j < 4 ; j++){
         temp[j] = cypher[i*4+j]; //store all values in the same row into temp
      }
      for(int j = 0 ; j < 4 ; j++){
         cypher[i*4+j] = temp[(j-i+4)%4]; //right shift by row amount
      }
   }
   return;
}

void inverseMixColumn(uint8_t (&cypher)[16]) {
    // Multiply matrix by constant matrix
    uint8_t tempCol1[4];
    uint8_t tempCol2[4];
    uint8_t tempCol3[4];
    uint8_t tempCol4[4];
    for(int i = 0 ; i < 4 ; i++){
        for(int j = 0 ; j < 4 ; j++){
            if(j == 0){
                tempCol1[i] = cypher[i*4+j];
            } else if(j == 1){
                tempCol2[i] = cypher[i*4+j];
            } else if(j == 2){
                tempCol3[i] = cypher[i*4+j];
            } else{
                tempCol4[i] = cypher[i*4+j];
            }
        }
    }
    invMixColumn(tempCol1);
    invMixColumn(tempCol2);
    invMixColumn(tempCol3);
    invMixColumn(tempCol4);
    for(int i = 0 ; i < 4 ; i++){
        for(int j = 0 ; j < 4 ; j++){
            if(j == 0){
                cypher[i*4+j] = tempCol1[i];
            } else if(j == 1){
                cypher[i*4+j] = tempCol2[i];
            } else if(j == 2){
                cypher[i*4+j] = tempCol3[i];
            } else{
                cypher[i*4+j] = tempCol4[i];
            }
        }
    }
   return;
}

/**
 * Helper function to multiply two bytes
 **/ 
void invMixColumn(uint8_t (&r)[4]) {
   uint8_t a[4];
   uint8_t b[4];
   uint8_t d[4];
   uint8_t e[4];
   uint8_t f[4];
   uint8_t h;
    /* The array 'a' is simply a copy of the input array 'r'
     * The array 'b' is each element of the array 'a' multiplied by 9
     * in Rijndael's Galois field
     * The array 'd' is each element of the array 'a' multiplied by 11
     * in Rijndael's Galois field
     * The array 'e' is each element of the array 'a' multiplied by 13
     * in Rijndael's Galois field
     * The array 'f' is each element of the array 'a' multiplied by 14
     * in Rijndael's Galois field */ 

/* 
inverse mix column matrix
0E 0B 0D 09
09 0E 0B 0D
0D 09 0E 0B
0B 0D 09 0E

09: (((x*2)*2)*2)^ x
11: ((((x*2)* 2)^ x)* 2)^ x
13: ((((x*2)^ x)* 2)* 2)^ x
14: ((((x*2)^ x)* 2)^ x)* 2
*/ 

   for (int c = 0; c < 4; c++) {
      a[c] = r[c];

      // *9
      h = (r[c] >> 7) & 1; 
      b[c] = r[c] << 1; 
      b[c] ^= h * 0x1B; 
      for(int i = 0 ; i < 2 ; i++){
         h = (b[c] >> 7) & 1; 
         b[c] = b[c] << 1; 
         b[c] ^= h * 0x1B; 
      }
      b[c] = r[c] ^ b[c];

      // *11
      h = (r[c] >> 7) & 1; 
      d[c] = r[c] << 1; 
      d[c] ^= h * 0x1B; 

      h = (d[c] >> 7) & 1; 
      d[c] = d[c] << 1; 
      d[c] ^= h * 0x1B;

      d[c] = r[c] ^ d[c]; 

      h = (d[c] >> 7) & 1; 
      d[c] = d[c] << 1; 
      d[c] ^= h * 0x1B;

      d[c] = r[c] ^ d[c]; 

      // *13
      h = (r[c] >> 7) & 1; 
      e[c] = r[c] << 1; 
      e[c] ^= h * 0x1B; 

      e[c] = r[c] ^ e[c]; 

      h = (e[c] >> 7) & 1; 
      e[c] = e[c] << 1; 
      e[c] ^= h * 0x1B;

      h = (e[c] >> 7) & 1; 
      e[c] = e[c] << 1; 
      e[c] ^= h * 0x1B;

      e[c] = r[c] ^ e[c]; 

      // *14
      h = (r[c] >> 7) & 1; 
      f[c] = r[c] << 1; 
      f[c] ^= h * 0x1B; 

      f[c] = r[c] ^ f[c]; 

      h = (f[c] >> 7) & 1; 
      f[c] = f[c] << 1; 
      f[c] ^= h * 0x1B;

      f[c] = r[c] ^ f[c]; 

      h = (f[c] >> 7) & 1; 
      f[c] = f[c] << 1; 
      f[c] ^= h * 0x1B;
   }

   r[0] = f[0] ^ d[1] ^ e[2] ^ b[3]; // 14*a0 + 11*a1 + 13*a2 + 9*a3
   r[1] = b[0] ^ f[1] ^ d[2] ^ e[3]; // 9*a0 + 14*a1 + 11*a2 + 13*a3
   r[2] = e[0] ^ b[1] ^ f[2] ^ d[3]; // 13*a0 + 9*a1 + 14*a2 + 11*a3
   r[3] = d[0] ^ e[1] ^ b[2] ^ f[3]; // 11*a0 + 13*a1 + 9*a2 + 14*a3
}


void inverseAddRoundKey(uint8_t (&cypher)[16], uint8_t roundKey[16]){
   for(int i = 0 ; i < 16 ; i++){
      cypher[i] = cypher[i] ^ roundKey[i]; //XOR every bit of original data with the key
   }
   return;
}

void aes256Decoding(uint8_t *cypher, int fileLength, uint8_t key[32]){
    //check if the file is successfully padded
    if(fileLength %16 != 0){
        printf("Error! File is not successfully padded!\n");
        return;
    }

    //each key is of length 16 bytes (128 bits) and there are 15 such keys
    //the below if statement is mainly for saving resources occupied by tempRoundKeys
    //might have a better way to do so
    roundKeysStruct roundKeys[15];
    //generate roundkey first
    if(1){
        uint8_t tempRoundKeys[16][15];
        generateRoundKey(tempRoundKeys,key);
        for(int i = 0 ; i < 15 ; i++){
            for(int j = 0 ; j < 16 ; j++){
                roundKeys[i].data[j] = tempRoundKeys[j][i];
            }
        }
    }

    //perform 14 rounds in total
    for(int i = 13 ; i >= 0 ; i--){
        //loop through whole file for this process
        for(int j = 0 ; j < fileLength/16 ; j++){
            uint8_t temp[16];
            //assign value to temp to pass into function
            for(int k = 0 ; k < 16 ; k++){
                temp[k] = cypher[16*j + k];
            }
            
            inverseAddRoundKey(temp,roundKeys[i+1].data);
            if(i != 13){
                inverseMixColumn(temp); // no mix column for the last round
            }
            inverseShiftRows(temp);
            inverseSubBytes(temp);
            //store the value back to original
            for(int k = 0 ; k < 16 ; k++){
                cypher[16*j + k] = temp[k];
            }
        }
    }

    //loop through whole file for this process
    for(int i = 0 ; i < fileLength/16 ; i++){
        uint8_t temp[16];
        //assign value to temp to pass into function
        for(int j = 0 ; j < 16 ; j++){
            temp[j] = cypher[16*i + j];
        }
        //perform add round key
        inverseAddRoundKey(temp,roundKeys[0].data);
        //store the value back to cypher
        for(int j = 0 ; j < 16 ; j++){
            cypher[16*i + j] = temp[j];
        }
    }

    return;
}