#include <bits/stdc++.h>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string s;
    if (!(std::cin >> s)) return 0;

    std::string t;
    t.reserve(s.size() * 2 + 1);
    for (char c : s) {
        t.push_back('#');
        t.push_back(c);
    }
    t.push_back('#');

    int m = t.size();
    std::vector<int> p(m);
    int center = 0, right = 0;
    long long ans = 0;

    for (int i = 0; i < m; ++i) {
        int mirror = 2 * center - i;
        if (i < right) p[i] = std::min(right - i, p[mirror]);
        while (i - 1 - p[i] >= 0 && i + 1 + p[i] < m && t[i - 1 - p[i]] == t[i + 1 + p[i]]) ++p[i];
        if (i + p[i] > right) {
            center = i;
            right = i + p[i];
        }
        ans += (p[i] + 1) / 2;
    }

    std::cout << ans << '\n';
    return 0;
}

