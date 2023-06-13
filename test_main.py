import encode
import decode
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.primitives import padding

### Test 1

key = b'\x01\x23\x45\x67\x89\xab\xcd\xef\xfe\xdc\xba\x98\x76\x54\x32\x10' \
      b'\x01\x23\x45\x67\x89\xab\xcd\xef\xfe\xdc\xba\x98\x76\x54\x32\x10'
plain_text = b'Your next line is...'

print("Plaintext:", plain_text)
cipher_text = encode.encode_func(plain_text, key)
print("Ciphertext:", cipher_text)

# Open the file in write mode
with open("cipher.txt", "wb") as file:
    file.write(cipher_text)
print("Cipher text saved to file.")
decrypted_text = decode.decode_func(cipher_text, key)
print("Decrypted Text:", decrypted_text)
