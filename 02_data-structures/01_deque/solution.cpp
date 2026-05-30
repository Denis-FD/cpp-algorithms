#include <iostream>
#include <optional>
#include <vector>

class DequeRingBuffer {
public:
    explicit DequeRingBuffer(int n) : deque_(n), max_n_(n) {}

    bool PushBack(int value) {
        if (IsFull()) {
            return false;
        }
        deque_[tail_] = value;
        tail_ = Next(tail_);
        ++size_;
        return true;
    }

    bool PushFront(int value) {
        if (IsFull()) {
            return false;
        }
        head_ = Prev(head_);
        deque_[head_] = value;
        ++size_;
        return true;
    }

    std::optional<int> PopFront() {
        if (IsEmpty()) {
            return std::nullopt;
        }
        int value = deque_[head_];
        head_ = Next(head_);
        --size_;
        return value;
    }

    std::optional<int> PopBack() {
        if (IsEmpty()) {
            return std::nullopt;
        }
        tail_ = Prev(tail_);
        int value = deque_[tail_];
        --size_;
        return value;
    }

    bool IsEmpty() const noexcept {
        return size_ == 0;
    }

    bool IsFull() const noexcept {
        return size_ == max_n_;
    }

private:
    std::vector<int> deque_;
    int max_n_ = 0;
    int size_ = 0;
    int head_ = 0;
    int tail_ = 0;

    int Next(int index) const noexcept {
        return (index + 1) % max_n_;
    }

    int Prev(int index) const noexcept {
        return (max_n_ + index - 1) % max_n_;
    }
};

void Run(std::istream& in) {
    int n_command, m_deque;
    in >> n_command >> m_deque;

    DequeRingBuffer deque(m_deque);

    std::string command;
    while (n_command-- > 0) {
        in >> command;

        if (command == "push_back") {
            int x;
            in >> x;
            if (!deque.PushBack(x)) {
                std::cout << "error" << '\n';
            }
        } else if (command == "push_front") {
            int x;
            in >> x;
            if (!deque.PushFront(x)) {
                std::cout << "error" << '\n';
            }
        } else if (command == "pop_front") {
            if (auto opt = deque.PopFront()) {
                std::cout << *opt << '\n';
            } else {
                std::cout << "error" << '\n';
            }
        } else if (command == "pop_back") {
            if (auto opt = deque.PopBack()) {
                std::cout << *opt << '\n';
            } else {
                std::cout << "error" << '\n';
            }
        }
    }
}

int main() {
    Run(std::cin);
    return 0;
}
