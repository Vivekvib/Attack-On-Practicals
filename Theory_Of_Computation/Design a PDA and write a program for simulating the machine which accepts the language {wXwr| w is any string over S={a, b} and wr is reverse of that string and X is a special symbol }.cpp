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
        q_reject
    };
    string getStateName(State s) {
        switch(s) {
            case q0: return "q0 (Pushing w)";
            case q1: return "q1 (Matching w^R)";
            case q2: return "q2 (Accept)";
            default: return "Reject";
        }
    }
public:
    bool simulate(string input) {
        State currentState = q0;
        stack<char> st;
        st.push('Z');
        cout << "\n--------------------------------------------------" << endl;
        cout << "Processing: \"" << input << "\"" << endl;
        cout << "Init: State " << getStateName(currentState) << ", Stack: [Z]" << endl;
        for (char inputChar : input) {
            char stackTop = st.top();
            switch (currentState) {
                case q0:
                    if (inputChar == 'a' || inputChar == 'b') {
                        st.push(inputChar);
                        cout << "  Input '" << inputChar << "' -> Push '" << inputChar << "', Stay q0" << endl;
                    } 
                    else if (inputChar == 'X') {
                        currentState = q1;
                        cout << "  Input 'X' -> Switch to Matching Mode (Goto q1)" << endl;
                    }
                    else {
                        currentState = q_reject;
                        cout << "  Input '" << inputChar << "' -> Reject (Invalid char)" << endl;
                    }
                    break;
                case q1:
                    if (stackTop == 'Z') {
                        currentState = q_reject;
                        cout << "  Input '" << inputChar << "', Stack Empty -> Reject (Length mismatch)" << endl;
                    } 
                    else if (inputChar == stackTop) {
                        st.pop();
                        cout << "  Input '" << inputChar << "' == Stack Top '" << stackTop << "' -> Pop, Stay q1" << endl;
                    } 
                    else {
                        currentState = q_reject;
                        cout << "  Input '" << inputChar << "' != Stack Top '" << stackTop << "' -> Reject (Mismatch)" << endl;
                    }
                    break;
                case q2:
                case q_reject:
                    break;
            }
            if (currentState == q_reject) break;
        }
        if (currentState == q1 && st.top() == 'Z') {
            currentState = q2;
            cout << "  End of Input, Stack Empty -> Goto q2 (Accept)" << endl;
        }
        cout << "Final State: " << getStateName(currentState) << endl;
        if (currentState == q2) {
            cout << "Result: ACCEPTED" << endl;
            return true;
        } else {
            if (currentState == q0) cout << "Reason: 'X' symbol missing." << endl;
            else if (!st.empty() && st.top() != 'Z') cout << "Reason: Stack not empty (Input too short)." << endl;
            else if (currentState == q_reject) cout << "Reason: Mismatch or invalid character." << endl;
            cout << "Result: REJECTED" << endl;
            return false;
        }
    }
};
int main() {
    PDA pda;
    cout << "=== PDA Simulator ===" << endl;
    cout << "Language: { wXw^R | w in {a,b}* }" << endl;
    cout << "Examples: aXa, abXba, abbXbba, X (empty w)" << endl;
    string input;
    while (true) {
        cout << "\nEnter string (or 'exit'): ";
        cin >> input;
        if (input == "exit") break;
        pda.simulate(input);
    }
    return 0;
}
