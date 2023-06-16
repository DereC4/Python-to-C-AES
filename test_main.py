from pydoc import plain
import encode
import decode
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.primitives import padding

key = b'\x01\x23\x45\x67\x89\xab\xcd\xef\xfe\xdc\xba\x98\x76\x54\x32\x10' \
      b'\x01\x23\x45\x67\x89\xab\xcd\xef\xfe\xdc\xba\x98\x76\x54\x32\x10'
plain_text = open("toEncode", "rb").read()
cipher_text = encode.encode_func(plain_text, key)

with open("output/cipher.txt", "w") as file:
    # Write the length of the text as the first line
    file.write(str(len(plain_text)) + '\n')

# Open the file in write mode
with open("output/cipher.txt", "ab") as file:
    file.write(cipher_text)
    print("Cipher text saved to file.")

# cipher_text = open("cipher.txt", "rb").read();

decrypted_text = decode.decode_func(cipher_text, key)
with open("output/decoded", "wb") as file:
    file.write(decrypted_text)
    print("Decrypted file")
