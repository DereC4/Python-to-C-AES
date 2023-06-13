import encode
import decode
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.primitives import padding

### Test 1

key = b'\x01\x23\x45\x67\x89\xab\xcd\xef\xfe\xdc\xba\x98\x76\x54\x32\x10' \
      b'\x01\x23\x45\x67\x89\xab\xcd\xef\xfe\xdc\xba\x98\x76\x54\x32\x10'
plaintext = b'Your next line is...'

print("Plaintext:", plaintext)
ciphertext = encode.encode_func(plaintext, key)
print("Ciphertext:", ciphertext)
decrypted_text = decode.decode_func(ciphertext, key)
print("Decrypted Text:", decrypted_text)
