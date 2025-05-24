#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

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

    const int pattern_size = static_cast<int>(pattern.size());
    const int text_size = static_cast<int>(text.size());

    if (pattern_size == 0 || pattern_size > text_size) {
        std::cout << 0 << '\n';
        return 0;
    }

    constexpr int alphabet_size = 256;
    int shift_table[alphabet_size];
    std::fill(shift_table, shift_table + alphabet_size, pattern_size);

    for (int idx = 0; idx < pattern_size - 1; ++idx) {
        shift_table[static_cast<unsigned char>(pattern[idx])] = pattern_size - 1 - idx;
    }

    std::vector<int> matches;
    matches.reserve(1000000);

    int pos = 0;
    while (pos <= text_size - pattern_size) {
        int j = pattern_size - 1;
        while (j >= 0 && pattern[j] == text[pos + j]) {
            --j;
        }
        if (j < 0) {
            matches.push_back(pos);
            pos += (pos + pattern_size < text_size) ? shift_table[static_cast<unsigned char>(text[pos + pattern_size])] : 1;
        } else {
            pos += shift_table[static_cast<unsigned char>(text[pos + pattern_size - 1])];
        }
    }

    std::cout << matches.size() << '\n';
    for (int index : matches) {
        std::cout << index << '\n';
    }

    return 0;
}

