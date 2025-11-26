import itertools
import string
import time
def brute_force_simulation(target_password):
    chars = string.ascii_letters + string.digits + string.punctuation
    attempts = 0
    start_time = time.time()
    print(f"Target Password: {target_password}")
    print(f"Character Set: {chars}")
    print("Starting simulation... (Press Ctrl+C to stop if it takes too long)\n")
    found = False
    for length in range(1, 9): 
        for guess_tuple in itertools.product(chars, repeat=length):
            attempts += 1
            guess = "".join(guess_tuple)
            if attempts % 100000 == 0:
                print(f"Attempt {attempts}: {guess}")
            if guess == target_password:
                end_time = time.time()
                duration = end_time - start_time
                print(f"\n[SUCCESS] Password found: {guess}")
                print(f"Total Attempts: {attempts}")
                print(f"Time Taken: {duration:.4f} seconds")
                return
    print("\n[FAILURE] Password not found within the length limit.")
if __name__ == "__main__":
    print("--- Brute Force Educational Simulation ---")
    print("This tool runs entirely in memory and does not interact with any network services.")
    print("Warning: Long passwords (5+ chars) may take a significant amount of time.\n")
    user_target = input("Enter a short password to simulate cracking (e.g., 'Abc!1'): ").strip()
    valid_chars = string.ascii_letters + string.digits + string.punctuation
    if not all(c in valid_chars for c in user_target):
        print("Error: The password contains characters not in the standard printable ASCII set.")
    else:
        brute_force_simulation(user_target)
