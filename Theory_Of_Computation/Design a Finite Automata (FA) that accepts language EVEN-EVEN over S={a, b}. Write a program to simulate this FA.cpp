#include <iostream> // For cout, cin, endl
#include <string>   // For string
#include <map>      // For map (to store the transition table)
#include <set>      // For set (to store final states)
using namespace std;
/**
 * @brief Simulates the DFA for the "EVEN-EVEN" language
 * (Even 'a's and Even 'b's)
 * @param inputString The string to process.
 * @return true if the string is accepted, false otherwise.
 */
bool simulateDFA(const string& inputString) {
    set<char> alphabet = {'a', 'b'};
    map<string, map<char, string>> transitions;
    transitions["q_EE"] = {{'a', "q_OE"}, {'b', "q_EO"}};
    transitions["q_OE"] = {{'a', "q_EE"}, {'b', "q_OO"}};
    transitions["q_EO"] = {{'a', "q_OO"}, {'b', "q_EE"}};
    transitions["q_OO"] = {{'a', "q_EO"}, {'b', "q_OE"}};
    string startState = "q_EE";
    set<string> finalStates = {"q_EE"};
    string currentState = startState;
    cout << "Input: '" << inputString << "'" << endl;
    cout << "Start at state: " << currentState << endl;
    for (char symbol : inputString) {
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
        "",         // 0 'a's, 0 'b's (Even, Even)
        "aa",       // 2 'a's, 0 'b's (Even, Even)
        "bb",       // 0 'a's, 2 'b's (Even, Even)
        "abab",     // 2 'a's, 2 'b's (Even, Even)
        "aabb",     // 2 'a's, 2 'b's (Even, Even)
        "bbaabbaa", // 4 'a's, 4 'b's (Even, Even)
        // Rejected
        "a",        // 1 'a', 0 'b's (Odd, Even)
        "b",        // 0 'a's, 1 'b' (Even, Odd)
        "ab",       // 1 'a', 1 'b' (Odd, Odd)
        "aaa",      // 3 'a's, 0 'b's (Odd, Even)
        "abb"       // 1 'a', 2 'b's (Odd, Even)
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
