#include <iostream>
#include <cmath>
using namespace std;

class SET {
private:
    int arr[100];
    int size;

public:
    void input(int n) {
        size = 0;
        cout << "Enter " << n << " elements:\n";
        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            if (!ismember(x)) {
                arr[size++] = x;
            }
        }
    }

    void display() const {
        cout << "{ ";
        for (int i = 0; i < size; i++) {
            cout << arr[i] << " ";
        }
        cout << "}" << endl;
    }

    bool ismember(int x) const {
        for (int i = 0; i < size; i++) {
            if (arr[i] == x) return true;
        }
        return false;
    }

    void powerset() const {
        int pow_size = pow(2, size);
        cout << "Power set:\n";
        for (int i = 0; i < pow_size; i++) {
            cout << "{ ";
            for (int j = 0; j < size; j++) {
                if (i & (1 << j))
                    cout << arr[j] << " ";
            }
            cout << "}" << endl;
        }
    }

    bool subset(const SET &other) const {
        for (int i = 0; i < size; i++) {
            if (!other.ismember(arr[i]))
                return false;
        }
        return true;
    }

    SET unionSet(const SET &other) const {
        SET result;
        result.size = 0;
        for (int i = 0; i < size; i++)
            result.arr[result.size++] = arr[i];

        for (int i = 0; i < other.size; i++) {
            if (!ismember(other.arr[i])) {
                result.arr[result.size++] = other.arr[i];
            }
        }

        return result;
    }

    SET intersectionSet(const SET &other) const {
        SET result;
        result.size = 0;

        for (int i = 0; i < size; i++) {
            if (other.ismember(arr[i])) {
                result.arr[result.size++] = arr[i];
            }
        }

        return result;
    }

    SET complement(const SET &universal) const {
        SET result;
        result.size = 0;

        for (int i = 0; i < universal.size; i++) {
            if (!ismember(universal.arr[i])) {
                result.arr[result.size++] = universal.arr[i];
            }
        }

        return result;
    }

    SET difference(const SET &other) const {
        SET result;
        result.size = 0;

        for (int i = 0; i < size; i++) {
            if (!other.ismember(arr[i])) {
                result.arr[result.size++] = arr[i];
            }
        }

        return result;
    }

    SET symmetricDifference(const SET &other) const {
        SET diff1 = this->difference(other);
        SET diff2 = other.difference(*this);
        return diff1.unionSet(diff2);
    }

    void cartesianProduct(const SET &other) const {
        cout << "Cartesian Product:\n{ ";
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < other.size; j++) {
                cout << "(" << arr[i] << "," << other.arr[j] << ") ";
            }
        }
        cout << "}" << endl;
    }
};

// -------------------------
// Main menu-driven logic
// -------------------------
int main() {
    SET A, B, U;
    int choice;

    int a_size, b_size, u_size;

    cout << "Enter size of Universal Set: ";
    cin >> u_size;
    U.input(u_size);

    cout << "Enter size of Set A: ";
    cin >> a_size;
    A.input(a_size);

    cout << "Enter size of Set B: ";
    cin >> b_size;
    B.input(b_size);

    do {
        cout << "\n----- MENU -----\n";
        cout << "1. Check membership (in A)\n";
        cout << "2. Display Power Set of A\n";
        cout << "3. Check if A is subset of B\n";
        cout << "4. Union of A and B\n";
        cout << "5. Intersection of A and B\n";
        cout << "6. Complement of A\n";
        cout << "7. Set Difference (A - B, B - A)\n";
        cout << "8. Symmetric Difference (A Δ B)\n";
        cout << "9. Cartesian Product (A × B)\n";
        cout << "10. Display Sets\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int x;
                cout << "Enter element to check in A: ";
                cin >> x;
                cout << (A.ismember(x) ? "Yes" : "No") << endl;
                break;
            }
            case 2:
                A.powerset();
                break;

            case 3:
                cout << (A.subset(B) ? "A is a subset of B" : "A is not a subset of B") << endl;
                break;

            case 4:
                cout << "A ∪ B = ";
                A.unionSet(B).display();
                break;

            case 5:
                cout << "A ∩ B = ";
                A.intersectionSet(B).display();
                break;

            case 6:
                cout << "Complement of A = ";
                A.complement(U).display();
                break;

            case 7:
                cout << "A - B = ";
                A.difference(B).display();
                cout << "B - A = ";
                B.difference(A).display();
                break;

            case 8:
                cout << "A Δ B = ";
                A.symmetricDifference(B).display();
                break;

            case 9:
                A.cartesianProduct(B);
                break;

            case 10:
                cout << "Set A: ";
                A.display();
                cout << "Set B: ";
                B.display();
                cout << "Universal Set: ";
                U.display();
                break;

            case 0:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }

    } while (choice != 0);

    return 0;
}
