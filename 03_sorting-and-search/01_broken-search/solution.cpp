#include <cassert>
#include <vector>

int broken_search(const std::vector<int>& vec, int k) {
    if (vec.empty()) {
        return -1;
    }

    int left = 0;
    int right = static_cast<int>(vec.size()) - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (vec[mid] == k) {
            return mid;
        }

        bool move_right;

        if (vec[left] <= vec[mid]) {  // if left sorted
            move_right = (k < vec[left] || k >= vec[mid]);
        } else {
            move_right = (k > vec[mid] && k <= vec[right]);
        }

        if (move_right) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return -1;
}

void test() {
    std::vector<int> arr = {19, 21, 100, 101, 1, 4, 5, 7, 12};
    assert(6 == broken_search(arr, 5));
}
