#include <iostream>
#include <vector>

int main() {
    int k;
    std::cin >> k;
    constexpr int players = 2;

    constexpr int row = 4;
    constexpr int col = 4;
    constexpr int n_val = 9;  // values from 1 to 9

    std::vector<int> buckets(n_val);

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            char ch;
            std::cin >> ch;
            if (ch != '.') {
                int value = static_cast<int>(ch - '0');
                ++buckets[value - 1];
            }
        }
    }

    const int max_pushes = k * players;
    int max_points = 0;
    for (int i = 0; i < n_val; ++i) {
        if (buckets[i] > 0 && buckets[i] <= max_pushes) {
            ++max_points;
        }
    }

    std::cout << max_points;

    return 0;
}
