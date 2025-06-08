#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;

    Node(char ch, int freq) : ch(ch), freq(freq), left(nullptr), right(nullptr) {}
    Node(Node* l, Node* r) : ch(0), freq(l->freq + r->freq), left(l), right(r) {}
};

struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

void buildCodes(Node* node, const string& str, unordered_map<char, string>& codes) {
    if (!node->left && !node->right) {
        codes[node->ch] = str.empty() ? "0" : str;
        return;
    }
    if (node->left) buildCodes(node->left, str + "0", codes);
    if (node->right) buildCodes(node->right, str + "1", codes);
}

int main() {
    string s;
    cin >> s;

    unordered_map<char, int> freq;
    for (char c : s) freq[c]++;

    priority_queue<Node*, vector<Node*>, Compare> pq;
    for (auto& p : freq) {
        pq.push(new Node(p.first, p.second));
    }

    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();
        pq.push(new Node(left, right));
    }

    Node* root = pq.top();
    unordered_map<char, string> codes;
    buildCodes(root, "", codes);

    string encoded;
    for (char c : s) encoded += codes[c];

    cout << codes.size() << " " << encoded.size() << "\n";
    for (auto& p : codes) {
        cout << p.first << ": " << p.second << "\n";
    }
    cout << encoded << "\n";

    return 0;
}
