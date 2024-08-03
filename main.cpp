#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

using namespace sf;

int main() {
    RenderWindow window(sf::VideoMode(1000, 1000), "BookScout");

    // Load the font from the specified path
    Font font;
    if (!font.loadFromFile("../font.ttf")) {
        std::cerr << "Error: Could not load the font file." << std::endl;
        return -1; // Exit if the font cannot be loaded
    } else {
        std::cout << "font loaded" << std::endl;
    }

    // Create a text object
    Text text;
    text.setFont(font);
    text.setString("Welcome to BookScout. Click on any book!");
    text.setCharacterSize(25); 
    text.setFillColor(sf::Color::Black); 

    // Center text at the top of the window
    FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f,
                   textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f(1000 / 2.0f, textRect.height + 40)); // Offset by 30 pixels from the top

    // Load the images into textures
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
        cerr << "Error: Could not load an image file." << endl;
        return -1;
    }

    // Load sprites
    Sprite sprite(texture), frank(b1), gatsby(b2), treasure(b3), alice(b4), jane(b5), ob(open_book), knuth(km), boyer(bm);

    // Sprite pos
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
    // Boolean to track if book and button are clicked
    bool bookClicked = false;
    bool boyerClicked = false, knuthClicked = false;

    Text how;
    how.setFont(font);
    how.setString("How would you like your BookScout search to be organized?");
    how.setCharacterSize(30);
    how.setFillColor(Color::Black);

    // Center the new text
    FloatRect hTextRect = how.getLocalBounds();
    how.setOrigin(hTextRect.left + hTextRect.width / 2.0f,
                  hTextRect.top + hTextRect.height / 2.0f);
    how.setPosition(Vector2f(1000 / 2.0f, 1000 / 2.0f - 380));

    // Text for showing which button was clicked
    Text clickedText;
    clickedText.setFont(font);
    clickedText.setCharacterSize(25);
    clickedText.setFillColor(Color::Black);

    // Main loop that continues until the window is closed
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            // Close window on 'close' event or when the Escape key is pressed
            if (event.type == Event::Closed || 
                (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)) {
                window.close();
            }

            // Check for mouse click events
            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

                    // Check if the mouse clicked on any book
                    if (frank.getGlobalBounds().contains(mousePos) ||
                        gatsby.getGlobalBounds().contains(mousePos) ||
                        treasure.getGlobalBounds().contains(mousePos) ||
                        alice.getGlobalBounds().contains(mousePos) ||
                        jane.getGlobalBounds().contains(mousePos)) {
                        bookClicked = true;
                    }

                    // Check if the mouse clicked on Boyer-Moore or Knuth-Morris button
                    if (bookClicked) {
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

        // Clear the window with a white color
        window.clear(Color::White);

        // Draw the appropriate screen based on clicks
        if (bookClicked) {
            if (boyerClicked) {
                clickedText.setString("Boyer-Moore button clicked!");
                clickedText.setPosition(Vector2f(1000 / 2.0f - 190, 1000 / 2.0f - 320));
                window.draw(clickedText);
            } else if (knuthClicked) {
                clickedText.setString("Knuth-Morris button clicked!");
                clickedText.setPosition(Vector2f(1000 / 2.0f - 190 , 1000 / 2.0f - 320)); //subtract by more if you want to go up more
                window.draw(clickedText);
            } else {
                window.draw(how);
                window.draw(ob);
                window.draw(boyer);
                window.draw(knuth);
            }
        } else {
            // Draw the original screen with the books and text
            window.draw(sprite);
            window.draw(frank);
            window.draw(gatsby);
            window.draw(treasure);
            window.draw(alice);
            window.draw(jane);
            window.draw(text);
        }

        // Display the current contents of the window
        window.display();
    }

    return 0;
}
