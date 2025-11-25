import requests
import hashlib
import sys
import time
CREDENTIALS_FILE = "credentials.txt"
API_URL = "https://api.pwnedpasswords.com/range/"
REQUEST_DELAY =1.6
def get_pwned_suffixes(hash_prefix):
    url = f"{API_URL}{hash_prefix}"
    try:
        response = requests.get(url)
        if response.status_code == 429:
            print("  [!] Rate limited. Waiting for 10 seconds...")
            time.sleep(10)
            return get_pwned_suffixes(hash_prefix) # Retry the request
        response.raise_for_status()  # Raise an exception for bad responses (4xx or 5xx)
        return response.text.splitlines()
    except requests.exceptions.RequestException as e:
        print(f"  [!] Error fetching data from API: {e}", file=sys.stderr)
        return None
def check_password_pwned(password):
    try:
        sha1_hash = hashlib.sha1(password.encode('utf-8')).hexdigest().upper()
        prefix, suffix = sha1_hash[:5], sha1_hash[5:]
        pwned_suffixes = get_pwned_suffixes(prefix)
        if pwned_suffixes is None:
            return -1 # Indicates an API error
        for line in pwned_suffixes:
            pwned_suffix, count_str = line.split(':')
            if pwned_suffix == suffix:
                count = int(count_str)
                return count
        return 0
    except Exception as e:
        print(f"  [!] Error processing password: {e}", file=sys.stderr)
        return -1 # Indicates an error
def main():
    try:
        with open(CREDENTIALS_FILE, 'r') as f:
            for line_num, line in enumerate(f, 1):
                line = line.strip()
                if not line or ',' not in line:
                    print(f"Skipping malformed line {line_num}: {line}")
                    continue
                try:
                    # Expecting "username,password" format
                    username, password = line.split(',', 1)
                    print(f"\nChecking password for user: '{username}'...")
                    password_to_check = password.strip()
                    if not password_to_check:
                         print("  [-] User has an empty password. (Skipped)")
                         continue                        
                    pwn_count = check_password_pwned(password_to_check)
                    if pwn_count > 0:
                        print(f"  [!!!] LEAKED: This password was found {pwn_count:,} times in data breaches.")
                    elif pwn_count == 0:
                        print("  [OK] Not found in data breaches.")
                    else:
                        print("  [?] Could not check password due to an API or processing error.")
                except ValueError:
                    print(f"Skipping malformed line {line_num}: {line}")
                except Exception as e:
                    print(f"An unexpected error occurred on line {line_num}: {e}", file=sys.stderr)
                time.sleep(REQUEST_DELAY)
                
    except FileNotFoundError:
        print(f"Error: Could not find the file '{CREDENTIALS_FILE}'.", file=sys.stderr)
        print("Please create this file with 'username,password' pairs.", file=sys.stderr)
    except Exception as e:
        print(f"An unexpected error occurred: {e}", file=sys.stderr)

if __name__ == "__main__":
    main()
