#include <iostream>
#include <vector>

std::vector<int> FindNearestZero(const std::vector<int>& v) {
    const int n = static_cast<int>(v.size());
    std::vector<int> res(n);

    int zero_idx = -n;

    for (int i = 0; i < n; ++i) {
        if (v[i] == 0) {
            zero_idx = i;
            res[i] = 0;
        } else {
            res[i] = i - zero_idx;
        }
    }

    for (int j = zero_idx; j >= 0; --j) {
        if (v[j] == 0) {
            zero_idx = j;
        } else {
            res[j] = std::min(res[j], zero_idx - j);
        }
    }

    return res;
}

void PrintVec(const std::vector<int>& v) {
    for (int number : v) {
        std::cout << number << ' ';
    }
    std::cout << '\n';
}

int main() {
    int n;
    std::cin >> n;

    std::vector<int> street(n);

    for (int i = 0; i < n; ++i) {
        std::cin >> street[i];
    }

    PrintVec(FindNearestZero(street));

    return 0;
}
