#include "LMP_Algorithm.h"
#include <iostream>
#include <chrono>
#include <fstream>

int main() {
    // start measuring time
    auto start = std::chrono::high_resolution_clock::now();

    try {
        // change filename for each novel
        std::string filename = "../Frankenstein.txt"; // Update with the correct path
        // read file
        std::string fileContent = readFile(filename);

        std::vector<std::string> cleanedWords = preprocessText(fileContent);

        // map of unique words
        std::unordered_map<std::string, int> wordMap = generateWordMap(cleanedWords);

        // count occurances of each word
        countWordsInText(wordMap, fileContent);

        // 30 most used words that are at least six characters
        std::vector<std::pair<std::string, int>> topWords = extractTopWords(wordMap);

        // comment out later
        printTopWords(topWords);

        // stop measuring time for the processing part
        auto endProcessing = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsedProcessing = endProcessing - start;
        std::cout << "Processing time: " << elapsedProcessing.count() << " seconds" << std::endl;

        // top words in a txt file for python file to read
        std::ofstream wordFile("top_words.txt");
        for (const auto& pair : topWords) {
            wordFile << pair.first << " " << pair.second << std::endl;
        }
        wordFile.close();

        // use python to run the word cloud
        system("python ../wordCloud.py top_words.txt");

    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsedTotal = end - start;
    std::cout << "Total execution time: " << elapsedTotal.count() << " seconds" << std::endl;

    return 0;
}
