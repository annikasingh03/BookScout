#include "WordCloud.h"
#include "LMP_Algorithm.h"
#include <iostream>

int main() {
        try {
            // Specify the filename
            std::string filename = "/Users/tatumbowen/Desktop/AliceInWonderland.txt"; // Update with the correct path

            // Read the file content
            std::string fileContent = readFile(filename);

            // Preprocess the text and get cleaned words
            std::vector<std::string> cleanedWords = preprocessText(fileContent);

            // Generate a map of unique words with initial value of zero
            std::unordered_map<std::string, int> wordMap = generateWordMap(cleanedWords);

            // Count occurrences of each word and update the map
            countWordsInText(wordMap, fileContent);

            // Extract the top 30 most used words
            std::vector<std::pair<std::string, int>> topWords = extractTopWords(wordMap);

            // Print the top words
            printTopWords(topWords);
        } catch (const std::exception &e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return 1;
        }

    return 0;
}
