#include <iostream> // For cout, cin, endl
#include <string>   // For string
#include <map>      // For map (to store the transition table)
#include <set>      // For set (to store final states)
using namespace std;
/**
 * @brief Simulates the DFA for the language L = {w | |w| >= 4 and w1w2 = w(n-1)wn}
 * @param inputString The string to process.
 * @return true if the string is accepted, false otherwise.
 */
bool simulateDFA(const string& inputString) {
    set<char> alphabet = {'a', 'b'};
    map<string, map<char, string>> transitions;
    transitions["q0"] = {{'a', "S_a"}, {'b', "S_b"}};
    transitions["S_a"] = {{'a', "S_aa"}, {'b', "S_ab"}};
    transitions["S_b"] = {{'a', "S_ba"}, {'b', "S_bb"}};
    transitions["S_aa"] = {{'a', "S_aa_L3a"}, {'b', "S_aa_L3b"}};
    transitions["S_ab"] = {{'a', "S_ab_L3a"}, {'b', "S_ab_L3b"}};
    transitions["S_ba"] = {{'a', "S_ba_L3a"}, {'b', "S_ba_L3b"}};
    transitions["S_bb"] = {{'a', "S_bb_L3a"}, {'b', "S_bb_L3b"}};
    transitions["S_aa_L3a"] = {{'a', "S_aa_AA"}, {'b', "S_aa_AB"}}; // "aaa" -> "aaaa"(AA) or "aaab"(AB)
    transitions["S_aa_L3b"] = {{'a', "S_aa_BA"}, {'b', "S_aa_BB"}}; // "aab" -> "aaba"(BA) or "aabb"(BB)
    transitions["S_ab_L3a"] = {{'a', "S_ab_AA"}, {'b', "S_ab_AB"}}; // "aba" -> "abaa"(AA) or "abab"(AB)
    transitions["S_ab_L3b"] = {{'a', "S_ab_BA"}, {'b', "S_ab_BB"}}; // "abb" -> "abba"(BA) or "abbb"(BB)
    transitions["S_ba_L3a"] = {{'a', "S_ba_AA"}, {'b', "S_ba_AB"}}; // "baa" -> "baaa"(AA) or "baab"(AB)
    transitions["S_ba_L3b"] = {{'a', "S_ba_BA"}, {'b', "S_ba_BB"}}; // "bab" -> "baba"(BA) or "babb"(BB)
    transitions["S_bb_L3a"] = {{'a', "S_bb_AA"}, {'b', "S_bb_AB"}}; // "bba" -> "bbaa"(AA) or "bbab"(AB)
    transitions["S_bb_L3b"] = {{'a', "S_bb_BA"}, {'b', "S_bb_BB"}}; // "bbb" -> "bbba"(BA) or "bbbb"(BB)
    // The logic is: S_xx_YZ on 'c' -> S_xx_Zc
    transitions["S_aa_AA"] = {{'a', "S_aa_AA"}, {'b', "S_aa_AB"}}; // Ends "aa" -> "aa" or "ab"
    transitions["S_aa_AB"] = {{'a', "S_aa_BA"}, {'b', "S_aa_BB"}}; // Ends "ab" -> "ba" or "bb"
    transitions["S_aa_BA"] = {{'a', "S_aa_AA"}, {'b', "S_aa_AB"}}; // Ends "ba" -> "aa" or "ab"
    transitions["S_aa_BB"] = {{'a', "S_aa_BA"}, {'b', "S_aa_BB"}}; // Ends "bb" -> "ba" or "bb"
    transitions["S_ab_AA"] = {{'a', "S_ab_AA"}, {'b', "S_ab_AB"}};
    transitions["S_ab_AB"] = {{'a', "S_ab_BA"}, {'b', "S_ab_BB"}};
    transitions["S_ab_BA"] = {{'a', "S_ab_AA"}, {'b', "S_ab_AB"}};
    transitions["S_ab_BB"] = {{'a', "S_ab_BA"}, {'b', "S_ab_BB"}};
    transitions["S_ba_AA"] = {{'a', "S_ba_AA"}, {'b', "S_ba_AB"}};
    transitions["S_ba_AB"] = {{'a', "S_ba_BA"}, {'b', "S_ba_BB"}};
    transitions["S_ba_BA"] = {{'a', "S_ba_AA"}, {'b', "S_ba_AB"}};
    transitions["S_ba_BB"] = {{'a', "S_ba_BA"}, {'b', "S_ba_BB"}};
    transitions["S_bb_AA"] = {{'a', "S_bb_AA"}, {'b', "S_bb_AB"}};
    transitions["S_bb_AB"] = {{'a', "S_bb_BA"}, {'b', "S_bb_BB"}};
    transitions["S_bb_BA"] = {{'a', "S_bb_AA"}, {'b', "S_bb_AB"}};
    transitions["S_bb_BB"] = {{'a', "S_bb_BA"}, {'b', "S_bb_BB"}};
    string startState = "q0";
    set<string> finalStates = {
        "S_aa_AA", 
        "S_ab_AB", 
        "S_ba_BA", 
        "S_bb_BB"
    };
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
        if (transitions.find(currentState) == transitions.end()) {
            cerr << "Error: Reached undefined state: " << currentState << endl;
            cout << "Result: Rejected\n" << endl;
            return false;
        }
        string nextState = transitions[currentState][symbol];
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
        "a",
        "aa",
        "aba",
        "aaaa",     // aa == aa
        "abab",     // ab == ab
        "baba",     // ba == ba
        "bbbb",     // bb == bb
        "aaab",     // aa != ab
        "bbaa",     // bb != aa
        "abba",     // ab != ba
        "aabaa",    // aa == aa
        "babbb",    // bb == bb
        "babab",    // ab != ab ... oh wait, prefix "ba", suffix "ab". REJECT
        "bababa",   // ba == ba
        "bbaba",    // bb != ba
        "aaaaa"     // aa == aa
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
