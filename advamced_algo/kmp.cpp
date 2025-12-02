#include <iostream>
#include <vector>

using namespace std;

void lpsTable(string p, vector<int> &lps) {
    for (int i = 1; i < p.size(); i++) {
        int j = lps[i - 1];
        while (j > 0 && p[i] != p[j]) {
            j = lps[j - 1];
        }
        if (p[i] == p[j]) {
            j++;
        }
        lps[i] = j;
    }
}

void matchAndSearch(string s, string p, vector<int> &lps) {
    int pre = 0;
    int suf = 0;
    int comparisons = 0;  // Counter for number of comparisons

    while (pre < p.size() && suf < s.size()) {
        comparisons++;  // Increment for each comparison

        if (s[suf] == p[pre]) {
            suf++;
            pre++;
        } else {
            if (pre == 0) {
                suf++;
            } else {
                pre = lps[pre - 1];
            }
        }
    }

    if (pre == p.size()) {
        cout << "Pattern found at index: " << suf - pre << endl;
    }

    cout << "Total comparisons: " << comparisons << endl;  // Output total comparisons
}

void kmp(string s, string p) {
    vector<int> lps(p.size(), 0);
    // creating lps table
    lpsTable(p, lps);

    // Match and search
    matchAndSearch(s, p, lps);
}

int main() {
    string s = "ababcabcabababd";
    string p = "ababd";

    kmp(s, p);

    return 0;
}
