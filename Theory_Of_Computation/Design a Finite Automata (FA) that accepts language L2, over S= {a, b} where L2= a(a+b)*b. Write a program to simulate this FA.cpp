#include <iostream>
#include <string>
#include <vector>
using namespace std;
class DFA {
private:
    enum StateID {
        S_START = 0,
        S_ENDS_A = 1,
        S_ENDS_B = 2, 
        S_DEAD = 3, 
        TOTAL_STATES = 4
    };
    vector<vector<int>> transitionTable;
    vector<bool> finalStates;
    vector<string> stateDescriptions;
public:
    DFA() {
        transitionTable.resize(TOTAL_STATES, vector<int>(2));
        finalStates.resize(TOTAL_STATES, false);
        stateDescriptions.resize(TOTAL_STATES);
        setupDFA();
    }
    void setupDFA() {
        stateDescriptions[S_START] = "Start (q0)";
        stateDescriptions[S_ENDS_A] = "Ends in 'a' (q1)";
        stateDescriptions[S_ENDS_B] = "Ends in 'b' (q2)";
        stateDescriptions[S_DEAD]  = "Dead State (Trap)";
        addTransition(S_START, S_ENDS_A, S_DEAD););
        addTransition(S_ENDS_B, S_ENDS_A, S_ENDS_B);
        addTransition(S_DEAD, S_DEAD, S_DEAD);
        finalStates[S_ENDS_B] = true;
    }
    void addTransition(int from, int toA, int toB) {
        transitionTable[from][0] = toA; // Input 'a'
        transitionTable[from][1] = toB; // Input 'b'
    }
    bool simulate(string input) {
        int currentState = S_START;
        cout << "\n--------------------------------------------------" << endl;
        cout << "Processing: \"" << input << "\"" << endl;
        cout << "Start: " << stateDescriptions[currentState] << endl;
        for (char c : input) {
            if (c != 'a' && c != 'b') {
                cout << "Error: Invalid char '" << c << "'. Alphabet is {a, b}." << endl;
                return false;
            }
            int inputIdx = (c == 'a') ? 0 : 1;
            int nextState = transitionTable[currentState][inputIdx];
            cout << "  Input '" << c << "' -> " << stateDescriptions[nextState] << endl;
            currentState = nextState;
        }
        cout << "End State: " << stateDescriptions[currentState] << endl;
        if (finalStates[currentState]) {
            cout << "Result: ACCEPTED (Starts with 'a', ends with 'b')" << endl;
            return true;
        } else {
            cout << "Result: REJECTED" << endl;
            return false;
        }
    }
};
int main() {
    DFA dfa;
    cout << "=== DFA Simulator ===" << endl;
    cout << "Language: L2 = a(a+b)*b" << endl;
    cout << "Regex logic: Starts with 'a', ends with 'b'." << endl;
    cout << "Alphabet: {a, b}" << endl;
    string input;
    while (true) {
        cout << "\nEnter string (or 'exit'): ";
        cin >> input;
        if (input == "exit") break;
        dfa.simulate(input);
    }
    return 0;
}
