import math

# Custom Exception for Invalid Triangles
class InvalidTriangleError(Exception):
    pass

class Triangle:
    def __init__(self, a, b, c):
        # Validate input
        if a <= 0 or b <= 0 or c <= 0:
            raise InvalidTriangleError("All sides must be greater than 0.")
        if a + b <= c or b + c <= a or a + c <= b:
            raise InvalidTriangleError("Sum of any two sides must be greater than the third side.")
        
        self.a = a
        self.b = b
        self.c = c

    def area(self):
        """Area using Heron's Formula"""
        s = (self.a + self.b + self.c) / 2
        area = math.sqrt(s * (s - self.a) * (s - self.b) * (s - self.c))
        return area

    def area_right_angled(self):
        """Area if triangle is right-angled — assumes two sides are base and height"""
        sides = sorted([self.a, self.b, self.c])
        if not math.isclose(sides[0]**2 + sides[1]**2, sides[2]**2, rel_tol=1e-5):
            raise InvalidTriangleError("This is not a right-angled triangle.")
        return 0.5 * sides[0] * sides[1]

    def __str__(self):
        return f"Triangle with sides: a={self.a}, b={self.b}, c={self.c}"
