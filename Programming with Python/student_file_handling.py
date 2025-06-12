import pickle

# Define the Student class
class Student:
    def __init__(self, roll_no, name, student_class, year, total_marks):
        self.roll_no = roll_no
        self.name = name
        self.student_class = student_class
        self.year = year
        self.total_marks = total_marks

    def display(self):
        print(f"Roll No: {self.roll_no}, Name: {self.name}, Class: {self.student_class}, Year: {self.year}, Total Marks: {self.total_marks}")
# Step 1: Create and store 5 student objects in a file
def write_students_to_file(filename):
    students = []
    for i in range(5):
        print(f"\nEnter details for Student {i+1}:")
        roll_no = int(input("Roll No: "))
        name = input("Name: ")
        student_class = input("Class: ")
        year = int(input("Year: "))
        total_marks = float(input("Total Marks: "))
        s = Student(roll_no, name, student_class, year, total_marks)
        students.append(s)

    with open(filename, 'wb') as f:
        pickle.dump(students, f)
    print("\nStudent records written to file successfully.")
# Step 2: Read and display the student records from the file
def read_students_from_file(filename):
    try:
        with open(filename, 'rb') as f:
            students = pickle.load(f)
            print("\nStudent Records Retrieved from File:\n")
            for s in students:
                s.display()
    except FileNotFoundError:
        print("File not found!")
    except Exception as e:
        print("Error reading from file:", e)
# Main function
def main():
    filename = "students.dat"
    write_students_to_file(filename)
    read_students_from_file(filename)
if __name__ == "__main__":
    main()
