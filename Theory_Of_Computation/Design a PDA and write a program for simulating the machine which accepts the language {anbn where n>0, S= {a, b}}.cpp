#include <iostream>
#include <string>
#include <vector>
#include <stack>
using namespace std;
class PDA {
private:
    enum State {
        q0,
        q1,
        q2,
        q3,
        q_reject 
    };
    string getStateName(State s) {
        switch(s) {
            case q0: return "q0 (Start)";
            case q1: return "q1 (Pushing)";
            case q2: return "q2 (Popping)";
            case q3: return "q3 (Accept)";
            default: return "Reject";
        }
    }
public:
    bool simulate(string input) {
        State currentState = q0;
        stack<char> st;
        st.push('Z'); // Initialize stack with Bottom Marker
        cout << "\n--------------------------------------------------" << endl;
        cout << "Processing: \"" << input << "\"" << endl;
        cout << "Init: State " << getStateName(currentState) << ", Stack: [Z]" << endl;
        for (char inputChar : input) {
            char stackTop = st.top();
            switch (currentState) {
                case q0:
                    if (inputChar == 'a' && stackTop == 'Z') {
                        st.push('A');
                        currentState = q1;
                        cout << "  Input 'a', Top 'Z' -> Push 'A', Goto q1" << endl;
                    } else {
                        currentState = q_reject;
                        cout << "  Input '" << inputChar << "' at Start -> Reject" << endl;
                    }
                    break;
                case q1:
                    if (inputChar == 'a' && stackTop == 'A') {
                        st.push('A');
                        cout << "  Input 'a', Top 'A' -> Push 'A', Stay q1" << endl;
                    }
                    else if (inputChar == 'b' && stackTop == 'A') {
                        st.pop();
                        currentState = q2;
                        cout << "  Input 'b', Top 'A' -> Pop 'A', Goto q2" << endl;
                    }
                    else {
                        currentState = q_reject; // Invalid sequence or chars
                        cout << "  Input '" << inputChar << "' in q1 -> Reject" << endl;
                    }
                    break;
                case q2:
                    if (inputChar == 'b' && stackTop == 'A') {
                        st.pop();
                        cout << "  Input 'b', Top 'A' -> Pop 'A', Stay q2" << endl;
                    }
                    else if (inputChar == 'a') {
                        currentState = q_reject;
                        cout << "  Input 'a' after 'b' -> Reject" << endl;
                    }
                    else if (inputChar == 'b' && stackTop == 'Z') {
                        currentState = q_reject;
                        cout << "  Input 'b', Top 'Z' -> Reject (Too many b's)" << endl;
                    }
                    else {
                        currentState = q_reject;
                    }
                    break;
                case q_reject:
                    break; // Stay in reject
            }
            if (currentState == q_reject) break;
        }
        if (currentState == q2 && st.top() == 'Z') {
            currentState = q3;
            cout << "  End of Input, Top 'Z' -> Goto q3 (Accept)" << endl;
        }
        cout << "Final State: " << getStateName(currentState) << endl;
        if (currentState == q3) {
            cout << "Result: ACCEPTED" << endl;
            return true;
        } else {
            if (!st.empty() && st.top() == 'A') cout << "Reason: Stack not empty (Too many a's)." << endl;
            else if (currentState == q_reject) cout << "Reason: Invalid transition or order." << endl;
            else if (currentState == q0) cout << "Reason: Empty input (n must be > 0)." << endl;
            cout << "Result: REJECTED" << endl;
            return false;
        }
    }
};
int main() {
    PDA pda;
    cout << "=== PDA Simulator ===" << endl;
    cout << "Language: { a^n b^n | n > 0 }" << endl;
    cout << "Alphabet: {a, b}, Stack: {A, Z}" << endl;

    string input;
    while (true) {
        cout << "\nEnter string (or 'exit'): ";
        cin >> input;
        if (input == "exit") break;
        pda.simulate(input);
    }
    return 0;
}
