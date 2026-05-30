#include <iostream>
#include <queue>
#include <vector>

using Field = std::vector<std::vector<char>>;

struct Point {
    int x;
    int y;

    Point operator+(const Point& other) const {
        return {x + other.x, y + other.y};
    }
};

bool IsInside(Point p, const Field& field) {
    const int n = static_cast<int>(field.size());
    const int m = static_cast<int>(field[0].size());
    return p.x >= 0 && p.x < n && p.y >= 0 && p.y < m;
}

bool IsEarth(Point p, const Field& field) {
    return field[p.x][p.y] == '#';
}

int BFS(Field& field, Point start) {
    const int dx[4] = {-1, 1, 0, 0};
    const int dy[4] = {0, 0, -1, 1};

    std::queue<Point> q;
    q.push(start);
    field[start.x][start.y] = '.';

    int current_island_size = 1;

    while (!q.empty()) {
        Point current = q.front();
        q.pop();

        for (int k = 0; k < 4; ++k) {
            Point next = current + Point{dx[k], dy[k]};

            if (IsInside(next, field) && IsEarth(next, field)) {
                field[next.x][next.y] = '.';
                q.push(next);
                ++current_island_size;
            }
        }
    }

    return current_island_size;
}

int main() {
    int n, m;
    std::cin >> n >> m;

    Field field(n, std::vector<char>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cin >> field[i][j];
        }
    }

    int island_count = 0;
    int max_island_size = 0;

    for (int x = 0; x < n; ++x) {
        for (int y = 0; y < m; ++y) {
            Point point{x, y};
            if (IsEarth(point, field)) {
                ++island_count;
                int current_island_size = BFS(field, point);
                max_island_size = std::max(max_island_size, current_island_size);
            }
        }
    }

    std::cout << island_count << ' ' << max_island_size << '\n';
}
