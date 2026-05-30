#include <algorithm>
#include <iostream>
#include <string>

std::string UnpackString(const std::string& packed_string) {
    constexpr size_t MAX_UNPACKED_SIZE = 100000;  // 10^5

    std::string s;
    s.reserve(MAX_UNPACKED_SIZE);

    for (char ch : packed_string) {
        if (ch != ']') {
            s.push_back(ch);
            continue;
        }

        std::string block;
        while (s.back() != '[') {
            block.push_back(s.back());
            s.pop_back();
        }
        s.pop_back();  // remove '['

        std::reverse(block.begin(), block.end());

        int k = s.back() - '0';
        s.pop_back();  // remove digit

        while (k-- > 0) {
            s += block;
        }
    }

    return s;
}

void LongestCommonPrefix(std::string& lcp, const std::string& s) {
    size_t i = 0;
    size_t n = std::min(lcp.size(), s.size());

    while (i < n && lcp[i] == s[i]) {
        ++i;
    }

    lcp.resize(i);
}

int main() {
    int n;  // (1 ≤ n ≤ 1000)
    std::cin >> n;

    std::string lcp;
    std::cin >> lcp;
    lcp = UnpackString(lcp);

    std::string s;
    for (int i = 1; i < n; ++i) {
        std::cin >> s;
        LongestCommonPrefix(lcp, UnpackString(s));
    }

    std::cout << lcp << '\n';
}
