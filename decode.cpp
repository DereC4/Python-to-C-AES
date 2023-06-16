#include <openssl/aes.h>
#include <openssl/rand.h>
#include <openssl/evp.h>
#include <openssl/pkcs7.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

/**
 * @brief  Decrypts the given AES ciphertext using the provided key
 * 
 */
void aes_256_decrypt(unsigned char *ciphertext, int cipher_len, unsigned char *key, unsigned char *iv, unsigned char *plaintext) {
    AES_KEY aes_key;
    int len;
    int padding; 

    // AES_set_decrypt_key(key, 256, &aes_key);
    // AES_cbc_encrypt(ciphertext, plaintext, AES_BLOCK_SIZE, &aes_key, iv, AES_DECRYPT);
    
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);
    EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, cipher_len);
    EVP_DecryptFinal_ex(ctx, plaintext + len, &len);
    EVP_CIPHER_CTX_free(ctx);   
    plaintext[len] = '\0';
}

int main() {
    std::ifstream file("cipher.txt", std::ios::in | std::ios::binary);
    
    // Get file size
    file.seekg(0, std::ios::end);
    uint8_t file_size = file.tellg();
    file.seekg(0, std::ios::beg);

    // Read in file
    unsigned char ciphertext[file_size];
    file.read((char *) ciphertext, file_size);
    file.close();
    printf("Filesize: %d\n", file_size);

    unsigned char key[32]= { 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF,
                    0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10,
                    0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF,
                    0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10};

    unsigned char plaintext[file_size];
    uint8_t iv[16];
    for (int i = 0; i < 16; i++) {
        iv[i] = 0;
    }

    aes_256_decrypt(ciphertext, (int) file_size, key, iv, plaintext);

    /* Show the decrypted text */
    printf("Decrypted text: %s\n", plaintext);
    return 0;
}