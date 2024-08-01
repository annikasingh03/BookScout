//
// Created by Tatum Bowen on 7/31/24.
//

#ifndef LMP_ALGORITHM_H
#define LMP_ALGORITHM_H
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

// List of common words to exclude
const std::unordered_set<std::string> commonWords = {
        "the", "and", "a", "to", "of", "in", "that", "it", "is", "was",
        "he", "for", "on", "are", "as", "with", "his", "they", "i", "at",
        "be", "this", "have", "from", "or", "one", "had", "by", "word",
        "but", "not", "what", "all", "were", "we", "when", "your", "can",
        "said", "there", "use", "an", "each", "which", "she", "do", "how",
        "their", "if", "now", "own", "ever", "here", "very", "am", "our", "go",
        "im", "so", "us", "ma", "you", "id", "sh", "ut", "her", "me", "no",
        "em", "ill", "see", "any", "iv", "hers", "est", "other", "out", "like",
        "know", "though", "vi", "get", "could", "should", "would", "about", "them",
        "again", "went", "ive", "ye", "some", "herself", "hes", "its", "off", "did",
        "then", "say", "who", "into", "way", "ten", "thing", "ear", "my", "too", "him",
        "irs", "much", "must", "began"


};

// Function to read a file and return its content as a string
std::string readFile(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        return std::string((std::istreambuf_iterator<char>(file)),
                           std::istreambuf_iterator<char>());
    } else {
        throw std::runtime_error("Unable to open file");
    }
}

// Function to compute the longest prefix suffix (LPS) array for KMP
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

// Function to perform KMP search and count occurrences of a pattern
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

// Function to preprocess and clean a word
std::string cleanWord(const std::string& word) {
    std::string cleanedWord;
    for (char ch : word) {
        if (std::isalpha(ch)) {
            cleanedWord += std::tolower(ch);
        }
    }
    return cleanedWord;
}

// Function to preprocess the text and remove common words and single-letter characters
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

// Function to generate a map of unique words from text
std::unordered_map<std::string, int> generateWordMap(const std::vector<std::string>& cleanedWords) {
    std::unordered_map<std::string, int> wordMap;
    for (const auto& word : cleanedWords) {
        wordMap[word] = 0;
    }
    return wordMap;
}

// Function to count occurrences of each word in the map using KMP and update the map
void countWordsInText(std::unordered_map<std::string, int>& wordMap, const std::string& txt) {
    for (auto& pair : wordMap) {
        int count = KMPSearch(pair.first, txt);
        pair.second = count;
    }
}

// Function to extract the top 30 most used words
std::vector<std::pair<std::string, int>> extractTopWords(const std::unordered_map<std::string, int>& wordMap, size_t topN = 30) {
    std::vector<std::pair<std::string, int>> wordList(wordMap.begin(), wordMap.end());
    std::partial_sort(wordList.begin(), wordList.begin() + std::min(topN, wordList.size()), wordList.end(),
                      [](const auto& a, const auto& b) {
                          return b.second < a.second; // Sort in descending order by count
                      });
    if (wordList.size() > topN) {
        wordList.resize(topN);
    }
    return wordList;
}

// Function to output the word counts
void printWordCounts(const std::unordered_map<std::string, int>& wordCount) {
    for (const auto &pair : wordCount) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
}

// Function to output the top words
void printTopWords(const std::vector<std::pair<std::string, int>>& topWords) {
    for (const auto &pair : topWords) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
}

#endif //LMP_ALGORITHM_H
