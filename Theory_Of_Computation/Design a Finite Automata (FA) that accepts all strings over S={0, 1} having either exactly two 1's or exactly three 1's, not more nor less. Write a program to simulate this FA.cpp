#include <iostream> // For cout, cin, endl
#include <string>   // For string
#include <map>      // For map (to store the transition table)
#include <set>      // For set (to store final states)
using namespace std;

/**
 * @brief Simulates the DFA for the language of strings with
 * exactly two or exactly three 1's.
 * @param inputString The string to process.
 * @return true if the string is accepted, false otherwise.
 */
bool simulateDFA(const string& inputString) {
    set<char> alphabet = {'0', '1'};
    map<string, map<char, string>> transitions;
    transitions["q0"] = {{'0', "q0"}, {'1', "q1"}}; // 0 ones
    transitions["q1"] = {{'0', "q1"}, {'1', "q2"}}; // 1 one
    transitions["q2"] = {{'0', "q2"}, {'1', "q3"}}; // 2 ones (Accept)
    transitions["q3"] = {{'0', "q3"}, {'1', "q4"}}; // 3 ones (Accept)
    transitions["q4"] = {{'0', "q4"}, {'1', "q4"}}; // 4+ ones (Reject/Trap)
    string startState = "q0";
    set<string> finalStates = {"q2", "q3"};
    string currentState = startState;
    
    cout << "Input: '" << inputString << "'" << endl;
    cout << "Start at state: " << currentState << endl;
    if (inputString.empty()) {
        cout << "Finished processing. Final state is: " << currentState << endl;
    }
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
        "01010",    // Accepted (2 ones)
        "11",       // Accepted (2 ones)
        "10101",    // Accepted (3 ones)
        "0111",     // Accepted (3 ones)
        "000",      // Rejected (0 ones)
        "100",      // Rejected (1 one)
        "1111",     // Rejected (4 ones)
        "0101110",  // Rejected (4 ones)
        ""          // Rejected (0 ones, empty string)
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
        simulateDFA(userInput);
    }
    return 0;
}
