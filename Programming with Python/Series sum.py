import sys
# Function to compute the series sum
def compute_series(n):
    total = 0
    for i in range(1, n + 1):
        term = 1 / (i ** i)
        if i % 2 == 0:
            total -= term
        else:
            total += term
    return total
# Check for command-line argument
if len(sys.argv) > 1:
    try:
        n = int(sys.argv[1])
    except ValueError:
        print("Please enter a valid integer for n.")
        sys.exit(1)
else:
    # If not provided via command-line, prompt the user
    try:
        n = int(input("Enter the number of terms (n): "))
    except ValueError:
        print("Invalid input. Please enter a valid integer.")
        sys.exit(1)
# Compute and display the result
result = compute_series(n)
print(f"The sum of the series up to {n} terms is: {result:.6f}")


### How to Run:
-> With command-line argument:
    python series_sum.py 5
-> Without argument (interactive mode):
 python series_sum.py
