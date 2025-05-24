#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <sstream>
#include <algorithm>

struct TrieNode {
    int children[26];
    int suffix_link;
    int dictionary_link;
    std::vector<int> matched_patterns;

    TrieNode() {
        std::fill(std::begin(children), std::end(children), -1);
        suffix_link = 0;
        dictionary_link = -1;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string input_text;
    if (!(std::cin >> input_text)) {
        return 0;
    }

    int pattern_count;
    std::cin >> pattern_count;

    std::vector<TrieNode> automaton(1);
    std::vector<int> pattern_lengths(pattern_count);

    for (int i = 0; i < pattern_count; ++i) {
        std::string pattern;
        std::cin >> pattern;
        pattern_lengths[i] = static_cast<int>(pattern.size());
        int node = 0;
        for (char character : pattern) {
            int idx = character - 'a';
            if (automaton[node].children[idx] == -1) {
                automaton[node].children[idx] = static_cast<int>(automaton.size());
                automaton.emplace_back();
            }
            node = automaton[node].children[idx];
        }
        automaton[node].matched_patterns.push_back(i);
    }

    std::queue<int> bfs_queue;
    for (int c = 0; c < 26; ++c) {
        int child = automaton[0].children[c];
        if (child != -1) {
            automaton[child].suffix_link = 0;
            bfs_queue.push(child);
        } else {
            automaton[0].children[c] = 0;
        }
    }

    while (!bfs_queue.empty()) {
        int current = bfs_queue.front();
        bfs_queue.pop();
        int link = automaton[current].suffix_link;
        automaton[current].dictionary_link = automaton[link].matched_patterns.empty() ? automaton[link].dictionary_link : link;

        for (int c = 0; c < 26; ++c) {
            int next = automaton[current].children[c];
            if (next != -1) {
                automaton[next].suffix_link = automaton[link].children[c];
                bfs_queue.push(next);
            } else {
                automaton[current].children[c] = automaton[link].children[c];
            }
        }
    }

    std::vector<std::vector<int>> occurrences(pattern_count);
    int current_state = 0;
    for (int i = 0; i < static_cast<int>(input_text.size()); ++i) {
        current_state = automaton[current_state].children[input_text[i] - 'a'];
        for (int v = current_state; v != -1; v = automaton[v].dictionary_link) {
            for (int id : automaton[v].matched_patterns) {
                occurrences[id].push_back(i - pattern_lengths[id] + 2);
            }
        }
    }

    std::ostringstream result;
    for (int i = 0; i < pattern_count; ++i) {
        result << occurrences[i].size();
        for (int pos : occurrences[i]) {
            result << ' ' << pos;
        }
        result << '\n';
    }

    std::cout << result.str();
    return 0;
}

