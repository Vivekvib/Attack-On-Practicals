import secrets  # Use secrets for cryptographically strong random numbers
import string
import os
DEFAULT_WORDS = [
    "apple", "banana", "coffee", "dragon", "emerald", "forest",
    "guitar", "hammer", "island", "jacket", "koala", "lemon",
    "mountain", "ninja", "ocean", "pencil", "quartz", "robot",
    "spider", "tiger", "umbrella", "violin", "wizard", "xenon",
    "yellow", "zebra"
]
def load_word_list(dictionary_path="/usr/share/dict/words"):
    word_list = []
    if os.path.exists(dictionary_path):
        try:
            with open(dictionary_path, 'r') as f:
                words_from_file = [line.strip() for line in f]
                word_list = [
                    word.lower() for word in words_from_file
                    if 4 <= len(word) <= 8 and word.isalpha()
                ]
            if len(word_list) < 100:
                print(f"Warning: Dictionary at {dictionary_path} was small or unsuitable. Using default list.")
                word_list = DEFAULT_WORDS
        except IOError as e:
            print(f"Error reading {dictionary_path}: {e}. Using default list.")
            word_list = DEFAULT_WORDS
        except Exception as e:
            print(f"An unexpected error occurred: {e}. Using default list.")
            word_list = DEFAULT_WORDS
    else:
        print(f"Dictionary file not found at {dictionary_path}. Using default list.")
        word_list = DEFAULT_WORDS
    return word_list
def generate_password(word_list, num_words=4, separator="-"):
    if not word_list:
        print("Error: Word list is empty. Cannot generate password.")
        return None
    chosen_words = [secrets.choice(word_list) for _ in range(num_words)]
    password = separator.join(chosen_words)
    return password
def generate_stronger_password(word_list, num_words=3, separator="-"):
    if not word_list:
        print("Error: Word list is empty. Cannot generate password.")
        return None
    chosen_words = [secrets.choice(word_list) for _ in range(num_words)]
    index_to_capitalize = secrets.randbelow(len(chosen_words))
    chosen_words[index_to_capitalize] = chosen_words[index_to_capitalize].capitalize()
    random_number = str(secrets.randbelow(100))
    special_char = secrets.choice(string.punctuation)
    password_parts = chosen_words + [random_number, special_char]
    secrets.SystemRandom().shuffle(password_parts)
    password = separator.join(password_parts)
    return password
if __name__ == "__main__":
    DICTIONARY_FILE_PATH = "/usr/share/dict/words"
    WORDS_IN_PASSWORD = 4
    SEPARATOR_CHAR = "-"
    print(f"Attempting to load word list from: {DICTIONARY_FILE_PATH}\n")
    words = load_word_list(DICTIONARY_FILE_PATH)
    print(f"Loaded {len(words)} suitable words into memory.\n")
    simple_password = generate_password(
        words, 
        num_words=WORDS_IN_PASSWORD, 
        separator=SEPARATOR_CHAR
    )
    if simple_password:
        print(f"Simple word-based password:")
        print(f"  {simple_password}\n")
    stronger_password = generate_stronger_password(
        words, 
        num_words=WORDS_IN_PASSWORD - 1, 
        separator=SEPARATOR_CHAR
    )
    if stronger_password:
        print(f"Stronger (XKCD-style) password:")
        print(f"  {stronger_password}\n")
