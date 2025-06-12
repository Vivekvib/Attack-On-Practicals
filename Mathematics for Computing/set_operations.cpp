#include <iostream>
#include <set>
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
// Sample usage in main()
// -------------------------
int main() {
    SET A, B, U;

    int u_size, a_size, b_size;

    cout << "Enter size of Universal Set: ";
    cin >> u_size;
    U.input(u_size);

    cout << "Enter size of Set A: ";
    cin >> a_size;
    A.input(a_size);

    cout << "Enter size of Set B: ";
    cin >> b_size;
    B.input(b_size);

    cout << "\nSet A: ";
    A.display();

    cout << "Set B: ";
    B.display();

    cout << "\nIs 3 in A? " << (A.ismember(3) ? "Yes" : "No") << endl;

    cout << "\nPower Set of A:\n";
    A.powerset();

    cout << "\nIs A subset of B? " << (A.subset(B) ? "Yes" : "No") << endl;

    cout << "\nA ∪ B = ";
    A.unionSet(B).display();

    cout << "A ∩ B = ";
    A.intersectionSet(B).display();

    cout << "Complement of A = ";
    A.complement(U).display();

    cout << "A - B = ";
    A.difference(B).display();

    cout << "Symmetric Difference (A Δ B) = ";
    A.symmetricDifference(B).display();

    cout << "\nA × B:\n";
    A.cartesianProduct(B);

    return 0;
}
