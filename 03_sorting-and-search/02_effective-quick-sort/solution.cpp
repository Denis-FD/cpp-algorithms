#include <iostream>
#include <vector>

struct Player {
    std::string name;
    int score;
    int penalty;

    bool operator<(const Player& p) const {
        if (score != p.score) {
            return score > p.score;
        }
        if (penalty != p.penalty) {
            return penalty < p.penalty;
        }
        return name < p.name;
    }
};

void PrintNames(const std::vector<Player>& players) {
    for (const auto& player : players) {
        std::cout << player.name << '\n';
    }
}

void QuickSortImpl(std::vector<Player>& vec, int left, int right) {
    if (left >= right) {
        return;
    }

    int i = left;
    int j = right;
    int mid = left + (right - left) / 2;

    auto pivot = vec[mid];

    while (i <= j) {
        while (i <= right && vec[i] < pivot) {
            ++i;
        }
        while (j >= left && pivot < vec[j]) {
            --j;
        }

        if (i <= j) {
            std::swap(vec[i], vec[j]);
            ++i;
            --j;
        }
    }

    QuickSortImpl(vec, left, j);
    QuickSortImpl(vec, i, right);
}

void QuickSort(std::vector<Player>& vec) {
    if (vec.empty()) {
        return;
    }
    QuickSortImpl(vec, 0, static_cast<int>(vec.size()) - 1);
}

int main() {
    int n;
    std::cin >> n;

    std::vector<Player> vec;
    vec.reserve(n);

    for (int i = 0; i < n; ++i) {
        Player p;
        std::cin >> p.name >> p.score >> p.penalty;
        vec.push_back(p);
    }

    QuickSort(vec);
    PrintNames(vec);
}
