#include <iostream> // For cout, cin, endl
#include <string>   // For string
#include <map>      // For map (to store the transition table)
#include <set>      // For set (to store final states)

using namespace std;

/**
 * @brief Simulates the DFA for the language of strings containing "111".
 * @param inputString The string to process.
 * @return true if the string is accepted, false otherwise.
 */
bool simulateDFA(const string& inputString) {
    set<char> alphabet = {'0', '1'};
    map<string, map<char, string>> transitions;

    transitions["q0"] = {{'0', "q0"}, {'1', "q1"}};
    transitions["q1"] = {{'0', "q0"}, {'1', "q2"}};
    transitions["q2"] = {{'0', "q0"}, {'1', "q3"}};
    transitions["q3"] = {{'0', "q3"}, {'1', "q3"}}; 
    string startState = "q0";
    set<string> finalStates = {"q3"};
    string currentState = startState;
    cout << "Input: '" << inputString << "'" << endl;
    cout << "Start at state: " << currentState << endl;
    for (char symbol : inputString) {
        // Check for invalid symbols
        if (alphabet.find(symbol) == alphabet.end()) {
            cerr << "Error: Symbol '" << symbol << "' is not in the alphabet {0, 1}" << endl;
            cout << "Result: Rejected\n" << endl;
            return false;
        }
        string nextState = transitions[currentState][symbol];
        cout << "Read '" << symbol << "', transition " << currentState << " -> " << nextState << endl;
        currentState = nextState;
    }
    bool isAccepted = (finalStates.find(currentState) != finalStates.end());
    cout << "Finished processing. Final state is: " << currentState << endl;
    if (isAccepted) {
        cout << "Result: Accepted\n" << endl;
    } else {
        cout << "Result: Rejected\n" << endl;
    }
    return isAccepted;
}
int main() {
    string testStrings[] = {
        "101010",       // Rejected
        "11011",        // Rejected
        "0011101",      // Accepted
        "111",          // Accepted
        "0111",         // Accepted
        "1111",         // Accepted
        "10111",        // Accepted
        "1"             // Rejected
    };
    int numTests = sizeof(testStrings) / sizeof(testStrings[0]);
    cout << "--- Running Test Cases ---" << endl;
    for (int i = 0; i < numTests; ++i) {
        simulateDFA(testStrings[i]);
    }
    cout << "--- Interactive Mode ---" << endl;
    cout << "Enter 'exit' to quit." << endl;
    string userInput;
    while (true) {
        cout << "Enter a string of 0s and 1s: ";
        getline(cin, userInput);
        if (userInput == "exit") {
            break;
        }
        if (userInput.empty()) {
            cout << "No input provided." << endl;
            continue;
        }
        simulateDFA(userInput);
    }
    return 0;
}
