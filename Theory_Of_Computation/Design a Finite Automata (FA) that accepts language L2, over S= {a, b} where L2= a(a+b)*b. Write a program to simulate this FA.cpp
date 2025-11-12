#include <iostream> // For cout, cin, endl
#include <string>   // For string
#include <map>      // For map (to store the transition table)
#include <set>      // For set (to store final states)
using namespace std;
/**
 * @brief Simulates the DFA for the language L = a(a+b)*b
 * (Starts with 'a' and ends with 'b')
 * @param inputString The string to process.
 * @return true if the string is accepted, false otherwise.
 */
bool simulateDFA(const string& inputString) {
    set<char> alphabet = {'a', 'b'};
    map<string, map<char, string>> transitions;
    transitions["q0"] = {{'a', "q1"}, {'b', "q_dead"}}; // Start state
    transitions["q1"] = {{'a', "q1"}, {'b', "q2"}};     // Started with 'a', ends in 'a'
    transitions["q2"] = {{'a', "q1"}, {'b', "q2"}};     // Started with 'a', ends in 'b' (Accept)
    transitions["q_dead"] = {{'a', "q_dead"}, {'b', "q_dead"}}; // Started with 'b' (Trap)
    string startState = "q0";
    set<string> finalStates = {"q2"};
    string currentState = startState;
    cout << "Input: '" << inputString << "'" << endl;
    if (inputString.empty()) {
        cout << "Finished processing. Final state is: " << currentState << endl;
        cout << "Result: Rejected\n" << endl;
        return false;
    }
    for (char symbol : inputString) {
        // Check for invalid symbols
        if (alphabet.find(symbol) == alphabet.end()) {
            cerr << "Error: Symbol '" << symbol << "' is not in the alphabet {a, b}" << endl;
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
        // Accepted
        "ab",
        "aab",
        "abb",
        "abab",
        "aaaaab",
        
        // Rejected
        "a",       // Doesn't end in 'b'
        "aa",      // Doesn't end in 'b'
        "b",       // Doesn't start with 'a'
        "ba",      // Doesn't start with 'a'
        "bab",     // Doesn't start with 'a'
        ""         // Empty string
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
        cout << "Enter a string of 'a's and 'b's: ";
        getline(cin, userInput);
        if (userInput == "exit") {
            break;
        }
        simulateDFA(userInput);
    }
    return 0;
}
