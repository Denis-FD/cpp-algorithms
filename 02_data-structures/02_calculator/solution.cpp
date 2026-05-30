#include <iostream>
#include <sstream>
#include <stack>
#include <string>

int FloorDiv(int a, int b) {
    int res = a / b;
    if (a % b < 0) {
        --res;
    }
    return res;
}

int main() {
    std::string line;
    std::getline(std::cin, line);

    std::istringstream in(line);

    std::stack<int> numbers;
    std::string token;

    while (in >> token) {
        if (token.size() == 1 && !std::isdigit(token[0])) {
            if (numbers.size() < 2) {
                std::cout << "error" << '\n';
                break;
            }
            int b = numbers.top();
            numbers.pop();
            int a = numbers.top();
            numbers.pop();

            char op = token[0];
            if (op == '+') {
                numbers.push(a + b);
            } else if (op == '-') {
                numbers.push(a - b);
            } else if (op == '*') {
                numbers.push(a * b);
            } else if (op == '/') {
                numbers.push(FloorDiv(a, b));
            } else {
                std::cout << "error" << '\n';
                break;
            }
        } else {
            numbers.push(std::stoi(token));
        }
    }

    std::cout << numbers.top() << '\n';

    return 0;
}
