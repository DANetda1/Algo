#include <iostream>
#include <vector>
#include <string>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string str;
    if (!(std::cin >> str)) {
        return 0;
    }

    int len = static_cast<int>(str.length());
    std::vector<int> prefix(len, 0);

    for (int idx = 1; idx < len; ++idx) {
        int prev = prefix[idx - 1];
        while (prev > 0 && str[idx] != str[prev]) {
            prev = prefix[prev - 1];
        }
        if (str[idx] == str[prev]) {
            ++prev;
        }
        prefix[idx] = prev;
    }

    for (int i = 0; i < len; ++i) {
        std::cout << prefix[i];
        if (i + 1 < len) {
            std::cout << ' ';
        }
    }
    std::cout << '\n';

    return 0;
}
