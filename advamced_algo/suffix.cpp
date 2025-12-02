#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

struct Node {
    unordered_map<char, Node*> children;
};

class SuffixTree {
    Node* root;
    
public:
    SuffixTree(string text) {
        root = new Node();
        text += '$';
        
        // Insert each suffix
        for (int i = 0; i < text.size(); i++) {
            Node* node = root;
            for (int j = i; j < text.size(); j++) {
                char c = text[j];
                if (node->children.find(c) == node->children.end()) {
                    node->children[c] = new Node();
                }
                node = node->children[c];
            }
        }
    }
    
    bool search(string pattern) {
        Node* node = root;
        for (char c : pattern) {
            if (node->children.find(c) == node->children.end()) {
                return false;
            }
            node = node->children[c];
        }
        return true;
    }
};

int main() {
    SuffixTree tree("basically");
    cout << tree.search("bas") << endl;  // 1 (true) 0 (false)
    return 0;
}
