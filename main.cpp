#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <chrono>
using namespace std;
#define NO_OF_CHARS 256


void badCharHeuristic(string str, int size, int badchar[NO_OF_CHARS]) {
    for (int i = 0; i < NO_OF_CHARS; i++)
        badchar[i] = -1;

    for (int i = 0; i < size; i++)
        badchar[(int)str[i]] = i;
}

int search(string txt, string pat) {
    int m = pat.size();
    int n = txt.size();
    int badchar[NO_OF_CHARS];
    badCharHeuristic(pat, m, badchar);

    int count = 0;
    int s = 0;
    while (s <= (n - m)) {
        int j = m - 1;

        while (j >= 0 && pat[j] == txt[s + j])
            j--;

        if (j < 0) {
            if ((s == 0 || !isalpha(txt[s - 1])) && (s + m == n || !isalpha(txt[s + m]))) {
                count++;
            }
            s += (s + m < n) ? m - badchar[txt[s + m]] : 1;
        } else {
            s += max(1, j - badchar[txt[s + j]]);
        }
    }
    return count;
}

string onlyText(const string &text) {
    string result;
    for (char c : text) {
        if (isalpha(c)) {
            result += tolower(c);
//       }
        } else if(isspace(c)){
            result += ' ';
            }


    }
    return result;
}

vector<string> convertToWords(const string &text) {
    vector<string> words;
    istringstream stream(text);
    string word;
    while (stream >> word) {
        words.push_back(word);
    }
    return words;
}

map<string, int> countNumWord(const string &text, const vector<string> &words) {
    map<string, int> wordCount;
    for (const string &word : words) {
        //change here for different word size count!!
        if (word.size() > 6) {
            wordCount[word] = search(text, word);
        }
    }
    return wordCount;
}
bool sortPairs(const pair<string, int> &a, const pair<string, int> &b) {
    if (a.second > b.second) {
        return true;
    } else {
        return false;
    }
}

int main() {

    string filePath = "C:/Users/maldo/CLionProjects/Project3/Alice.txt";

    ifstream file(filePath);
    if (!file.is_open()) {
        cout << "Failed to open the file: " << filePath << endl;
        return 1;
    }

    stringstream buffer;
    buffer << file.rdbuf();
    string text = buffer.str();
    file.close();

    string onlyText1 = onlyText(text);

    vector<string> words = convertToWords(onlyText1);

    auto start = chrono::high_resolution_clock::now();

    map<string, int> numOfWords = countNumWord(onlyText1, words);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;

    // Sort
    vector<pair<string, int>> sortedWords(numOfWords.begin(), numOfWords.end());
    sort(sortedWords.begin(), sortedWords.end(), sortPairs);

    set<string> commonWords = {"the", "and", "to", "of", "it", "she", "said", "you", "in", "was", "that", "as", "her", "with", "at", "on", "all", "for"};

    int topNums = 100;
    int count = 0;
    cout << "Top " << topNums << " popular words:" << endl;
    for (auto &word : sortedWords) {
        if(commonWords.find(word.first) == commonWords.end()) {
            cout << word.first << ": " << word.second << endl;
            count++;
            if(count == topNums){
                break;
            }
        }
    }
//    cout << sortedWords[i].first << ": " << sortedWords[i].second << endl;

    cout << "Time taken: " << duration.count() << " seconds" << endl;

    return 0;
}

//30