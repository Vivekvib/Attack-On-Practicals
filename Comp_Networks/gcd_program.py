# (i) Recursive GCD function using Euclidean algorithm
def gcd_recursive(a, b):
    if b == 0:
        return a
    else:
        return gcd_recursive(b, a % b)

# (ii) Iterative GCD function
def gcd_iterative(a, b):
    while b != 0:
        a, b = b, a % b
    return a

# Input two numbers from user
a = int(input("Enter first number: "))
b = int(input("Enter second number: "))

# Call both functions
gcd_rec = gcd_recursive(a, b)
gcd_itr = gcd_iterative(a, b)

# Display results
print(f"GCD (Recursive): {gcd_rec}")
print(f"GCD (Iterative): {gcd_itr}")
