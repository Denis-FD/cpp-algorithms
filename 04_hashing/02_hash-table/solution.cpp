#include <cstdint>
#include <iostream>
#include <list>
#include <optional>
#include <vector>

class HashTable {
public:
    HashTable() : buckets_(BUCKET_COUNT) {}

    void Put(int key, int value) {
        size_t idx = Hash(key);

        for (auto& node : buckets_[idx]) {
            if (node.key == key) {
                node.value = value;
                return;
            }
        }

        buckets_[idx].push_back({key, value});
        ++size_;
    }

    std::optional<int> Get(int key) const {
        size_t idx = Hash(key);

        if (!buckets_[idx].empty()) {
            for (const auto& node : buckets_[idx]) {
                if (node.key == key) {
                    return node.value;
                }
            }
        }

        return std::nullopt;
    }

    std::optional<int> Delete(int key) {
        size_t idx = Hash(key);

        for (auto it = buckets_[idx].begin(); it != buckets_[idx].end(); ++it) {
            if (it->key == key) {
                int value = it->value;
                buckets_[idx].erase(it);
                --size_;
                return value;
            }
        }

        return std::nullopt;
    }

private:
    struct Node {
        int key;
        int value;
    };

    static constexpr size_t BUCKET_COUNT = 200'003;

    std::vector<std::list<Node>> buckets_;
    size_t size_ = 0;

    size_t Hash(int key) const {
        constexpr int64_t a = 47;

        int64_t h = (static_cast<int64_t>(key) * a + a) % BUCKET_COUNT;
        if (h < 0) {
            h += BUCKET_COUNT;
        }

        return static_cast<size_t>(h);
    }
};

void PrintOpt(const std::optional<int>& opt) {
    if (opt) {
        std::cout << *opt << '\n';
    } else {
        std::cout << "None" << '\n';
    }
}

int main() {
    HashTable table;

    int n;
    std::cin >> n;

    for (int i = 0; i < n; ++i) {
        std::string command;
        std::cin >> command;
        if (command == "put") {
            int key, value;
            std::cin >> key >> value;
            table.Put(key, value);
        } else if (command == "get") {
            int key;
            std::cin >> key;
            PrintOpt(table.Get(key));
        } else if (command == "delete") {
            int key;
            std::cin >> key;
            PrintOpt(table.Delete(key));
        } else {
            break;
        }
    }
}
