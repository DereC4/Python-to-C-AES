import os
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.primitives import padding

def encode_func(text, key):
    iv = os.urandom(16)
    cipher = Cipher(algorithms.AES256(key), modes.CBC(iv))
    encryptor = cipher.encryptor()

    padder = padding.PKCS7(256).padder()
    padded_data = padder.update(text) + padder.finalize()
    print("Padded:", padded_data)
    ciphertext = encryptor.update(padded_data) + encryptor.finalize()
    return ciphertext



