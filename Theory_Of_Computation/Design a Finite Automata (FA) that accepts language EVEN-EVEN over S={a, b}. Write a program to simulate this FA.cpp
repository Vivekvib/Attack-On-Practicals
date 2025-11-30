#include <iostream> 
#include <string>   
#include <map>      
#include <set>      
using namespace std;
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
        "",        
        "aa",      
        "bb",       
        "abab",    
        "aabb",    
        "bbaabbaa", 
        // Rejected
        "a",       
        "b",       
        "ab",     
        "aaa",    
        "abb"      
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
