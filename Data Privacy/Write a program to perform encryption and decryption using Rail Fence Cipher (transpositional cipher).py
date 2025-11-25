def rail_fence_cipher(text, key, mode):
    if key <= 1:
        return text
    if mode == 'encrypt':
        rails = [''] * key
        current_rail = 0
        direction = 1  # 1 for down, -1 for up
        for char in text:
            rails[current_rail] += char
            if current_rail == 0:
                direction = 1
            elif current_rail == key - 1:
                direction = -1
            current_rail += direction
        return "".join(rails)
    elif mode == 'decrypt':
        text_len = len(text)
        rail_lengths = [0] * key
        current_rail = 0
        direction = 1
        for _ in range(text_len):
            rail_lengths[current_rail] += 1
            if current_rail == 0:
                direction = 1
            elif current_rail == key - 1:
                direction = -1
            current_rail += direction
        rails = []
        cipher_index = 0
        for length in rail_lengths:
            # Take the correct slice from the cipher text for the current rail
            rail_slice = text[cipher_index : cipher_index + length]
            rails.append(list(rail_slice)) # Convert string to list of chars
            cipher_index += length
        result = []
        current_rail = 0
        direction = 1
        for _ in range(text_len):
            # Pop the first character from the current rail's list
            result.append(rails[current_rail].pop(0))        
            # Move to the next rail
            if current_rail == 0:
                direction = 1
            elif current_rail == key - 1:
                direction = -1
            current_rail += direction            
        return "".join(result)
def main():
    print("Rail Fence Cipher Program")
    print("-------------------------")
    while True:
        choice = input("Do you want to (e)ncrypt or (d)ecrypt? (e/d): ").lower()
        if choice in ['e', 'd']:
            break
        else:
            print("Invalid choice. Please enter 'e' or 'd'.")
    message = input("Enter your message: ")
    while True:
        try:
            key = int(input("Enter the number of rails (e.g., 3): "))
            if key > 1:
                break
            else:
                print("Number of rails must be greater than 1.")
        except ValueError:
            print("Invalid input. Please enter a whole number.")
    if choice == 'e':
        encrypted_message = rail_fence_cipher(message, key, 'encrypt')
        print("\n--- Encryption ---")
        print(f"Original Message:  {message}")
        print(f"Encrypted Message: {encrypted_message}")
    else:
        decrypted_message = rail_fence_cipher(message, key, 'decrypt')
        print("\n--- Decryption ---")
        print(f"Original Message:  {message}")
        print(f"Decrypted Message: {decrypted_message}")
if __name__ == "__main__":
    main()

