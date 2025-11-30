#include <iostream> 
#include <string> 
#include <map> 
#include <set>  

using namespace std;
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
        "101010",     
        "11011",       
        "0011101",     
        "111",         
        "0111",       
        "1111",        
        "10111",       
        "1"            
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
