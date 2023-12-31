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
void aes_256_decrypt(unsigned char *ciphertext, int cipher_len, unsigned char *key, unsigned char *iv, unsigned char *plaintext, int payload_size) {
    AES_KEY aes_key;
    int len;
    int padding; 

    // AES_set_decrypt_key(key, 256, &aes_key);
    // AES_cbc_encrypt(ciphertext, plaintext, AES_BLOCK_SIZE, &aes_key, iv, AES_DECRYPT);
    
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_CIPHER_CTX_set_padding(ctx, 1);
    EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);
    EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, cipher_len);
    EVP_DecryptFinal_ex(ctx, plaintext + len, &len);
    EVP_CIPHER_CTX_free(ctx);   
    printf("Before null terminator text: %s\n", plaintext);
    plaintext[payload_size] = '\0';
}

int main() {

    // Get first line (file size), then read the rest of the cipher in
    std::ifstream file("output/cipher.txt", std::ios::in | std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return 1;
    }
    std::string temp;
    std::getline(file, temp);
    // std::cout << "Payload Size: " << temp << std::endl;
    int payload_size = std::stoi(temp);
    printf("Payload Size: %d\n", payload_size);

    // Get file length
    // uint8_t begin = file.tellg();
    // file.seekg (0, std::ios::end);
    // uint8_t end = file.tellg();
    // uint8_t file_size = (end-begin);
    // file.seekg(0, std::ios::beg);
    // std::getline(file, temp);
    // printf("Filesize: %d\n", file_size);
        // Collect file contents into a character array
    // Get the length of the file

    // Read the remaining file contents into a vector<char>
    std::vector<char> data(
        (std::istreambuf_iterator<char>(file)),
        (std::istreambuf_iterator<char>())
    );

    // Convert the vector<char> to a char array
    char* cipher_text = data.data();
    size_t dataSize = data.size();
    printf("%s\n", cipher_text);
    printf("%d\n", dataSize);

    // Read in file. Padding should now be taken care of
    // unsigned char ciphertext[file_size];
    // file.read((char *) ciphertext, file_size);
    // file.close();

    unsigned char key[32]= { 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF,
                    0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10,
                    0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF,
                    0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10};
    unsigned char plaintext[payload_size];
    uint8_t iv[16];
    for (int i = 0; i < 16; i++) {
        iv[i] = 0;
    }

    aes_256_decrypt((unsigned char*)cipher_text, (int) dataSize, key, iv, plaintext, payload_size);

    // /* Show the decrypted text */
    printf("Decrypted text: %s\n", plaintext);
    return 0;
}