#include <iostream>
#include <string>
using namespace std;
const int Q0_SCAN_RIGHT = 0;
const int Q1_CARRY = 1;
const int Q_HALT = -1; // "Accept" state
const int Q_REJECT = -2; // Not used in this TM, but good practice
const char BLANK = 'B';
bool runTMIncrement(string& s) {
    string tape = BLANK + s + "BBBBBBBBBB";
    int head = 1; 
    int currentState = Q0_SCAN_RIGHT; // Start at q0
    int steps = 0;
    const int MAX_STEPS = 10000; // Safety to prevent infinite loops

    while (steps < MAX_STEPS) {
        if (currentState == Q_HALT) {
            size_t first = tape.find_first_not_of(BLANK);
            if (string::npos == first) {
                s = "0"; 
            } else {
                size_t last = tape.find_last_not_of(BLANK);
                s = tape.substr(first, last - first + 1);
            }
            return true;
        }
        if (currentState == Q_REJECT) return false;
        if (head == tape.length()) {
            tape += BLANK;
        }
        if (head < 0) {
            // This is critical for the "111" -> "1000" case
            tape.insert(0, 1, BLANK);
            head = 0;
        }
        char read = tape[head];
        switch (currentState) {
            case Q0_SCAN_RIGHT:
                if (read == '0' || read == '1') {
                    head++;
                } else if (read == BLANK) {
                    head--;
                    currentState = Q1_CARRY;
                }
                break;
            case Q1_CARRY: 
                if (read == '0') {
                    tape[head] = '1'; 
                    currentState = Q_HALT; 
                } else if (read == '1') {
                    tape[head] = '0';
                    head--;     
                } else if (read == BLANK) {
                    tape[head] = '1'; 
                    currentState = Q_HALT;
                }
                break;
        }
        steps++;
    }
    return false;
}
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
        if (runTMIncrement(input)) {
            cout << "Result: " << input << endl;
        } else {
            cout << "Result: FAILED (TM Timed Out or Rejected)" << endl;
        }
    }
    cout << "Exiting simulator." << endl;
    return 0;
}
