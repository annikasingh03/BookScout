//
// Created by Tatum Bowen on 7/31/24.
//

#ifndef KMP_ALGORITHM_H
#define KMP_ALGORITHM_H
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <algorithm>
#include <cctype>
#include <unordered_set>

// common words (excluding these)
const std::unordered_set<std::string> commonWords = {
        "copyright", "anything", "getting", "rather", "electronic", "before", "replied",
        "remark", "though", "should", "minute", "through", "little", "things", "nothing",
        "thought", "because"
};

// read the novel txt file and return as a string
std::string readFile(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        return std::string((std::istreambuf_iterator<char>(file)),
                           std::istreambuf_iterator<char>());
    } else {
        throw std::runtime_error("Unable to open file");
    }
}

// compute the LPS for the KMP algorithm
void computeLPSArray(const std::string &pat, std::vector<int> &lps) {
    int M = pat.size();
    lps[0] = 0;
    int len = 0;
    int i = 1;
    while (i < M) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// KMP algorithm to go through each word in the map and count occurances
int KMPSearch(const std::string &pat, const std::string &txt) {
    int M = pat.size();
    int N = txt.size();
    std::vector<int> lps(M);
    computeLPSArray(pat, lps);

    int i = 0;
    int j = 0;
    int count = 0;
    while (i < N) {
        if (pat[j] == txt[i]) {
            j++;
            i++;
        }

        if (j == M) {
            count++;
            j = lps[j - 1];
        } else if (i < N && pat[j] != txt[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
    return count;
}

// cleans the words (get rid of punctuation, only alpha characters)
std::string cleanWord(const std::string& word) {
    std::string cleanedWord;
    for (char ch : word) {
        if (std::isalpha(ch)) {
            cleanedWord += std::tolower(ch);
        }
    }
    return cleanedWord;
}

// removes the common words and single letters from the total list
std::vector<std::string> preprocessText(const std::string& txt) {
    std::istringstream stream(txt);
    std::string word;
    std::vector<std::string> cleanedWords;

    while (stream >> word) {
        std::string cleanedWord = cleanWord(word);
        if (cleanedWord.size() > 1 && commonWords.find(cleanedWord) == commonWords.end()) {
            cleanedWords.push_back(cleanedWord);
        }
    }

    return cleanedWords;
}

// map of every unique word
std::unordered_map<std::string, int> generateWordMap(const std::vector<std::string>& cleanedWords) {
    std::unordered_map<std::string, int> wordMap;
    for (const auto& word : cleanedWords) {
        wordMap[word] = 0;
    }
    return wordMap;
}

// uses the KMP algorithm to count each word in the map
void countWordsInText(std::unordered_map<std::string, int>& wordMap, const std::string& txt) {
    for (auto& pair : wordMap) {
        int count = KMPSearch(pair.first, txt);
        pair.second = count;
    }
}

// for the word cloud: extracts top 30 words that are six characters or more
std::vector<std::pair<std::string, int>> extractTopWords(const std::unordered_map<std::string, int>& wordMap, size_t topN = 30) {
    std::vector<std::pair<std::string, int>> wordList;

    for (const auto& pair : wordMap) {
        if (pair.first.size() >= 6) {
            wordList.push_back(pair);
        }
    }

    std::partial_sort(wordList.begin(), wordList.begin() + std::min(topN, wordList.size()), wordList.end(),
                      [](const auto& a, const auto& b) {
                          return b.second < a.second; // Sort in descending order by count
                      });
    if (wordList.size() > topN) {
        wordList.resize(topN);
    }
    return wordList;
}

// prints the total map of unique words and occurences
void printWordCounts(const std::unordered_map<std::string, int>& wordCount) {
    for (const auto &pair : wordCount) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
}

// just prints the top 30 words
void printTopWords(const std::vector<std::pair<std::string, int>>& topWords) {
    for (const auto &pair : topWords) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
}

#endif //KMP_ALGORITHM_H
