#include <iostream>
#include <string>
#include <vector>
using namespace std;
enum State {
    q0, 
    q1,
    q2,
    q3,
    q4 
};
string getStateName(State s) {
    switch (s) {
        case q0: return "q0";
        case q1: return "q1";
        case q2: return "q2";
        case q3: return "q3";
        case q4: return "q4";
        default: return "unknown";
    }
}
State transition(State currentState, char input) {
    switch (currentState) {
        case q0:
            if (input == '1') return q1;
            if (input == '0') return q0;
            break;
        case q1:
            if (input == '1') return q2;
            if (input == '0') return q1;
            break;
        case q2:
            if (input == '1') return q3;
            if (input == '0') return q2;
            break;
        case q3:
            if (input == '1') return q4;
            if (input == '0') return q3;
            break;
        case q4:
            return q4; 
    }
    return currentState;
}
bool simulateDFA(string inputString) {
    State currentState = q0; // Start state
    cout << "\nProcessing String: \"" << inputString << "\"" << endl;
    cout << "Start: " << getStateName(currentState) << endl;
    for (char c : inputString) {
        if (c != '0' && c != '1') {
            cout << "Error: Invalid character '" << c << "'. Alphabet is {0, 1}." << endl;
            return false;
        }
        State nextState = transition(currentState, c);
        cout << "  Input '" << c << "' : " 
             << getStateName(currentState) << " -> " << getStateName(nextState) << endl;
        currentState = nextState;
    }
    cout << "Final State: " << getStateName(currentState) << endl;
    if (currentState == q2 || currentState == q3) {
        cout << "Result: ACCEPTED (Contains exactly 2 or 3 ones)" << endl;
        return true;
    } else {
        if (currentState == q4) {
            cout << "Result: REJECTED (Too many ones)" << endl;
        } else {
             cout << "Result: REJECTED (Not enough ones)" << endl;
        }
        return false;
    }
}
int main() {
    cout << "=== DFA Simulator ===" << endl;
    cout << "Language: Strings with exactly 2 or exactly 3 ones." << endl;
    cout << "States: q0, q1, q2(F), q3(F), q4(Trap)" << endl;
    string input;
    while (true) {
        cout << "\nEnter a binary string (or 'exit' to quit): ";
        cin >> input;
        if (input == "exit") break;
        simulateDFA(input);
    }
    return 0;
}
