import os
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes


def decode_func(ciphertext, key):
    cipher = Cipher(algorithms.AES(key), modes.ECB())
    decryptor = cipher.decryptor()
    plaintext = decryptor.update(ciphertext) + decryptor.finalize()
    return plaintext