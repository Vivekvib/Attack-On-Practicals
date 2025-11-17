#include <iostream>
#include <string>
#include <stack> // Not used, but included in previous requests

// Use the standard namespace
using namespace std;

// --- Turing Machine State Definitions ---
// We use integer constants to represent the states
const int Q0_START = 0;
const int Q1_FIND_B = 1;
const int Q2_FIND_C = 2;
const int Q3_REWIND = 3;
const int Q4_NEXT_LOOP = 4;
const int Q5_VERIFY = 5;
const int Q_ACCEPT = -1;
const int Q_REJECT = -2;

// --- Tape Constants ---
const char BLANK = 'B';

/**
 * @brief Simulates the TM for the language L = {a^n b^n c^n | n > 0}
 * @param s The input string to check.
 * @return true if the string is in the language, false otherwise.
 */
bool isAcceptedTM(string s) {
    // A TM tape is infinite. We simulate it with a string
    // and add Blanks ('B') as needed.
    string tape = s;
    tape += "BBBBBBBBBB"; // Add some initial blank padding
    
    int head = 0; // The tape head position
    int currentState = Q0_START; // Start at q0
    int steps = 0;
    const int MAX_STEPS = 10000; // Safety to prevent infinite loops

    while (steps < MAX_STEPS) {
        // --- Check for halt states ---
        if (currentState == Q_ACCEPT) return true;
        if (currentState == Q_REJECT) return false;

        // --- Ensure tape is large enough ---
        if (head == tape.length()) {
            tape += BLANK; // Add a blank if we move off the right end
        }
        if (head < 0) {
            // Should not happen in this TM's logic, but good to check
            currentState = Q_REJECT;
            continue;
        }

        char read = tape[head]; // Read the character under the head

        switch (currentState) {
            case Q0_START: // q0: Must find 'a' (for n > 0)
                if (read == 'a') {
                    tape[head] = 'X'; // Write 'X'
                    head++;           // Move Right
                    currentState = Q1_FIND_B; // Go to q1
                } else {
                    // If input is "" or starts with b, c, etc.
                    currentState = Q_REJECT;
                }
                break;

            case Q1_FIND_B: // q1: Find 'b'
                if (read == 'a' || read == 'Y') {
                    head++; // Skip 'a's and 'Y's
                } else if (read == 'b') {
                    tape[head] = 'Y'; // Write 'Y'
                    head++;           // Move Right
                    currentState = Q2_FIND_C; // Go to q2
                } else {
                    // No 'b' found
                    currentState = Q_REJECT;
                }
                break;

            case Q2_FIND_C: // q2: Find 'c'
                if (read == 'b' || read == 'Z') {
                    head++; // Skip 'b's and 'Z's
                } else if (read == 'c') {
                    tape[head] = 'Z'; // Write 'Z'
                    head--;           // Move Left
                    currentState = Q3_REWIND; // Go to q3
                } else {
                    // No 'c' found
                    currentState = Q_REJECT;
                }
                break;

            case Q3_REWIND: // q3: Rewind to 'X'
                if (read == 'a' || read == 'b' || read == 'Y' || read == 'Z') {
                    head--; // Keep moving Left
                } else if (read == 'X') {
                    head++;           // Move Right (one step)
                    currentState = Q4_NEXT_LOOP; // Go to q4
                } else {
                    // Should not happen
                    currentState = Q_REJECT;
                }
                break;

            case Q4_NEXT_LOOP: // q4: Find next 'a'
                if (read == 'a') {
                    tape[head] = 'X'; // Write 'X'
                    head++;           // Move Right
                    currentState = Q1_FIND_B; // Repeat cycle
                } else if (read == 'Y') {
                    // No more 'a's. Start verification.
                    head++;           // Move Right
                    currentState = Q5_VERIFY; // Go to q5
                } else {
                    // e.g., found 'b' or 'c' where 'a' should be
                    currentState = Q_REJECT;
                }
                break;

            case Q5_VERIFY: // q5: Verify only Y's and Z's left
                if (read == 'Y' || read == 'Z') {
                    head++; // Skip 'Y's and 'Z's
                } else if (read == BLANK) {
                    // Found the blank at the end. Success!
                    currentState = Q_ACCEPT;
                } else {
                    // Found stray 'b' or 'c'
                    currentState = Q_REJECT;
                }
                break;
        }
        steps++;
    }

    // If we exit the loop due to MAX_STEPS, it's a timeout (reject)
    return false;
}

// Main function to drive the simulation
int main() {
    cout << "--- TM Simulator for L = {a^n b^n c^n | n > 0} ---" << endl;
    cout <<"Note: 'B' represents a blank tape cell." << endl;
    cout << "Enter 'q' to quit." << endl;

    string input;
    while (true) {
        cout << "\nEnter a string (using a, b, c): ";
        cin >> input;

        if (input == "q") {
            break;
        }

        if (isAcceptedTM(input)) {
            cout << "Result: ACCEPTED" << endl;
        } else {
            cout << "Result: REJECTED" << endl;
        }
    }

    cout << "Exiting simulator." << endl;
    return 0;
}
