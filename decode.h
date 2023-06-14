#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <inttypes.h>
#include <vector>
#include "inverse_sbox.h"
#include "roundkey.h"

using namespace std;

void inverseSubBytes(uint8_t (&cypher)[16]); //inverse byte substitution

void inverseShiftRows(uint8_t (&cypher)[16]); //inverse row shifting

void inverseMixColumn(uint8_t (&cypher)[16]); //inverse column mixing

void inverseAddRoundKey(uint8_t (&cypher)[16], uint8_t roundKey[16]); //inverse round key adding

//decode the whole file, assume file length is already padded to multiple of 16
void aes256Decoding(uint8_t *cypher, int fileLength, uint8_t key[32]); 

//inverse mix column helper function
void invMixColumn(uint8_t (&r)[4]);