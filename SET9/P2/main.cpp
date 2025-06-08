#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

int main() {
    std::string s;
    std::getline(std::cin, s);

    std::unordered_map<std::string, int> d;
    for (int i = 0; i < 128; ++i) {
        d[std::string(1, i)] = i;
    }

    int c = 128;
    std::string t;
    std::vector<int> r;

    for (char x : s) {
        std::string tx = t + x;
        if (d.count(tx)) {
            t = tx;
        } else {
            r.push_back(d[t]);
            d[tx] = c++;
            t = std::string(1, x);
        }
    }

    if (!t.empty()) {
        r.push_back(d[t]);
    }

    std::cout << r.size() << "\n";
    for (int i = 0; i < r.size(); ++i) {
        if (i) std::cout << " ";
        std::cout << r[i];
    }
    std::cout << "\n";
    return 0;
}
