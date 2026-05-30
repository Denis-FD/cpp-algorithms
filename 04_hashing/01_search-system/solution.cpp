#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using Word = std::string;
using Words = std::vector<Word>;
using Document = std::string;
using Documents = std::vector<Document>;
using ID = int;

constexpr size_t MAX_DOCUMENT_COUNT = 10000;
constexpr size_t MAX_RESULTS = 5;

struct WordCountInDoc {
    ID doc_id;
    int count;
};

using WordIndex = std::unordered_map<Word, std::vector<WordCountInDoc>>;

struct DocRelevance {
    ID doc_id;
    int relevance;

    bool operator<(const DocRelevance& rhs) const {
        if (relevance != rhs.relevance) {
            return relevance > rhs.relevance;
        }
        return doc_id < rhs.doc_id;
    }
};

Words SplitWords(const std::string& str) {
    std::istringstream iss{str};
    Words ws;
    Word w;

    while (iss >> w) {
        ws.push_back(w);
    }
    return ws;
}

std::unordered_map<Word, int> DocToWordsFrequency(const Document& str) {
    auto words = SplitWords(str);

    std::unordered_map<Word, int> freq;
    freq.reserve(words.size());

    for (auto& word : words) {
        ++freq[word];
    }

    return freq;
}

WordIndex BuildWordIndex(const Documents& docs) {
    WordIndex idx;

    for (ID id = 1; id <= static_cast<int>(docs.size()); ++id) {
        auto freq = DocToWordsFrequency(docs[id - 1]);

        for (auto& [word, count] : freq) {
            idx[word].push_back(WordCountInDoc{id, count});
        }
    }

    return idx;
}

std::unordered_set<Word> GetUniqueWords(const std::string& str) {
    auto words = SplitWords(str);

    std::unordered_set<Word> unique_words;
    unique_words.reserve(words.size());

    for (auto& word : words) {
        unique_words.insert(word);
    }

    return unique_words;
}

std::vector<int> AccumulateRelevance(const WordIndex& idx, const std::string& request) {
    auto unique_words = GetUniqueWords(request);

    std::vector<int> id_to_sum(MAX_DOCUMENT_COUNT, 0);

    for (auto& word : unique_words) {
        auto it = idx.find(word);
        if (it == idx.end()) {
            continue;
        }

        for (auto& [id, count] : it->second) {
            id_to_sum[id] += count;
        }
    }

    return id_to_sum;
}

std::vector<DocRelevance> SelectTop5Docs(const std::vector<int>& id_to_sum) {
    std::vector<DocRelevance> res;
    res.reserve(MAX_DOCUMENT_COUNT);

    for (ID id = 0; id < MAX_DOCUMENT_COUNT; ++id) {
        if (id_to_sum[id] > 0) {
            res.push_back(DocRelevance{id, id_to_sum[id]});
        }
    }

    size_t top_n = std::min(res.size(), MAX_RESULTS);

    std::partial_sort(res.begin(), res.begin() + top_n, res.end());

    if (res.size() > top_n) {
        res.resize(top_n);
    }
    return res;
}

int main() {
    int n;
    std::cin >> n >> std::ws;

    std::vector<std::string> documents;
    documents.reserve(n);
    for (int i = 0; i < n; ++i) {
        std::string line;
        std::getline(std::cin, line);
        documents.push_back(std::move(line));
    }

    const auto word_index = BuildWordIndex(documents);

    int m;
    std::cin >> m >> std::ws;

    for (int i = 0; i < m; ++i) {
        std::string request;
        std::getline(std::cin, request);

        const auto relevance = AccumulateRelevance(word_index, request);

        for (const auto& doc : SelectTop5Docs(relevance)) {
            std::cout << doc.doc_id << ' ';
        }
        std::cout << '\n';
    }
}
