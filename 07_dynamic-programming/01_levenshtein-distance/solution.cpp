#include <iostream>
#include <string>
#include <vector>

int LevenshteinDistance(const std::string& s, const std::string& t) {
    if (t.size() > s.size()) {
        return LevenshteinDistance(t, s);
    }

    const int n = static_cast<int>(s.size());
    const int m = static_cast<int>(t.size());

    std::vector<int> dp(m + 1);

    for (int j = 1; j <= m; ++j) {
        dp[j] = j;
    }

    for (int i = 1; i <= n; ++i) {
        int prev_diag = dp[0];
        dp[0] = i;

        for (int j = 1; j <= m; ++j) {
            int upper = dp[j];
            int left = dp[j - 1];
            int diag = prev_diag + (s[i - 1] != t[j - 1]);

            dp[j] = std::min(upper + 1, std::min(left + 1, diag));

            prev_diag = upper;
        }
    }

    return dp[m];
}

int main() {
    std::string s, t;
    std::cin >> s;
    std::cin >> t;

    std::cout << LevenshteinDistance(s, t) << '\n';
}
