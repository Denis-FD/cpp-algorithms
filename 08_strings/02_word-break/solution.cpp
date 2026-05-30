#include <array>
#include <iostream>
#include <string>
#include <vector>

class Trie {
    static constexpr int ALPHABET_LENGTH = 26;

    struct Node {
        std::array<int, ALPHABET_LENGTH> next;
        bool is_terminal = false;

        Node() {
            next.fill(-1);
        }
    };

public:
    Trie() {
        nodes_.emplace_back();
    }

    void Add(const std::string& word) {
        int node = 0;
        for (char ch : word) {
            int letter = ch - 'a';
            if (nodes_[node].next[letter] == -1) {
                int new_node = static_cast<int>(nodes_.size());
                nodes_[node].next[letter] = new_node;
                nodes_.emplace_back();
            }
            node = nodes_[node].next[letter];
        }
        nodes_[node].is_terminal = true;
    }

    int GetRoot() const {
        return 0;
    }

    int Next(int node, char ch) const {
        if (node == -1) {
            return -1;
        }
        int letter = ch - 'a';
        return nodes_[node].next[letter];
    }

    bool IsTerminal(int node) const {
        if (node == -1) {
            return false;
        }
        return nodes_[node].is_terminal;
    }

private:
    std::vector<Node> nodes_;
};

bool CanSplitTextFromWords(const std::string& text, const Trie& trie) {
    int text_size = static_cast<int>(text.size());
    std::vector<bool> dp(text_size + 1, false);
    dp[0] = true;

    for (int start = 0; start < text_size; ++start) {
        if (!dp[start]) {
            continue;
        }

        int node = trie.GetRoot();
        for (int end = start; end < text_size; ++end) {
            node = trie.Next(node, text[end]);

            if (node == -1) {
                break;
            }

            if (trie.IsTerminal(node)) {
                dp[end + 1] = true;
            }
        }

        if (dp[text_size]) {
            break;
        }
    }

    return dp[text_size];
}

int main() {
    std::string text;
    std::cin >> text;

    int n;
    std::cin >> n;

    Trie trie;
    std::string word;
    for (int i = 0; i < n; ++i) {
        std::cin >> word;
        trie.Add(word);
    }

    std::cout << (CanSplitTextFromWords(text, trie) ? "YES" : "NO") << '\n';
}
