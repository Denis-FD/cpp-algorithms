/*
https://contest.yandex.ru/contest/23815/run-report/156481576/

-- ОПИСАНИЕ --
Реализована сортировка списка участников олимпиады по трем ключам:
score - по убыванию, если равны, то сортируем по:
penalty - по возрастанию, если равны, то сортируем по:
name - по возрастанию (лексикографически).
Сортировка выполняется алгоритмом быстрой сортировки без выделения дополнительной
памяти - in-place quick sort

-- ПРИНЦИП РАБОТЫ --
Для сортировки запускается метод void QuickSortImpl(std::vector<Player>& vec, int left, int right),
где vec - массив игроков олимпиады, left/right — границы текущего диапазона.
В качестве опорного элемента берется значение из середины диапазона: pivot = vec[mid].
Два указателя i и j начинают двигаться с границ диапазона (left и right) и идут навстречу:
i сдвигается вправо, пока vec[i] меньше pivot, j сдвигается влево, пока pivot меньше vec[j].
Когда оба указателя остановились, и i <= j, элементы vec[i] и vec[j] меняются местами,
после чего i увеличивается, а j уменьшается.
После завершения цикла диапазон оказывается разбит на две части:
[left, j] — элементы, которые не больше pivot,
[i, right] — элементы, которые не меньше pivot.
Затем рекурсивно сортируются обе части: [left, j] и [i, right].

-- ДОКАЗАТЕЛЬСТВО КОРРЕКТНОСТИ --
Во время работы цикла поддерживается инвариант: элементы в диапазоне [left, i-1] не должны стоять позже pivot,
а в диапазоне [j+1, right] не должны стоять раньше pivot (по заданному порядку сравнения).
Указатели i и j движутся навстречу, находят первые элементы, стоящие не в своей части, меняют их местами
и сдвигаются внутрь (++i, --j) - инвариант сохраняется.
Когда i > j, диапазон оказывается разбит на две части, сначала идут элементы из [left, j], потом из [i, right].
Рекурсивная сортировка этих частей (база: длина ≤ 1) дает полностью отсортированный массив.

-- ВРЕМЕННАЯ СЛОЖНОСТЬ --
В среднем - O(N log N), где N кол-во участников олимпиады, т.к. на каждом уровне рекурсии выполняется линейное 
разбиение, а средняя глубина рекурсии логарифмическая. В худшем случае, при неудачных разбиениях - O(N^2).

-- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --
Разбиение выполняется in-place и требует O(1) дополнительной памяти.
Дополнительно используется стек рекурсии: в среднем O(log N), в худшем O(N).
*/

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
