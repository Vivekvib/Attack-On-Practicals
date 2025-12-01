#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;
class DFA {
private:
    static const int S_START = 0;
    static const int S_A = 1;
    static const int S_B = 2
    static const int S_AA = 3;
    static const int S_AB = 4;
    static const int S_BA = 5;
    static const int S_BB = 6;
    static const int S_L3_AA_A = 7;
    static const int S_L3_AA_B = 8;
    static const int S_L3_AB_A = 9;
    static const int S_L3_AB_B = 10;
    static const int S_L3_BA_A = 11;
    static const int S_L3_BA_B = 12;
    static const int S_L3_BB_A = 13;
    static const int S_L3_BB_B = 14;
    static const int LOOP_AA_aa = 15; // Accepting (Matches AA)
    static const int LOOP_AA_ab = 16;
    static const int LOOP_AA_ba = 17;
    static const int LOOP_AA_bb = 18;
    static const int LOOP_AB_aa = 19;
    static const int LOOP_AB_ab = 20; // Accepting (Matches AB)
    static const int LOOP_AB_ba = 21;
    static const int LOOP_AB_bb = 22;
    static const int LOOP_BA_aa = 23;
    static const int LOOP_BA_ab = 24;
    static const int LOOP_BA_ba = 25; // Accepting (Matches BA)
    static const int LOOP_BA_bb = 26;
    static const int LOOP_BB_aa = 27;
    static const int LOOP_BB_ab = 28;
    static const int LOOP_BB_ba = 29;
    static const int LOOP_BB_bb = 30;
    static const int TOTAL_STATES = 31;
    vector<vector<int>> transitionTable;
    vector<bool> finalStates;
    vector<string> stateDescriptions;
public:
    DFA() {
        transitionTable.resize(TOTAL_STATES, vector<int>(2)); 
        finalStates.resize(TOTAL_STATES, false);
        stateDescriptions.resize(TOTAL_STATES);
        setupDFA();
    }
    void setupDFA() {
        stateDescriptions[S_START] = "Start";
        addTransition(S_START, S_A, S_B);
        stateDescriptions[S_A] = "Got 'a'";
        stateDescriptions[S_B] = "Got 'b'";
        addTransition(S_A, S_AA, S_AB);
        addTransition(S_B, S_BA, S_BB);
        stateDescriptions[S_AA] = "Target: AA (Len 2)";
        stateDescriptions[S_AB] = "Target: AB (Len 2)";
        stateDescriptions[S_BA] = "Target: BA (Len 2)";
        stateDescriptions[S_BB] = "Target: BB (Len 2)";
        addTransition(S_AA, S_L3_AA_A, S_L3_AA_B);
        addTransition(S_AB, S_L3_AB_A, S_L3_AB_B);
        addTransition(S_BA, S_L3_BA_A, S_L3_BA_B);
        addTransition(S_BB, S_L3_BB_A, S_L3_BB_B);
        // Transitions go to Loop States (Level 4)
        stateDescriptions[S_L3_AA_A] = "Target AA | Suffix: aa (Len 3)";
        stateDescriptions[S_L3_AA_B] = "Target AA | Suffix: ab (Len 3)";
        addTransition(S_L3_AA_A, LOOP_AA_aa, LOOP_AA_ab);
        addTransition(S_L3_AA_B, LOOP_AA_ba, LOOP_AA_bb);
        stateDescriptions[S_L3_AB_A] = "Target AB | Suffix: ba (Len 3)"; // Prev was b (from ab), now a -> ba
        stateDescriptions[S_L3_AB_B] = "Target AB | Suffix: bb (Len 3)";
        addTransition(S_L3_AB_A, LOOP_AB_aa, LOOP_AB_ab);
        addTransition(S_L3_AB_B, LOOP_AB_ba, LOOP_AB_bb);
        stateDescriptions[S_L3_BA_A] = "Target BA | Suffix: aa (Len 3)";
        stateDescriptions[S_L3_BA_B] = "Target BA | Suffix: ab (Len 3)";
        addTransition(S_L3_BA_A, LOOP_BA_aa, LOOP_BA_ab);
        addTransition(S_L3_BA_B, LOOP_BA_ba, LOOP_BA_bb);
        stateDescriptions[S_L3_BB_A] = "Target BB | Suffix: ba (Len 3)";
        stateDescriptions[S_L3_BB_B] = "Target BB | Suffix: bb (Len 3)";
        addTransition(S_L3_BB_A, LOOP_BB_aa, LOOP_BB_ab);
        addTransition(S_L3_BB_B, LOOP_BB_ba, LOOP_BB_bb);
        setupLoopBlock(LOOP_AA_aa, "AA", S_AA);
        setupLoopBlock(LOOP_AB_aa, "AB", S_AB);
        setupLoopBlock(LOOP_BA_aa, "BA", S_BA);
        setupLoopBlock(LOOP_BB_aa, "BB", S_BB);
        finalStates[LOOP_AA_aa] = true;
        finalStates[LOOP_AB_ab] = true;
        finalStates[LOOP_BA_ba] = true;
        finalStates[LOOP_BB_bb] = true;
    }
    void addTransition(int from, int toA, int toB) {
        transitionTable[from][0] = toA;
        transitionTable[from][1] = toB;
    }
    void setupLoopBlock(int startId, string targetName, int targetType) {
        int id_aa = startId;
        int id_ab = startId + 1;
        int id_ba = startId + 2;
        int id_bb = startId + 3;
        stateDescriptions[id_aa] = "Target " + targetName + " | Suffix: aa";
        stateDescriptions[id_ab] = "Target " + targetName + " | Suffix: ab";
        stateDescriptions[id_ba] = "Target " + targetName + " | Suffix: ba";
        stateDescriptions[id_bb] = "Target " + targetName + " | Suffix: bb";
        addTransition(id_aa, id_aa, id_ab);
        addTransition(id_ab, id_ba, id_bb);
        addTransition(id_ba, id_aa, id_ab);
        addTransition(id_bb, id_ba, id_bb);
    }
    bool simulate(string input) {
        int currentState = S_START;
        cout << "\n--------------------------------------------------" << endl;
        cout << "Processing: \"" << input << "\"" << endl;
        cout << "Start: " << stateDescriptions[currentState] << endl;
        for (char c : input) {
            if (c != 'a' && c != 'b') {
                cout << "Error: Invalid char '" << c << "'" << endl;
                return false;
            }
            int inputIdx = (c == 'a') ? 0 : 1;
            int nextState = transitionTable[currentState][inputIdx];
            cout << "  Input '" << c << "' -> " << stateDescriptions[nextState] << endl;
            currentState = nextState;
        }
        cout << "End State: " << stateDescriptions[currentState] << endl;
        if (finalStates[currentState]) {
            cout << "Result: ACCEPTED" << endl;
            return true;
        } else {
            cout << "Result: REJECTED" << endl;
            return false;
        }
    }
};
int main() {
    DFA dfa;
    cout << "=== DFA Simulator ===" << endl;
    cout << "Language: Strings (len >= 4) where first 2 chars == last 2 chars." << endl;
    cout << "Alphabet: {a, b}" << endl;
    string input;
    while (true) {
        cout << "\nEnter string (or 'exit'): ";
        cin >> input;
        if (input == "exit") break;
        dfa.simulate(input);
    }
    return 0;
}
