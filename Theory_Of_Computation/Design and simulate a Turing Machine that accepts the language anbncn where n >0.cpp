#include <iostream>
#include <string>
using namespace std;
const int Q0_START = 0;
const int Q1_FIND_B = 1;
const int Q2_FIND_C = 2;
const int Q3_REWIND = 3;
const int Q4_NEXT_LOOP = 4;
const int Q5_VERIFY = 5;
const int Q_ACCEPT = -1;
const int Q_REJECT = -2;
const char BLANK = 'B';
bool isAcceptedTM(string s) {
    string tape = s;
    tape += "BBBBBBBBBB";
    int head = 0;
    int currentState = Q0_START;
    int steps = 0;
    const int MAX_STEPS = 10000;
    while (steps < MAX_STEPS) {
        if (currentState == Q_ACCEPT) return true;
        if (currentState == Q_REJECT) return false;
        if (head == tape.length()) {
            tape += BLANK;
        }
        if (head < 0) {
            currentState = Q_REJECT;
            continue;
        }
        char read = tape[head];
        switch (currentState) {
            case Q0_START:
                if (read == 'a') {
                    tape[head] = 'X';
                    head++;       
                    currentState = Q1_FIND_B;
                } else {
                    currentState = Q_REJECT;
                }
                break;

            case Q1_FIND_B:
                if (read == 'a' || read == 'Y') {
                    head++;
                } else if (read == 'b') {
                    tape[head] = 'Y';
                    head++;
                    currentState = Q2_FIND_C;
                } else {
                    currentState = Q_REJECT;
                }
                break;
            case Q2_FIND_C:
                if (read == 'b' || read == 'Z') {
                    head++;
                } else if (read == 'c') {
                    tape[head] = 'Z'; 
                    head--;         
                    currentState = Q3_REWIND; 
                } else {
                    currentState = Q_REJECT;
                }
                break;

            case Q3_REWIND:
                if (read == 'a' || read == 'b' || read == 'Y' || read == 'Z') {
                    head--;
                } else if (read == 'X') {
                    head++;  
                    currentState = Q4_NEXT_LOOP; 
                } else {
                    currentState = Q_REJECT;
                }
                break;

            case Q4_NEXT_LOOP:
                if (read == 'a') {
                    tape[head] = 'X'; 
                    head++;      
                    currentState = Q1_FIND_B;
                } else if (read == 'Y') {
                    // No more 'a's. Start verification.
                    head++;  
                    currentState = Q5_VERIFY;
                } else {
                    currentState = Q_REJECT;
                }
                break;
            case Q5_VERIFY:
                if (read == 'Y' || read == 'Z') {
                    head++;
                } else if (read == BLANK) {
                    currentState = Q_ACCEPT;
                } else {
                    currentState = Q_REJECT;
                }
                break;
        }
        steps++;
    }
    return false;
}
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


