#include <iostream>
#include <string>
#include <stack> // For the stack data structure

// Use the standard namespace
using namespace std;

/**
 * @brief Simulates the PDA for the language L = {a^n b^n | n > 0}
 * @param s The input string to check.
 * @return true if the string is in the language, false otherwise.
 */
bool isAccepted(string s) {
    stack<char> st;
    int currentState = 0; // Represents state q0

    // --- Transition 1: δ(q0, ε, ε) -> (q1, Z) ---
    // This is our initialization.
    st.push('Z'); // Push stack-bottom marker
    currentState = 1; // Move to state q1

    int stringIndex = 0; // To iterate through the input string

    // Loop through each character of the string
    while (stringIndex < s.length()) {
        char inputChar = s[stringIndex];

        if (currentState == 1) { // State q1: Pushing 'a's
            if (inputChar == 'a') {
                // --- Transition 2: δ(q1, a, X) -> (q1, AX) ---
                // We just push 'A' and stay in state q1
                st.push('A');
                stringIndex++;
            } else if (inputChar == 'b') {
                // --- Transition 3: δ(q1, b, A) -> (q2, ε) ---
                // Check if we can make the transition
                if (!st.empty() && st.top() == 'A') {
                    st.pop(); // Pop 'A'
                    currentState = 2; // Move to state q2
                    stringIndex++;
                } else {
                    // Crash! No 'A' to pop (e.g., input "b..." or "aabbb" with n=0)
                    return false;
                }
            } else {
                // Invalid character
                return false;
            }
        } else if (currentState == 2) { // State q2: Popping 'b's
            if (inputChar == 'b') {
                // --- Transition 4: δ(q2, b, A) -> (q2, ε) ---
                if (!st.empty() && st.top() == 'A') {
                    st.pop(); // Pop 'A' for the 'b'
                    // Stay in state q2
                    stringIndex++;
                } else {
                    // Crash! Too many 'b's (e.g., "abb") or stack is empty
                    return false;
                }
            } else {
                // Invalid state! e.g., "aba". We see an 'a' in state q2.
                return false;
            }
        }
    }

    // --- After the string is fully read ---
    // We are now checking for ε transitions.
    
    // If we are still in state q1, it means we only saw 'a's (e.g., "aaa")
    // This is not accepted.
    if (currentState == 1) {
        return false;
    }

    // If we are in state q2, we check for the final transition
    if (currentState == 2) {
        // --- Transition 5: δ(q2, ε, Z) -> (q3, ε) ---
        if (!st.empty() && st.top() == 'Z') {
            st.pop(); // Pop 'Z'
            currentState = 3; // Move to final state q3
        } else {
            // We are in state q2, but the stack top is not 'Z'.
            // This means we had too few 'b's (e.g., "aab").
            return false;
        }
    }

    // The string is accepted if AND ONLY IF we are in state q3
    // AND the stack is now empty.
    return (currentState == 3 && st.empty());
}

// Main function to drive the simulation
int main() {
    cout << "--- PDA Simulator for L = {a^n b^n | n > 0} ---" << endl;
    cout << "Enter 'q' to quit." << endl;

    string input;
    while (true) {
        cout << "\nEnter a string: ";
        cin >> input;

        if (input == "q") {
            break;
        }

        if (isAccepted(input)) {
            cout << "Result: ACCEPTED" << endl;
        } else {
            cout << "Result: REJECTED" << endl;
        }
    }

    cout << "Exiting simulator." << endl;
    return 0;
}
