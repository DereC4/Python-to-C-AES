#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <inttypes.h>
#include <vector>
#include "decode.h"
#include "encode.h"
using namespace std;

int main(){

   int fileLength;
   int numRound = 14;

   //get the data in toEncode.txt as string
   std::ifstream in("toEncode.txt");
   std::string contents_string((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());

   //get file size
   fileLength = contents_string.size();
   printf("original file length is: %d\n",fileLength);

   //convert string to uint8_t
   std::vector<uint8_t> tempVector(contents_string.begin(), contents_string.end());
   uint8_t *contents_char_arr = &tempVector[0];

   //pad the data to multiple of 16 with ' '
   for(int i = 0 ; i < 16 - fileLength%16 ; i++){
      contents_char_arr[fileLength+i] = ' ';
   }

   //update file length
   fileLength = fileLength + 16 - fileLength%16;
   printf("padded file length is: %d\n",fileLength);

   //========================== test code for file conversion ======================================
   printf("Converted file in characters are: \n");
   for(int i = 0 ; i < fileLength ; i++){
      printf("%c",contents_char_arr[i]);
   }
   printf("\nConverted file in hex are: \n\n");

   //print out data in hex & in blocks
   for(int i = 0 ; i < fileLength ; i++){
      printf("%x ",contents_char_arr[i]);
      if(i%4 == 3){
         printf("\n");
      }
      if(i%16 == 15){
         printf("\n");
      }
   }
   //========================== test code for file conversion ends ======================================

   //========================== test code for row shifting ======================================
   uint8_t temp[16];
   for(int i = 0 ; i < 16 ; i++){
      temp[i] = contents_char_arr[i];
   }

   printf("Original first block: \n\n");
   for(int i = 0 ; i < 16 ; i++){
      printf("%x ",contents_char_arr[i]);
      if(i % 4 == 3){
         printf("\n");
      }
   }
   printf("\n");

   printf("First block after row-shifting: \n\n");
   shiftRows(temp);
   for(int i = 0 ; i < 16 ; i++){
      printf("%x ",temp[i]);
      if(i % 4 == 3){
         printf("\n");
      }
   }
   printf("\n");
   //========================== test code for row shifting ends ======================================

   //========================== test code for byte substitution ======================================
   for(int i = 0 ; i < 16 ; i++){
      temp[i] = contents_char_arr[i];
   }

   printf("Original first block: \n\n");
   for(int i = 0 ; i < 16 ; i++){
      printf("%x ",contents_char_arr[i]);
      if(i % 4 == 3){
         printf("\n");
      }
   }
   printf("\n");

   subBytes(temp);
   printf("First block after Sub-byting: \n\n");
   for(int i = 0 ; i < 16 ; i++){
      printf("%x ",temp[i]);
      if(i % 4 == 3){
         printf("\n");
      }
   }
   printf("\n");
   //========================== test code for byte substitution ends ======================================

   //========================== test code for generate Round key ======================================

   printf("Generating Keys\n");
   uint8_t tempRoundKeys[16][15];
   uint8_t key[32] = {
      0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
      0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
      0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
      0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f};
   generateRoundKey(tempRoundKeys, key);
   for (int i = 0; i < 15; i++)
   {
      for (int j = 0; j < 16; j++) {
         printf("%x ", tempRoundKeys[j][i]); 
      }
      printf("\n");
   }
   //========================== test code for generate Round key ends ======================================

   //========================== test code for add Round key ======================================

   //========================== test code for add Round key ends ======================================

   //========================== test code for mix column ======================================

   uint8_t textForMixColumn[16] = {0x87, 0xF2, 0x4D, 0x97,
                                   0x6E, 0x4C, 0x90, 0xEC,
                                   0x46, 0xE7, 0x4A, 0xC3,
                                   0xA6, 0x8C, 0xD8, 0x95};

   printf("Original first block: \n\n");
   for(int i = 0 ; i < 16 ; i++){
      printf("%x ",textForMixColumn[i]);
      if(i % 4 == 3){
         printf("\n");
      }
   }
   printf("\n");

   printf("First block after column mixing: \n\n");
   mixColumn(textForMixColumn);
   for(int i = 0 ; i < 16 ; i++){
      printf("%x ",textForMixColumn[i]);
      if(i % 4 == 3){
         printf("\n");
      }
   }
   printf("\n");
   //========================== test code for mix column ends ======================================

   //========================== test code for inverse row shifting ======================================
   for(int i = 0 ; i < 16 ; i++){
      temp[i] = contents_char_arr[i];
   }
   printf("Original first block: \n\n");
   for(int i = 0 ; i < 16 ; i++){
      printf("%x ",contents_char_arr[i]);
      if(i % 4 == 3){
         printf("\n");
      }
   }
   printf("\n");

   printf("First block after row-shifting and inverse row-shifting: \n\n");
   shiftRows(temp);
   inverseShiftRows(temp);
   for(int i = 0 ; i < 16 ; i++){
      printf("%x ",temp[i]);
      if(i % 4 == 3){
         printf("\n");
      }
   }
   printf("\n");
   //========================== test code for inverse row shifting ends ======================================

   //========================== test code for inverse byte substitution ======================================
   for(int i = 0 ; i < 16 ; i++){
      temp[i] = contents_char_arr[i];
   }

   printf("Original first block: \n\n");
   for(int i = 0 ; i < 16 ; i++){
      printf("%x ",contents_char_arr[i]);
      if(i % 4 == 3){
         printf("\n");
      }
   }
   printf("\n");

   subBytes(temp);
   inverseSubBytes(temp);
   printf("First block after byte substitution and inverse byte substitution: \n\n");
   for(int i = 0 ; i < 16 ; i++){
      printf("%x ",temp[i]);
      if(i % 4 == 3){
         printf("\n");
      }
   }
   printf("\n");
   //========================== test code for inverse byte substitution ends ======================================

   //========================== test code for inverse mix column ======================================
    uint8_t reverseMixText[16] = {0x87, 0xF2, 0x4D, 0x97,
                                   0x6E, 0x4C, 0x90, 0xEC,
                                   0x46, 0xE7, 0x4A, 0xC3,
                                   0xA6, 0x8C, 0xD8, 0x95};

   printf("Original first block: \n\n");
   for(int i = 0 ; i < 16 ; i++) {
      printf("%x ",reverseMixText[i]);
      if(i % 4 == 3) {
         printf("\n");
      }
   }
   printf("\n");

   printf("First block after column mixing: \n\n");
   mixColumn(reverseMixText);
   for(int i = 0 ; i < 16 ; i++) {
      printf("%x ",reverseMixText[i]);
      if(i % 4 == 3) {
         printf("\n");
      }
   }

    printf("First block after reverse mixing: \n\n");
    inverseMixColumn(reverseMixText);
    for(int i = 0 ; i < 16 ; i++) {
        printf("%x ",reverseMixText[i]);
        if(i % 4 == 3) {
            printf("\n");
        }
    }
   printf("\n");
   //========================== test code for inverse mix column ends ======================================

   //========================== test code for inverse add Round key ======================================

   //========================== test code for inverse add Round key ends ======================================
   return 0;
}
