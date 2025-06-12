# Recursive binary search function
def binary_search_recursive(arr, left, right, key):
    if left > right:
        return -1  # Key not found
    mid = (left + right) // 2
    if arr[mid] == key:
        return mid
    elif key < arr[mid]:
        return binary_search_recursive(arr, left, mid - 1, key)
    else:
        return binary_search_recursive(arr, mid + 1, right, key)

# Iterative (non-recursive) binary search
def binary_search_iterative(arr, key):
    left = 0
    right = len(arr) - 1
    while left <= right:
        mid = (left + right) // 2
        if arr[mid] == key:
            return mid
        elif key < arr[mid]:
            right = mid - 1
        else:
            left = mid + 1
    return -1  # Key not found

# Input sorted array
arr = input("Enter sorted list of numbers (space-separated): ").split()
arr = [int(x) for x in arr]

# Input key to search
key = int(input("Enter the element to search: "))

# (i) Recursive search
index_rec = binary_search_recursive(arr, 0, len(arr) - 1, key)
print(f"Recursive Binary Search: {'Found at index ' + str(index_rec) if index_rec != -1 else 'Not Found'}")

# (ii) Iterative search
index_itr = binary_search_iterative(arr, key)
print(f"Iterative Binary Search: {'Found at index ' + str(index_itr) if index_itr != -1 else 'Not Found'}")
