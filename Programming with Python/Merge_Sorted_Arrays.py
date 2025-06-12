# Function to merge two sorted arrays
def merge_sorted(arr1, arr2):
    i, j = 0, 0
    merged = []

    # Merge the arrays like the merge step in merge sort
    while i < len(arr1) and j < len(arr2):
        if arr1[i] < arr2[j]:
            merged.append(arr1[i])
            i += 1
        else:
            merged.append(arr2[j])
            j += 1

    # If elements left in arr1
    while i < len(arr1):
        merged.append(arr1[i])
        i += 1

    # If elements left in arr2
    while j < len(arr2):
        merged.append(arr2[j])
        j += 1

    return merged

# Input from the user
arr1 = input("Enter first sorted array (space-separated): ").split()
arr2 = input("Enter second sorted array (space-separated): ").split()

# Convert to integers
arr1 = [int(x) for x in arr1]
arr2 = [int(x) for x in arr2]

# Call the function and print result
merged_array = merge_sorted(arr1, arr2)
print("Merged sorted array:", merged_array)
