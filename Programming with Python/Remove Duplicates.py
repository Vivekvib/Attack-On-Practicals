# Function to remove duplicates from a list
def remove_duplicates(arr):
    unique_list = []
    for item in arr:
        if item not in unique_list:
            unique_list.append(item)
    return unique_list

# Input: Read a list from the user
input_str = input("Enter the array elements separated by spaces: ")
arr = input_str.split()  # Creates a list of strings

# Optional: Convert to integers if needed
arr = [int(x) for x in arr]

# Remove duplicates
unique_arr = remove_duplicates(arr)

# Output the result
print("Array after removing duplicates:", unique_arr)
