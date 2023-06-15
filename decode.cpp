#include <openssl/aes.h>
#include <openssl/rand.h>
#include <iostream>
#include <string>

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

int main() {
    const unsigned char ciphertext[32] = { 0x4F, 0x6D, 0x61, 0x65, 0x20, 0x77, 0x61, 0x20,
                            0x6D, 0x6F, 0x75, 0x20, 0x73, 0x68, 0x69, 0x6E,
                            0x84, 0x59, 0x37, 0x60, 0x05, 0x4C, 0xE5, 0xB8,
                            0xBB, 0xAE, 0xEB, 0xF7, 0x51, 0x64, 0xC1, 0xD9};
    const unsigned char key[32]= { 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF,
                    0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10,
                    0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF,
                    0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10};
    unsigned char plaintext[AES_BLOCK_SIZE];
    uint8_t iv[16];
    for (int i = 0; i < 16; i++) {
        iv[i] = 0;
    }

    /* Decrypt the ciphertext */
    uint8_t decryptedtext_len = aes_256_decrypt(ciphertext, key, iv, plaintext);

    /* Add a NULL terminator. We are expecting printable text */
    decryptedtext[decryptedtext_len] = '\0';

    /* Show the decrypted text */
    printf("Decrypted text is:\n");
    printf("%s\n", decryptedtext);

    return 0;
}