import os
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes

def encode_func(text, key):
    iv = os.urandom(16)
    cipher = Cipher(algorithms.AES256(key), modes.CBC(iv))
    encryptor = cipher.encryptor()
    ciphertext = encryptor.update(text) + encryptor.finalize()
    return ciphertext



