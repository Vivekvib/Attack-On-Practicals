#include <iostream> // For cout, cin, endl
#include <string>   // For string
#include <map>      // For map (to store the transition table)
#include <set>      // For set (to store final states)
#include <stdexcept> // For std::out_of_range
using namespace std;
/**
 * @brief Simulates the "product machine" for L1 (prefix/suffix) and L2 (a...b).
 * @param inputString The string to process.
 * @param operation "union" or "intersection".
 * @param transitions1 DFA for L1
 * @param startState1 Start state of L1
 * @param finalStates1 Final states of L1
 * @param transitions2 DFA for L2
 * @param startState2 Start state of L2
 * @param finalStates2 Final states of L2
 */
bool simulateProductDFA(
    const string& inputString,
    const string& operation,
    const map<string, map<char, string>>& transitions1,
    const string& startState1,
    const set<string>& finalStates1,
    const map<string, map<char, string>>& transitions2,
    const string& startState2,
    const set<string>& finalStates2) 
{
    set<char> alphabet = {'a', 'b'};
    string currentState1 = startState1;
    string currentState2 = startState2;
    cout << "Input: '" << inputString << "' | Operation: " << operation << endl;
    cout << "Start at state: (" << currentState1 << ", " << currentState2 << ")" << endl;
    for (char symbol : inputString) {
        if (alphabet.find(symbol) == alphabet.end()) {
            cerr << "Error: Symbol '" << symbol << "' is not in the alphabet {a, b}" << endl;
            cout << "Result: Rejected\n" << endl;
            return false;
        }
        string nextState1, nextState2;
        try {
            nextState1 = transitions1.at(currentState1).at(symbol);
            nextState2 = transitions2.at(currentState2).at(symbol);
        } catch (const out_of_range& e) {
            cerr << "Error: Invalid transition from state (" 
                 << currentState1 << ", " << currentState2 
                 << ") on symbol '" << symbol << "'" << endl;
            cout << "Result: Rejected\n" << endl;
            return false;
        }
        cout << "Read '" << symbol << "', transition (" << currentState1 << ", " << currentState2
             << ") -> (" << nextState1 << ", " << nextState2 << ")" << endl;
        currentState1 = nextState1;
        currentState2 = nextState2;
    }
    bool inF1 = (finalStates1.find(currentState1) != finalStates1.end());
    bool inF2 = (finalStates2.find(currentState2) != finalStates2.end());
    cout << "Finished processing." << endl;
    cout << "Final M1 state: " << currentState1 << " (in F1? " << (inF1 ? "Yes" : "No") << ")" << endl;
    cout << "Final M2 state: " << currentState2 << " (in F2? " << (inF2 ? "Yes" : "No") << ")" << endl;
    bool isAccepted = false;
    if (operation == "union") {
        isAccepted = inF1 || inF2; // Accept if in F1 OR in F2
    } else if (operation == "intersection") {
        isAccepted = inF1 && inF2; // Accept if in F1 AND in F2
    }
    if (isAccepted) {
        cout << "Result: Accepted\n" << endl;
    } else {
        cout << "Result: Rejected\n" << endl;
    }
    return isAccepted;
}
int main() {
    map<string, map<char, string>> transitions1;
    // States for Length 0, 1, 2
    transitions1["q0"] = {{'a', "S_a"}, {'b', "S_b"}};
    transitions1["S_a"] = {{'a', "S_aa"}, {'b', "S_ab"}};
    transitions1["S_b"] = {{'a', "S_ba"}, {'b', "S_bb"}};
    // States for Length 2
    transitions1["S_aa"] = {{'a', "S_aa_L3a"}, {'b', "S_aa_L3b"}};
    transitions1["S_ab"] = {{'a', "S_ab_L3a"}, {'b', "S_ab_L3b"}};
    transitions1["S_ba"] = {{'a', "S_ba_L3a"}, {'b', "S_ba_L3b"}};
    transitions1["S_bb"] = {{'a', "S_bb_L3a"}, {'b', "S_bb_L3b"}};
    // States for Length 3
    transitions1["S_aa_L3a"] = {{'a', "S_aa_AA"}, {'b', "S_aa_AB"}};
    transitions1["S_aa_L3b"] = {{'a', "S_aa_BA"}, {'b', "S_aa_BB"}};
    transitions1["S_ab_L3a"] = {{'a', "S_ab_AA"}, {'b', "S_ab_AB"}};
    transitions1["S_ab_L3b"] = {{'a', "S_ab_BA"}, {'b', "S_ab_BB"}};
    transitions1["S_ba_L3a"] = {{'a', "S_ba_AA"}, {'b', "S_ba_AB"}};
    transitions1["S_ba_L3b"] = {{'a', "S_ba_BA"}, {'b', "S_ba_BB"}};
    transitions1["S_bb_L3a"] = {{'a', "S_bb_AA"}, {'b', "S_bb_AB"}};
    transitions1["S_bb_L3b"] = {{'a', "S_bb_BA"}, {'b', "S_bb_BB"}};
    // States for Length 4+ (Main Machine)
    transitions1["S_aa_AA"] = {{'a', "S_aa_AA"}, {'b', "S_aa_AB"}};
    transitions1["S_aa_AB"] = {{'a', "S_aa_BA"}, {'b', "S_aa_BB"}};
    transitions1["S_aa_BA"] = {{'a', "S_aa_AA"}, {'b', "S_aa_AB"}};
    transitions1["S_aa_BB"] = {{'a', "S_aa_BA"}, {'b', "S_aa_BB"}};
    transitions1["S_ab_AA"] = {{'a', "S_ab_AA"}, {'b', "S_ab_AB"}};
    transitions1["S_ab_AB"] = {{'a', "S_ab_BA"}, {'b', "S_ab_BB"}};
    transitions1["S_ab_BA"] = {{'a', "S_ab_AA"}, {'b', "S_ab_AB"}};
    transitions1["S_ab_BB"] = {{'a', "S_ab_BA"}, {'b', "S_ab_BB"}};
    transitions1["S_ba_AA"] = {{'a', "S_ba_AA"}, {'b', "S_ba_AB"}};
    transitions1["S_ba_AB"] = {{'a', "S_ba_BA"}, {'b', "S_ba_BB"}};
    transitions1["S_ba_BA"] = {{'a', "S_ba_AA"}, {'b', "S_ba_AB"}};
    transitions1["S_ba_BB"] = {{'a', "S_ba_BA"}, {'b', "S_ba_BB"}};
    transitions1["S_bb_AA"] = {{'a', "S_bb_AA"}, {'b', "S_bb_AB"}};
    transitions1["S_bb_AB"] = {{'a', "S_bb_BA"}, {'b', "S_bb_BB"}};
    transitions1["S_bb_BA"] = {{'a', "S_bb_AA"}, {'b', "S_bb_AB"}};
    transitions1["S_bb_BB"] = {{'a', "S_bb_BA"}, {'b', "S_bb_BB"}};
    string startState1 = "q0";
    set<string> finalStates1 = {"S_aa_AA", "S_ab_AB", "S_ba_BA", "S_bb_BB"};
    map<string, map<char, string>> transitions2;
    transitions2["q0"] = {{'a', "q1"}, {'b', "q_dead"}};
    transitions2["q1"] = {{'a', "q1"}, {'b', "q2"}};
    transitions2["q2"] = {{'a', "q1"}, {'b', "q2"}};
    transitions2["q_dead"] = {{'a', "q_dead"}, {'b', "q_dead"}};
    string startState2 = "q0";
    set<string> finalStates2 = {"q2"};
    cout << "--- Running Test Cases ---" << endl;
    simulateProductDFA("abab", "union", transitions1, startState1, finalStates1, transitions2, startState2, finalStates2);
    simulateProductDFA("abab", "intersection", transitions1, startState1, finalStates1, transitions2, startState2, finalStates2);
    simulateProductDFA("aabaa", "union", transitions1, startState1, finalStates1, transitions2, startState2, finalStates2);
    simulateProductDFA("aabaa", "intersection", transitions1, startState1, finalStates1, transitions2, startState2, finalStates2);
    simulateProductDFA("aab", "union", transitions1, startState1, finalStates1, transitions2, startState2, finalStates2);
    simulateProductDFA("aab", "intersection", transitions1, startState1, finalStates1, transitions2, startState2, finalStates2);
    simulateProductDFA("bbb", "union", transitions1, startState1, finalStates1, transitions2, startState2, finalStates2);
    simulateProductDFA("bbb", "intersection", transitions1, startState1, finalStates1, transitions2, startState2, finalStates2);
    cout << "--- Interactive Mode ---" << endl;
    cout << "Enter 'exit' to quit." << endl;
    string userInput, opInput;
    while (true) {
        cout << "Enter operation (union/intersection) or 'exit': ";
        getline(cin, opInput);
        if (opInput == "exit") break;
        if (opInput != "union" && opInput != "intersection") {
            cout << "Invalid operation. Please enter 'union' or 'intersection'." << endl;
            continue;
        }
        cout << "Enter a string of 'a's and 'b's: ";
        getline(cin, userInput);
        if (userInput == "exit") break;
        simulateProductDFA(userInput, opInput, transitions1, startState1, finalStates1, transitions2, startState2, finalStates2);
    }
    return 0;
}
