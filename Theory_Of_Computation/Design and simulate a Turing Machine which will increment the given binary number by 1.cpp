#include <iostream>
#include <string>

// Use the standard namespace
using namespace std;

// --- Turing Machine State Definitions ---
const int Q0_SCAN_RIGHT = 0;
const int Q1_CARRY = 1;
const int Q_HALT = -1; // "Accept" state
const int Q_REJECT = -2; // Not used in this TM, but good practice

// --- Tape Constants ---
const char BLANK = 'B';

/**
 * @brief Simulates a TM that increments a binary number.
 * The function modifies the input string 's' to show the result.
 * @param s The input string (binary number), passed by reference.
 * @return true if the TM halts correctly, false otherwise.
 */
bool runTMIncrement(string& s) {
    // A TM tape is infinite. We simulate it by padding the string.
    // We need a blank at the front for the "111" -> "1000" case.
    string tape = BLANK + s + "BBBBBBBBBB";
    
    // Start head at the beginning of the original string
    int head = 1; 
    int currentState = Q0_SCAN_RIGHT; // Start at q0
    int steps = 0;
    const int MAX_STEPS = 10000; // Safety to prevent infinite loops

    while (steps < MAX_STEPS) {
        // --- Check for halt states ---
        if (currentState == Q_HALT) {
            // Success. We need to copy the final tape
            // back to the 's' string, trimming blanks.
            
            // Find the first non-blank character
            size_t first = tape.find_first_not_of(BLANK);
            if (string::npos == first) {
                // Tape is all blanks (shouldn't happen, but safe)
                s = "0"; 
            } else {
                // Find the last non-blank character
                size_t last = tape.find_last_not_of(BLANK);
                s = tape.substr(first, last - first + 1);
            }
            return true;
        }

        if (currentState == Q_REJECT) return false;

        // --- Ensure tape is large enough ---
        if (head == tape.length()) {
            tape += BLANK; // Add a blank if we move off the right end
        }
        
        // Handle moving off the left end
        if (head < 0) {
            // This is critical for the "111" -> "1000" case
            tape.insert(0, 1, BLANK); // Prepend a blank
            head = 0; // The head is now at this new blank
        }

        char read = tape[head]; // Read the character under the head

        switch (currentState) {
            case Q0_SCAN_RIGHT: // q0: Scan right
                if (read == '0' || read == '1') {
                    head++; // Move Right
                } else if (read == BLANK) {
                    head--; // Move Left
                    currentState = Q1_CARRY; // Go to q1
                }
                break;

            case Q1_CARRY: // q1: Carry loop
                if (read == '0') {
                    tape[head] = '1'; // Write '1'
                    // Move Stop (S)
                    currentState = Q_HALT; 
                } else if (read == '1') {
                    tape[head] = '0'; // Write '0'
                    head--;           // Move Left
                } else if (read == BLANK) {
                    tape[head] = '1'; // Write '1'
                    // Move Stop (S)
                    currentState = Q_HALT;
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
    cout << "--- TM Simulator: Binary Increment (n + 1) ---" << endl;
    cout << "Note: 'B' represents a blank tape cell." << endl;
    cout << "Enter 'q' to quit." << endl;

    string input;
    while (true) {
        cout << "\nEnter a binary number: ";
        cin >> input;

        if (input == "q") {
            break;
        }

        // We pass 'input' by reference. The function will modify it.
        if (runTMIncrement(input)) {
            cout << "Result: " << input << endl;
        } else {
            cout << "Result: FAILED (TM Timed Out or Rejected)" << endl;
        }
    }

    cout << "Exiting simulator." << endl;
    return 0;
}
