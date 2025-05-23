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

    int size = static_cast<int>(str.size());
    std::vector<int> prefix(size, 0);

    for (int idx = 1; idx < size; ++idx) {
        int prev = prefix[idx - 1];
        while (prev > 0 && str[idx] != str[prev]) {
            prev = prefix[prev - 1];
        }
        if (str[idx] == str[prev]) {
            ++prev;
        }
        prefix[idx] = prev;
    }

    int period = size - prefix[size - 1];
    std::cout << period << '\n';

    return 0;
}
