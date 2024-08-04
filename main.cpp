#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
#include "bm.h"
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include<map>
#include <algorithm>
#include <cctype>
#include <unordered_set>
using namespace sf;
#include <chrono>
#include "LMP_Algorithm.h"
#define NO_OF_CHARS 256


void wordCloud(const std::string& filename);

void wordCloud(const std::string& filename) {
    // start measuring time
    auto start = std::chrono::high_resolution_clock::now();

    try {
        // read file
        std::string fileContent = readFile(filename);

        std::vector<std::string> cleanedWords = preprocessText(fileContent);

        // map of unique words
        std::unordered_map<std::string, int> wordMap = generateWordMap(cleanedWords);

        // count occurrences of each word
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
        if (!wordFile) {
            throw std::runtime_error("Failed to open top_words.txt for writing.");
        }
        for (const auto& pair : topWords) {
            wordFile << pair.first << " " << pair.second << std::endl;
        }
        wordFile.close();

        // use python to run the word cloud
        int ret = std::system("python wordCloud.py top_words.txt");
        if (ret != 0) {
            throw std::runtime_error("Python script failed with error code " + std::to_string(ret));
        }

    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        throw;  // Re-throw exception to be caught in main()
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsedTotal = end - start;
    std::cout << "Total execution time: " << elapsedTotal.count() << " seconds" << std::endl;
}

void wordCloudBM( const string& filename){

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Failed to open the file: " << filename << endl;
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
    vector<pair<string, int>> Tops;

    int topNums = 30;
    int count = 0;
    cout << "Top " << topNums << " popular words:" << endl;
    for (auto &word : sortedWords) {
            cout << word.first << ": " << word.second << endl;
            count++;
            Tops.push_back({word.first, word.second});
            if(count == topNums){
                break;
            }
    }
//    cout << sortedWords[i].first << ": " << sortedWords[i].second << endl;

    cout << "Time taken: " << duration.count() << " seconds" << endl;

    std::ofstream wordFile("top_words.txt");
        if (!wordFile) {
            throw std::runtime_error("Failed to open top_words.txt for writing.");
        }
        for (const auto& pair : Tops) {
            wordFile << pair.first << " " << pair.second << std::endl;
        }
        wordFile.close();

        // use python to run the word cloud
        int ret = std::system("python wordCloud.py top_words.txt");
        if (ret != 0) {
            throw std::runtime_error("Python script failed with error code " + std::to_string(ret));
        }
}


int main() {
    RenderWindow window(sf::VideoMode(1000, 1000), "BookScout");

    // loading font
    Font font;
    if (!font.loadFromFile("font.ttf")) {
        std::cerr << "Error: Could not load the font file." << std::endl;
        return -1; // Exit if the font cannot be loaded
    } else {
        std::cout << "font loaded" << std::endl;
    }

   
    Text text;
    text.setFont(font);
    text.setString("Welcome to BookScout. Click on any book!");
    text.setCharacterSize(25); 
    text.setFillColor(sf::Color::Black); 

 
    FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f,
                   textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f(1000 / 2.0f, textRect.height + 40)); //40 pixels from the top

    //  into textures
    Texture texture, b1, b2, b3, b4, b5, open_book, km, bm;
    if (!texture.loadFromFile("images\\tiny_lib.png") ||
        !b1.loadFromFile("images\\frank.png") ||
        !b2.loadFromFile("images\\gatsby.png") ||
        !b3.loadFromFile("images\\treasure.png") ||
        !b4.loadFromFile("images\\alice.png") ||
        !b5.loadFromFile("images\\jane.png") ||
        !open_book.loadFromFile("images\\open_book.png") ||
        !km.loadFromFile("images\\knuth.png") ||
        !bm.loadFromFile("images\\boyer.png")) {
        cerr << "Cant load image." << endl;
        return -1;
    }

    // Load sprites
    Sprite sprite(texture), frank(b1), gatsby(b2), treasure(b3), alice(b4), jane(b5), ob(open_book), knuth(km), boyer(bm);

    //  pos of sprite
    FloatRect spriteRect = sprite.getLocalBounds();
    sprite.setOrigin(spriteRect.left + spriteRect.width / 2.0f,
                     spriteRect.top + spriteRect.height / 2.0f);
    sprite.setPosition(Vector2f(1000 / 2.0f, 1000 / 2.0f)); // center in the window

    // frankenstein location
    FloatRect frankRect = frank.getLocalBounds();
    frank.setOrigin(frankRect.left + frankRect.width / 2.0f,
                    frankRect.top + frankRect.height / 2.0f);
    frank.setPosition(Vector2f(1000 / 2.0f - 68, 1000 / 2.0f - 58)); //x axis, y  //subtraction goes left addition goes right

    // gatsby location
    FloatRect gatsbyRect = gatsby.getLocalBounds();
    gatsby.setOrigin(gatsbyRect.left + gatsbyRect.width / 2.0f,
                     frankRect.top + gatsbyRect.height / 2.0f);
    gatsby.setPosition(Vector2f(1000 / 2.0f - 43, 1000 / 2.0f - 63)); //x axis, y  //subtraction by less goes left addition goes right

    // treasure location
    FloatRect treasureRect = treasure.getLocalBounds();
    treasure.setOrigin(treasureRect.left + treasureRect.width / 2.0f,
                       treasureRect.top + treasureRect.height / 2.0f);
    treasure.setPosition(Vector2f(1000 / 2.0f - 17, 1000 / 2.0f - 58)); 

    // alice location
    FloatRect aRect = alice.getLocalBounds();
    alice.setOrigin(aRect.left + aRect.width / 2.0f,
                    aRect.top + aRect.height / 2.0f);
    alice.setPosition(Vector2f(1000 / 2.0f + 9, 1000 / 2.0f - 53)); 

    // jane location
    FloatRect jRect = jane.getLocalBounds();
    jane.setOrigin(jRect.left + jRect.width / 2.0f,
                   jRect.top + jRect.height / 2.0f);
    jane.setPosition(Vector2f(1000 / 2.0f + 74, 1000 / 2.0f - 63)); 

    // open book location
    FloatRect oRect = ob.getLocalBounds();
    ob.setOrigin(oRect.left + oRect.width / 2.0f,
                 oRect.top + oRect.height / 2.0f);
    ob.setPosition(Vector2f(1000 / 2.0f, 1000 / 2.0f - 63)); 

    // knuth button location
    FloatRect kmRect = knuth.getLocalBounds();
    knuth.setOrigin(kmRect.left + kmRect.width / 2.0f,
                    oRect.top + oRect.height / 2.0f);
    knuth.setPosition(Vector2f(1000 / 2.0f + 240, 1000 / 2.0f + 350)); 

    // boyer button location
    FloatRect bmRect = boyer.getLocalBounds();
    boyer.setOrigin(bmRect.left + oRect.width / 2.0f,
                    oRect.top + oRect.height / 2.0f);
    boyer.setPosition(Vector2f(1000 / 2.0f - 200, 1000 / 2.0f + 350)); 
    // flags to track if book and button are clicked
    bool b1Clicked = false, b2Clicked = false, b3Clicked = false, b4Clicked = false, b5Clicked = false;
    bool book_chosen = false;
    bool boyerClicked = false, knuthClicked = false;
    bool wordCloudGenerated = false;

    Text how;
    how.setFont(font);
    how.setString("How would you like your BookScout search to be organized?");
    how.setCharacterSize(23);
    how.setFillColor(Color::Black);

    // center the new text
    FloatRect hTextRect = how.getLocalBounds();
    how.setOrigin(hTextRect.left + hTextRect.width / 2.0f,
                  hTextRect.top + hTextRect.height / 2.0f);
    how.setPosition(Vector2f(1000 / 2.0f, 1000 / 2.0f - 380));

    
    Text clickedText;
    clickedText.setFont(font);
    clickedText.setCharacterSize(25);
    clickedText.setFillColor(Color::Black);


    string title;
    
    
    
    //window loop
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            // exit window
            if (event.type == Event::Closed || 
                (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)) {
                window.close();
            }

            // mouse click events
            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

                
                    if ( frank.getGlobalBounds().contains(mousePos) ){
                        b1Clicked = true, book_chosen = true, title = "Frankenstein.txt"; 
                        wordCloudGenerated = false;  
                    }
                    else if( gatsby.getGlobalBounds().contains(mousePos) ){
                        b2Clicked = true, book_chosen = true, title = "GreatGatsby.txt"; 
                        wordCloudGenerated = false;  
                    }
                    else if( treasure.getGlobalBounds().contains(mousePos) ){
                        b3Clicked = true, book_chosen = true, title = "TreasureIsland.txt"; 
                        wordCloudGenerated = false;  
                    }
                    else if( alice.getGlobalBounds().contains(mousePos) ){
                        b4Clicked = true, book_chosen = true, title = "AliceInWonderland.txt"; 
                        wordCloudGenerated = false;  
                    }
                    else if( jane.getGlobalBounds().contains(mousePos) ){
                        b5Clicked = true, book_chosen = true, title = "JaneEyre.txt"; 
                        wordCloudGenerated = false;  
                    }

                    // check if bm or km was clicked 
                    if (book_chosen) {
                        if (boyer.getGlobalBounds().contains(mousePos)) {
                            boyerClicked = true;
                            knuthClicked = false;
                        } else if (knuth.getGlobalBounds().contains(mousePos)) {
                            knuthClicked = true;
                            boyerClicked = false;
                        }
                    }
                }
            }
        }

        //white
        window.clear(Color::White);

        // Draw the appropriate screen based on clicks./ma
        if (book_chosen) {
            if (boyerClicked && !wordCloudGenerated) {  
                clickedText.setString("Boyer-Moore button clicked!");
                clickedText.setPosition(Vector2f(1000 / 2.0f - 190, 1000 / 2.0f - 320));
                wordCloudBM(title);
                wordCloudGenerated = true;
                window.draw(clickedText);

            } else if (knuthClicked && !wordCloudGenerated) { 
                clickedText.setString("Knuth-Morris button clicked!");
                clickedText.setPosition(Vector2f(1000 / 2.0f - 190 , 1000 / 2.0f - 320)); //subtract by more if you want to go up more
                wordCloud(title);
                wordCloudGenerated = true;  // Set the flag to true
                window.draw(clickedText);
            } else {
                window.draw(how);
                window.draw(ob);
                window.draw(boyer);
                window.draw(knuth);
            }
        } else {
            window.draw(sprite);
            window.draw(frank);
            window.draw(gatsby);
            window.draw(treasure);
            window.draw(alice);
            window.draw(jane);
            window.draw(text);
        }

        window.display();
    }

    return 0;
}
