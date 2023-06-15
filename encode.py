import os
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.primitives import padding

def encode_func(text, key):
    # IV is temporary a set
    # iv = os.urandom(16)
    iv = b'\x00' * 16
    # print("IV: ", iv)
    cipher = Cipher(algorithms.AES(key), modes.CBC(iv))
    encryptor = cipher.encryptor()

    # Pad plaintext
    padder = padding.PKCS7(128).padder()
    padded_data = padder.update(text) + padder.finalize()
    # print("Padded:", padded_data)
    ciphertext = iv + encryptor.update(padded_data) + encryptor.finalize()
    return ciphertext



