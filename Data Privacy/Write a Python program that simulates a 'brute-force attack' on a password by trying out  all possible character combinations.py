import itertools, string

# The password we are trying to find
target = "abc" 

# Character set to check (Letters, digits, punctuation)
chars = string.ascii_letters + string.digits + string.punctuation

# Iterate through lengths (1 character, then 2, etc.)
for length in range(1, 9):
    # Generate all possible combinations of that length
    for guess in itertools.product(chars, repeat=length):
        guess_str = "".join(guess)
        if guess_str == target:
            print(f"Password found: {guess_str}")
            exit()
