import encode
import decode

key = b'\x01\x23\x45\x67\x89\xab\xcd\xef\xfe\xdc\xba\x98\x76\x54\x32\x10' \
      b'\x01\x23\x45\x67\x89\xab\xcd\xef\xfe\xdc\xba\x98\x76\x54\x32\x10'
plaintext = b'Hello World'

print("Plaintext:", plaintext)
ciphertext = encode.encode_func(plaintext, key)
print("Ciphertext:", ciphertext)
decrypted_text = decode.decode_func(ciphertext, key)
print("Decrypted Text:", decrypted_text)