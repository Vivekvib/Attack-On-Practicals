#include <iostream>
using namespace std;

class Relation {
private:
    int matrix[20][20];
    int set[20];
    int size;

public:
    void input() {
        cout << "Enter number of elements in the set: ";
        cin >> size;

        cout << "Enter " << size << " elements of the set:\n";
        for (int i = 0; i < size; i++) {
            cin >> set[i];
        }

        cout << "Enter the relation matrix (0 or 1):\n";
        cout << "Row i and Column j will be 1 if (i,j) ∈ R else 0\n";
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                cin >> matrix[i][j];
            }
        }
    }

    void displayMatrix() const {
        cout << "\nRelation Matrix:\n";
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    bool isReflexive() const {
        for (int i = 0; i < size; i++) {
            if (matrix[i][i] != 1)
                return false;
        }
        return true;
    }

    bool isSymmetric() const {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (matrix[i][j] != matrix[j][i])
                    return false;
            }
        }
        return true;
    }

    bool isAntiSymmetric() const {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (i != j && matrix[i][j] == 1 && matrix[j][i] == 1)
                    return false;
            }
        }
        return true;
    }

    bool isTransitive() const {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (matrix[i][j]) {
                    for (int k = 0; k < size; k++) {
                        if (matrix[j][k] && !matrix[i][k]) {
                            return false;
                        }
                    }
                }
            }
        }
        return true;
    }

    void checkRelationType() const {
        bool reflexive = isReflexive();
        bool symmetric = isSymmetric();
        bool antisymmetric = isAntiSymmetric();
        bool transitive = isTransitive();

        cout << "\nProperties:\n";
        cout << "Reflexive: " << (reflexive ? "Yes" : "No") << endl;
        cout << "Symmetric: " << (symmetric ? "Yes" : "No") << endl;
        cout << "Anti-Symmetric: " << (antisymmetric ? "Yes" : "No") << endl;
        cout << "Transitive: " << (transitive ? "Yes" : "No") << endl;

        if (reflexive && symmetric && transitive)
            cout << "\nThis is an Equivalence Relation.\n";
        else if (reflexive && antisymmetric && transitive)
            cout << "\nThis is a Partial Order Relation.\n";
        else
            cout << "\nThis is Neither an Equivalence nor a Partial Order Relation.\n";
    }
};

// -------------------------
// Main function
// -------------------------
int main() {
    Relation r;
    r.input();
    r.displayMatrix();
    r.checkRelationType();
    return 0;
}
