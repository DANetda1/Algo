#include <iostream>
#include <vector>
#include <string>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string pattern, text;
    if (!std::getline(std::cin, pattern)) {
        return 0;
    }
    if (!std::getline(std::cin, text)) {
        text.clear();
    }

    int pattern_length = static_cast<int>(pattern.size());
    int text_length = static_cast<int>(text.size());

    if (pattern_length == 0 || pattern_length > text_length) {
        std::cout << 0 << '\n';
        return 0;
    }

    std::vector<int> prefix_function(pattern_length, 0);
    for (int i = 1; i < pattern_length; ++i) {
        int k = prefix_function[i - 1];
        while (k > 0 && pattern[i] != pattern[k]) {
            k = prefix_function[k - 1];
        }
        if (pattern[i] == pattern[k]) {
            ++k;
        }
        prefix_function[i] = k;
    }

    std::vector<int> occurrences;
    occurrences.reserve(1000000);

    int matched = 0;
    for (int i = 0; i < text_length; ++i) {
        while (matched > 0 && text[i] != pattern[matched]) {
            matched = prefix_function[matched - 1];
        }
        if (text[i] == pattern[matched]) {
            ++matched;
        }
        if (matched == pattern_length) {
            occurrences.push_back(i - pattern_length + 1);
            matched = prefix_function[matched - 1];
        }
    }

    std::cout << occurrences.size() << '\n';
    for (int index : occurrences) {
        std::cout << index << '\n';
    }

    return 0;
}
