import random
def load_words(file_path):
    valid_words = []
    try:
        with open(file_path, 'r') as f:
            for line in f:
                word = line.strip().lower()
                if word.isalpha() and len(word) >= 4:
                    valid_words.append(word)
        return valid_words
    except (FileNotFoundError, IOError):
        return []
def create_fallback_dictionary(filename="words.txt"):
    sample_words = [
        "apple", "brave", "cactus", "cloud", "dragon", "eagle", "forest", "giant",
        "house", "indigo", "jungle", "karma", "lemon", "mango", "noble", "ocean",
        "piano", "quiet", "river", "solar", "tiger", "unity", "violet", "water",
        "xenon", "yellow", "zebra", "battery", "horse", "staple", "correct"
    ]
    try:
        with open(filename, 'w') as f:
            f.write("\n".join(sample_words))
        print(f"[Info] Created local dictionary file: {filename}")
        return filename
    except IOError as e:
        print(f"[Error] Could not create fallback dictionary: {e}")
        return None

def generate_password(word_list, num_words=4, separator="-"):
    if not word_list:
        return None
    secure_rng = random.SystemRandom()
    chosen_words = [secure_rng.choice(word_list) for _ in range(num_words)]
    return separator.join(chosen_words)
if __name__ == "__main__":
    print("--- Dictionary-Based Password Generator ---")
    candidate_paths = [
        "/usr/share/dict/words",
        "/usr/dict/words",
        "words.txt" # Local fallback
    ]    
    words = []
    for path in candidate_paths:
        loaded_words = load_words(path)
        if loaded_words:
            words = loaded_words
            print(f"[Info] Successfully loaded words from: {path}")
            break
    if not words:
        print("[Info] No system dictionary found.")
        fallback_path = create_fallback_dictionary()
        if fallback_path:
             words = load_words(fallback_path)
    if words:
        print(f"[Info] {len(words)} suitable words loaded.")
        while True:
            password = generate_password(words)
            print(f"\nGenerated Password: {password}")
            user_input = input("Generate another? (Y/n): ").strip().lower()
            if user_input == 'n':
                break
    else:
        print("[Error] Could not locate or create a dictionary file.")
