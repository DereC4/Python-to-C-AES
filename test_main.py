import encode
import decode
import secrets

key = secrets.token_bytes(32)  # 32 bytes = 256 bits

print(key)
plaintext = b'Hello World'
print("Plaintext:", plaintext)
ciphertext = encode.encode_func(plaintext, key)
print("Ciphertext:", ciphertext)
decrypted_text = decode.decode_func(ciphertext, key)
print("Decrypted Text:", decrypted_text)