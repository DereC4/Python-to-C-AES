#include <openssl/aes.h>
#include <openssl/rand.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

/**
 * @brief  Decrypts the given AES ciphertext using the provided key
 * 
 */
void aes_256_decrypt(unsigned char *ciphertext, unsigned char *key, unsigned char *iv, unsigned char *plaintext) {
    AES_KEY aes_key;
    AES_set_decrypt_key(key, 256, &aes_key);
    AES_cbc_encrypt(ciphertext, plaintext, AES_BLOCK_SIZE, &aes_key, iv, AES_DECRYPT);
}

int main() {
    std::ifstream file("cipher.txt", std::ios::in | std::ios::binary);
    
    // Get file size
    file.seekg(0, std::ios::end);
    uint8_t file_size = file.tellg();
    file.seekg(0, std::ios::beg);

    unsigned char ciphertext[file_size];
    file.read((char *) ciphertext, file_size);

    unsigned char key[32]= { 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF,
                    0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10,
                    0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF,
                    0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10};

    unsigned char plaintext[AES_BLOCK_SIZE];
    uint8_t iv[16];
    for (int i = 0; i < 16; i++) {
        iv[i] = 0;
    }

    aes_256_decrypt(ciphertext, key, iv, plaintext);

    /* Show the decrypted text */
    printf("Decrypted text: %s\n", plaintext);


    return 0;
}