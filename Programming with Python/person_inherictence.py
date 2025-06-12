# Base class
class Person:
    def __init__(self, name):
        self.name = name

    def display(self):
        print("Name:", self.name)

# Derived class: Student
class Student(Person):
    def __init__(self, name, course, marks, year):
        super().__init__(name)
        self.course = course
        self.marks = marks
        self.year = year

    def display(self):
        print("Student Details:")
        print("Name:", self.name)
        print("Course:", self.course)
        print("Marks:", self.marks)
        print("Year:", self.year)

# Derived class: Employee
class Employee(Person):
    def __init__(self, name, department, salary):
        super().__init__(name)
        self.department = department
        self.salary = salary

    def display(self):
        print("Employee Details:")
        print("Name:", self.name)
        print("Department:", self.department)
        print("Salary:", self.salary)

# Demonstrating Runtime Polymorphism
def show_details(person_obj):
    person_obj.display()

# Main Program
if __name__ == "__main__":
    # Create objects
    s1 = Student("Vivek", "BSc CS", 89, 2025)
    e1 = Employee("Nisha", "IT", 55000)

    # Using polymorphism
    print("Using Polymorphism with Student:")
    show_details(s1)

    print("\nUsing Polymorphism with Employee:")
    show_details(e1)
