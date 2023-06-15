#include <openssl/aes.h>
#include <openssl/rand.h>
#include <iostream>
#include <string>

std::string aes_decrypt(const std::string& ciphertext, const std::string& key) {
    AES_KEY aes_key;
    std::string plaintext;

    // Set up the decryption key
    if (AES_set_decrypt_key(reinterpret_cast<const unsigned char*>(key.data()), 256, &aes_key) < 0) {
        std::cerr << "Error setting up AES decryption key." << std::endl;
        return plaintext;
    }

    // Perform decryption
    size_t ciphertext_len = ciphertext.size();
    unsigned char decrypted_block[AES_BLOCK_SIZE];
    for (size_t i = 0; i < ciphertext_len; i += AES_BLOCK_SIZE) {
        AES_decrypt(reinterpret_cast<const unsigned char*>(&ciphertext[i]), decrypted_block, &aes_key);
        plaintext.append(reinterpret_cast<char*>(decrypted_block), AES_BLOCK_SIZE);
    }

    // Remove PKCS7 padding
    unsigned char padding_byte = plaintext.back();
    size_t padding_size = static_cast<size_t>(padding_byte);
    plaintext.resize(plaintext.size() - padding_size);

    return plaintext;
}

int main() {
    // The ciphertext and key generated in Python
    std::string ciphertext = "\xd7\x7a\xe3\x67\x39\x10\x7b\x0a\xf2\x3d\xa0\xbb\x5c\x83\x98\xe2";
    std::string key = "\x01\x23\x45\x67\x89\xab\xcd\xef\xfe\xdc\xba\x98\x76\x54\x32\x10"
                      "\x01\x23\x45\x67\x89\xab\xcd\xef\xfe\xdc\xba\x98\x76\x54\x32\x10";

    // Perform decryption
    std::string plaintext = aes_decrypt(ciphertext, key);

    // Display the decrypted plaintext
    std::cout << "Decrypted plaintext: " << plaintext << std::endl;

    return 0;
}