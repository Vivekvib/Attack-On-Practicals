class MatrixDimensionError(Exception):
    """Custom exception for incompatible matrix dimensions"""
    pass

class Matrix:
    def __init__(self, rows):
        self.rows = rows
        self.m = len(rows)
        self.n = len(rows[0]) if rows else 0

    def __str__(self):
        return "\n".join(["\t".join(map(str, row)) for row in self.rows])

    def add(self, other):
        if self.m != other.m or self.n != other.n:
            raise MatrixDimensionError("Matrices must have the same dimensions to add.")
        
        result = []
        for i in range(self.m):
            result_row = []
            for j in range(self.n):
                result_row.append(self.rows[i][j] + other.rows[i][j])
            result.append(result_row)
        return Matrix(result)

    def multiply(self, other):
        if self.n != other.m:
            raise MatrixDimensionError("Columns of first matrix must equal rows of second matrix to multiply.")
        
        result = []
        for i in range(self.m):
            result_row = []
            for j in range(other.n):
                val = 0
                for k in range(self.n):
                    val += self.rows[i][k] * other.rows[k][j]
                result_row.append(val)
            result.append(result_row)
        return Matrix(result)

    def transpose(self):
        result = []
        for i in range(self.n):
            result_row = []
            for j in range(self.m):
                result_row.append(self.rows[j][i])
            result.append(result_row)
        return Matrix(result)

# Utility to read a matrix
def read_matrix(name):
    rows = int(input(f"Enter number of rows for {name}: "))
    cols = int(input(f"Enter number of columns for {name}: "))
    print(f"Enter elements row-wise for {name}:")
    matrix = []
    for i in range(rows):
        row = list(map(int, input(f"Row {i+1}: ").split()))
        while len(row) != cols:
            print(f"Row must have {cols} elements. Try again.")
            row = list(map(int, input(f"Row {i+1}: ").split()))
        matrix.append(row)
    return Matrix(matrix)

# Menu-driven interface
def main():
    print("\n--- Matrix Operations ---")
    while True:
        print("\nChoose an option:")
        print("a. Add two matrices")
        print("b. Multiply two matrices")
        print("c. Transpose a matrix")
        print("d. Exit")

        choice = input("Enter your choice (a-d): ").lower()

        try:
            if choice == 'a':
                m1 = read_matrix("Matrix 1")
                m2 = read_matrix("Matrix 2")
                result = m1.add(m2)
                print("\nResult of Addition:")
                print(result)

            elif choice == 'b':
                m1 = read_matrix("Matrix 1")
                m2 = read_matrix("Matrix 2")
                result = m1.multiply(m2)
                print("\nResult of Multiplication:")
                print(result)

            elif choice == 'c':
                m = read_matrix("Matrix")
                result = m.transpose()
                print("\nTranspose of Matrix:")
                print(result)

            elif choice == 'd':
                print("Exiting the program.")
                break

            else:
                print("Invalid choice. Please select from a to d.")

        except MatrixDimensionError as e:
            print(f"Error: {e}")
        except ValueError:
            print("Please enter valid integers only.")
        except Exception as e:
            print(f"Unexpected error: {e}")

if __name__ == "__main__":
    main()
