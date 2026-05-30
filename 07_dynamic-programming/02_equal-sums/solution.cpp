#include <iostream>
#include <numeric>
#include <vector>

bool CanSplitEqualSum(const std::vector<int>& nums) {
    if (nums.empty()) {
        return true;
    }

    const int total_sum = std::accumulate(nums.begin(), nums.end(), 0);

    if (total_sum % 2 != 0) {
        return false;
    }

    const int sum = total_sum / 2;

    std::vector<bool> dp(sum + 1, false);
    dp[0] = true;

    for (int num : nums) {
        if (num > sum) {
            return false;
        }

        for (int s = sum; s >= num; --s) {
            dp[s] = dp[s] || dp[s - num];
        }

        if (dp[sum]) {
            return true;
        }
    }

    return false;
}

int main() {
    int n;
    std::cin >> n;

    std::vector<int> scores(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> scores[i];
    }

    if (CanSplitEqualSum(scores)) {
        std::cout << "True" << '\n';
    } else {
        std::cout << "False" << '\n';
    }
}
