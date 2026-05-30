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

template <typename T>
void SiftDown(std::vector<T>& heap, int idx) {
    const int n = static_cast<int>(heap.size());

    while (true) {
        int left = idx * 2 + 1;
        if (left >= n) {
            break;
        }
        int right = idx * 2 + 2;
        int idx_smallest = left;

        if (right < n && heap[right] < heap[left]) {
            idx_smallest = right;
        }

        if (heap[idx_smallest] < heap[idx]) {
            std::swap(heap[idx], heap[idx_smallest]);
            idx = idx_smallest;
        } else {
            break;
        }
    }
}

template <typename T>
std::vector<T> BuildHeap(const std::vector<T>& vec) {
    std::vector<T> heap = vec;
    const int n = static_cast<int>(heap.size());
    for (int i = n / 2 - 1; i >= 0; --i) {
        SiftDown(heap, i);
    }
    return heap;
}

template <typename T>
T PopMin(std::vector<T>& heap) {
    T result = heap[0];
    heap[0] = heap.back();
    heap.pop_back();
    SiftDown(heap, 0);
    return result;
}

template <typename T>
void HeapSort(std::vector<T>& vec) {
    const int n = static_cast<int>(vec.size());
    if (n < 2) {
        return;
    }

    auto heap = BuildHeap(vec);

    for (int i = 0; i < n; ++i) {
        vec[i] = PopMin(heap);
    }
}

int main() {
    int n;
    std::cin >> n;

    std::vector<Player> players(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> players[i].name >> players[i].score >> players[i].penalty;
    }

    HeapSort(players);

    for (const auto& player : players) {
        std::cout << player.name << '\n';
    }
}
