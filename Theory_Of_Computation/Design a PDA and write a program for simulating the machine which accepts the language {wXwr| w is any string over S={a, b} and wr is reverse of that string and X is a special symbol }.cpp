#include <iostream>
#include <string>
#include <stack> // For the stack data structure

// Use the standard namespace
using namespace std;

/**
 * @brief Simulates the PDA for the language L = {wXw^r | w is in {a, b}*}
 * @param s The input string to check.
 * @return true if the string is in the language, false otherwise.
 */
bool isAcceptedPalindrome(string s) {
    stack<char> st;
    int currentState = 0; // Represents state q0

    // --- Transition 1: δ(q0, ε, ε) -> (q1, Z) ---
    st.push('Z'); // Push stack-bottom marker
    currentState = 1; // Move to state q1

    int stringIndex = 0; // To iterate through the input string

    // Loop through each character of the string
    while (stringIndex < s.length()) {
        char inputChar = s[stringIndex];

        if (currentState == 1) { // State q1: Pushing w
            if (inputChar == 'a') {
                // --- Transition 2: δ(q1, a, Y) -> (q1, aY) ---
                st.push('a');
                stringIndex++;
            } else if (inputChar == 'b') {
                // --- Transition 3: δ(q1, b, Y) -> (q1, bY) ---
                st.push('b');
                stringIndex++;
            } else if (inputChar == 'X') {
                // --- Transition 4: δ(q1, X, Y) -> (q2, Y) ---
                // Do nothing to the stack, just change state
                currentState = 2; // Move to state q2
                stringIndex++;
            } else {
                // Invalid character in this state
                return false;
            }
        } else if (currentState == 2) { // State q2: Popping for w^r
            if (inputChar == 'a') {
                // --- Transition 5: δ(q2, a, a) -> (q2, ε) ---
                if (!st.empty() && st.top() == 'a') {
                    st.pop(); // Pop the matching 'a'
                    stringIndex++;
                } else {
                    // Mismatch! (e.g., "aXb") or stack empty
                    return false;
                }
            } else if (inputChar == 'b') {
                // --- Transition 6: δ(q2, b, b) -> (q2, ε) ---
                if (!st.empty() && st.top() == 'b') {
                    st.pop(); // Pop the matching 'b'
                    stringIndex++;
                } else {
                    // Mismatch! (e.g., "bXa") or stack empty
                    return false;
                }
            } else {
                // Invalid character in this state (e.g., "aXaX")
                return false;
            }
        }
    }

    // --- After the string is fully read ---
    // We are now checking for ε transitions.

    // If we are still in state q1, it means we never saw an 'X'.
    if (currentState == 1) {
        return false;
    }

    // If we are in state q2, we check for the final transition
    if (currentState == 2) {
        // --- Transition 7: δ(q2, ε, Z) -> (q3, ε) ---
        if (!st.empty() && st.top() == 'Z') {
            st.pop(); // Pop 'Z'
            currentState = 3; // Move to final state q3
        } else {
            // We are in state q2, but the stack top is not 'Z'.
            // This means w was longer than w^r (e.g., "abXa").
            return false;
        }
    }

    // The string is accepted if AND ONLY IF we are in state q3
    // AND the stack is now empty.
    return (currentState == 3 && st.empty());
}

// Main function to drive the simulation
int main() {
    cout << "--- PDA Simulator for L = {wXw^r} ---" << endl;
    cout << "Enter 'q' to quit." << endl;

    string input;
    while (true) {
        cout << "\nEnter a string (using a, b, X): ";
        cin >> input;

        if (input == "q") {
            break;
        }

        if (isAcceptedPalindrome(input)) {
            cout << "Result: ACCEPTED" << endl;
        } else {
            cout << "Result: REJECTED" << endl;
        }
    }

    cout << "Exiting simulator." << endl;
    return 0;
}
