#ifndef REMOTE_JUDGE
struct Node {
    int value;
    Node* left = nullptr;
    Node* right = nullptr;
    Node(Node* left, Node* right, int value) : value(value), left(left), right(right) {}
};
#endif
#ifdef REMOTE_JUDGE
#include "solution.h"
#endif
#include <cassert>

Node* remove(Node* root, int key) {
    if (!root) {
        return nullptr;
    }

    if (key < root->value) {
        root->left = remove(root->left, key);
    } else if (key > root->value) {
        root->right = remove(root->right, key);
    } else {
        // 1. Нет детей
        if (!root->left && !root->right) {
            return nullptr;
        }
        // 2. Только один ребенок справа
        else if (!root->left) {
            return root->right;
        }
        // 3. Только один ребенок слева
        else if (!root->right) {
            return root->left;
        }
        // 4. Два ребенка
        else {
            Node* min_node = root->right;
            while (min_node->left) {
                min_node = min_node->left;
            }
            root->value = min_node->value;
            root->right = remove(root->right, min_node->value);
        }
    }
    return root;
}

#ifndef REMOTE_JUDGE
void test() {
    Node node1({nullptr, nullptr, 2});
    Node node2({&node1, nullptr, 3});
    Node node3({nullptr, &node2, 1});
    Node node4({nullptr, nullptr, 6});
    Node node5({&node4, nullptr, 8});
    Node node6({&node5, nullptr, 10});
    Node node7({&node3, &node6, 5});
    Node* newHead = remove(&node7, 10);
    assert(newHead->value == 5);
    assert(newHead->right == &node5);
    assert(newHead->right->value == 8);
}

int main() {
    test();
}
#endif
