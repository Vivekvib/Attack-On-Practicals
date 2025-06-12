def show_address(string):
    print("\nAddress of each character:")
    for i in range(len(string)):
        print(f"Character: {string[i]}, Address: {id(string[i])}")

def concatenate(str1, str2):
    result = ""
    for ch in str1:
        result += ch
    for ch in str2:
        result += ch
    return result

def compare(str1, str2):
    if len(str1) != len(str2):
        return "Strings are not equal"
    for i in range(len(str1)):
        if str1[i] != str2[i]:
            return "Strings are not equal"
    return "Strings are equal"

def string_length(string):
    count = 0
    for _ in string:
        count += 1
    return count

def to_uppercase(string):
    result = ""
    for ch in string:
        ascii_val = ord(ch)
        if 97 <= ascii_val <= 122:  # a-z
            result += chr(ascii_val - 32)
        else:
            result += ch
    return result

def reverse_string(string):
    rev = ""
    for i in range(len(string) - 1, -1, -1):
        rev += string[i]
    return rev

def insert_string(original, to_insert, pos):
    result = ""
    for i in range(pos):
        result += original[i]
    for ch in to_insert:
        result += ch
    for i in range(pos, len(original)):
        result += original[i]
    return result
  
# Main menu-driven program
while True:
    print("\n--- String Manipulation Menu ---")
    print("a) Show address of each character in string")
    print("b) Concatenate two strings")
    print("c) Compare two strings")
    print("d) Calculate length of the string")
    print("e) Convert all lowercase characters to uppercase")
    print("f) Reverse the string")
    print("g) Insert a string in another string at user-specified position")
    print("h) Exit")
    choice = input("Enter your choice (a-g): ").lower()
    if choice == 'a':
        s = input("Enter a string: ")
        show_address(s)
    elif choice == 'b':
        s1 = input("Enter first string: ")
        s2 = input("Enter second string: ")
        print("Concatenated string:", concatenate(s1, s2))
    elif choice == 'c':
        s1 = input("Enter first string: ")
        s2 = input("Enter second string: ")
        print(compare(s1, s2))
    elif choice == 'd':
        s = input("Enter a string: ")
        print("Length of the string:", string_length(s))
    elif choice == 'e':
        s = input("Enter a string: ")
        print("Uppercase string:", to_uppercase(s))
    elif choice == 'f':
        s = input("Enter a string: ")
        print("Reversed string:", reverse_string(s))
    elif choice == 'g':
        s1 = input("Enter the original string: ")
        s2 = input("Enter the string to insert: ")
        pos = int(input("Enter position to insert at (0-based index): "))
        if pos < 0 or pos > len(s1):
            print("Invalid position.")
        else:
            print("Resulting string:", insert_string(s1, s2, pos))
    elif choice == 'h':
        print("Exiting program.")
        break
    else:
        print("Invalid choice. Please try again.")
