#include <iostream>
#include <string>
#include <vector>
using namespace std;
enum State {
    q_ee, 
    q_oe, 
    q_eo, 
    q_oo  
};
string getStateName(State s) {
    switch (s) {
        case q_ee: return "q_ee (Even a, Even b)";
        case q_oe: return "q_oe (Odd a, Even b)";
        case q_eo: return "q_eo (Even a, Odd b)";
        case q_oo: return "q_oo (Odd a, Odd b)";
        default: return "unknown";
    }
}
State transition(State currentState, char input) {
    switch (currentState) {
        case q_ee:
            if (input == 'a') return q_oe;
            if (input == 'b') return q_eo;
            break;
        case q_oe:
            if (input == 'a') return q_ee;
            if (input == 'b') return q_oo;
            break;
        case q_eo:
            if (input == 'a') return q_oo; 
            if (input == 'b') return q_ee; 
            break;
        case q_oo:
            if (input == 'a') return q_eo;
            if (input == 'b') return q_oe; 
            break;
    }
    return currentState;
}
bool simulateDFA(string inputString) {
    State currentState = q_ee; // Start state (0 'a's and 0 'b's is Even-Even)
    cout << "\nProcessing String: \"" << inputString << "\"" << endl;
    cout << "Start: " << getStateName(currentState) << endl;
    for (char c : inputString) {
        if (c != 'a' && c != 'b') {
            cout << "Error: Invalid character '" << c << "'. Alphabet is {a, b}." << endl;
            return false;
        }
        State nextState = transition(currentState, c);
        cout << "  Input '" << c << "' : " 
             << getStateName(currentState) << " -> " << getStateName(nextState) << endl;
        currentState = nextState;
    }
    cout << "Final State: " << getStateName(currentState) << endl;
    if (currentState == q_ee) {
        cout << "Result: ACCEPTED (Even 'a's and Even 'b's)" << endl;
        return true;
    } else {
        cout << "Result: REJECTED" << endl;
        return false;
    }
}
int main() {
    cout << "=== DFA Simulator ===" << endl;
    cout << "Language: EVEN-EVEN (Even number of 'a's and Even number of 'b's)." << endl;
    cout << "States: q_ee(F), q_oe, q_eo, q_oo" << endl;
    string input;
    while (true) {
        cout << "\nEnter a string over {a, b} (or 'exit' to quit): ";
        cin >> input;
        if (input == "exit") break;
        simulateDFA(input);
    }
    return 0;
}
