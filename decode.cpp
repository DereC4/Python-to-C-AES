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


/**
 * @brief Removes PKCS7 padding from the decrypted text
 * 
 * @param decrypted_text 
 * @param text_length 
 * @return int 
 */
int remove_padding(unsigned char* decrypted_text, int text_length) {
    int padding = decrypted_text[text_length - 1];
    int new_length = text_length - padding;
    return new_length;
}

unsigned char* readInCipher() {
    std::ifstream file("cipher.txt", std::ios::binary);
    if (!file) {
        std::cerr << "Failed to open file: " << "cipher.txt" << std::endl;
        return nullptr;
    }

    // Get the file size
    file.seekg(0, std::ios::end);
    size_t file_size = static_cast<size_t>(file.tellg());
    file.seekg(0, std::ios::beg);

    uint8_t file_array[file_size];

    if (!file.read(reinterpret_cast<char*>(file_array), file_size)) {
        std::cerr << "Failed to read file: " << "cipher.txt" << std::endl;
        delete[] file_array;
        return nullptr;
    }
    return file_array;
}

int main() {
    unsigned char* ciphertext = readInCipher(); 
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