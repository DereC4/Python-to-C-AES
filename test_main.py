import encode
import decode

fileLength = 0;
numRound = 14;
key = b'ThisIsASecretKeyForAES256'
plaintext = b'This is a secret message'

ciphertext = encode.encode_func(plaintext, key)
decrypted_text = decode.decode_func(ciphertext, key)

print("Plaintext:", plaintext)
print("Ciphertext:", ciphertext)
print("Decrypted Text:", decrypted_text)