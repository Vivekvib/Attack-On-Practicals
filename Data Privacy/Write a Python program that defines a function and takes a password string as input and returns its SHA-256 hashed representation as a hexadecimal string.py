import hashlib
def hash_password_sha256(password_string):
    sha256_hash = hashlib.sha256()
    encoded_password = password_string.encode('utf-8')
    sha256_hash.update(encoded_password)
    return sha256_hash.hexdigest()
def main():
    print("SHA-256 Password Hashing Program")
    print("--------------------------------")
    password = input("Enter the password to hash: ")
    hashed_password = hash_password_sha256(password)
    print("\n--- Hashing Result ---")
    print(f"Original Password: {password}")
    print(f"SHA-256 Hash:      {hashed_password}")
if __name__ == "__main__":
    main()

