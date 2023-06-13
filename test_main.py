import encode
import decode

key = b'ThisIsASecretKeyForAES256'
plaintext = b'Hello World'

print("Plaintext:", plaintext)
ciphertext = encode.encode_func(plaintext, key)
print("Ciphertext:", ciphertext)
decrypted_text = decode.decode_func(ciphertext, key)
print("Decrypted Text:", decrypted_text)