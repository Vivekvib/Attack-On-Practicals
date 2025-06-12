import sys

# Combine all command line arguments into a single string
if len(sys.argv) < 2:
    print("Usage: python alphabet_frequency.py <your text here>")
    sys.exit(1)

text = " ".join(sys.argv[1:])  # Join arguments into a single string

# Convert to lowercase to count case-insensitively
text = text.lower()

# Create a dictionary to store frequency of each alphabet
frequency = {}

for char in text:
    if char.isalpha():  # Only consider alphabets
        frequency[char] = frequency.get(char, 0) + 1

# Print the results
print("Alphabet Frequency Table")
print("------------------------")
print("Letter\tCount")
for letter in sorted(frequency):
    print(f"{letter}\t{frequency[letter]}")
