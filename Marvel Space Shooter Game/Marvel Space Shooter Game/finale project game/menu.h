#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "game.h"
#include <iostream>

class Menu {
public:
    Menu() {
        // Load font
        if (!font.loadFromFile("fonts/tech.ttf")) {
            std::cerr << "Error loading font\n";
        }

        // Load background texture
        if (!backgroundTexture.loadFromFile("img/1268307.png")) {
            std::cerr << "Error loading background image\n";
        }

        backgroundSprite.setTexture(backgroundTexture);
        backgroundSprite.setScale(1.0f, 0.5f); // Adjust to fit the window

        // Load menu music
        if (!menuMusic.openFromFile("sound/theme.ogg")) {
            std::cerr << "Error loading menu music\n";
        }
        menuMusic.setLoop(true);
        menuMusic.play();

        // Set up menu items
        setupMenuItems();
    }

    void display_menu() {
        sf::RenderWindow window(sf::VideoMode(1300, 600), "OOP-Project Menu");

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }

                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Up) {
                        moveUp();
                    }
                    else if (event.key.code == sf::Keyboard::Down) {
                        moveDown();
                    }
                    else if (event.key.code == sf::Keyboard::Enter) {
                        selectOption(window);
                    }
                }
            }

            window.clear();
            window.draw(backgroundSprite);
            for (const auto& text : menuItems) {
                window.draw(text);
            }
            window.display();
        }
    }

private:
    sf::Font font;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    std::vector<sf::Text> menuItems;
    int selectedItemIndex = 0;
    sf::Music menuMusic;

    void setupMenuItems() {
        std::vector<std::string> menuTexts = {
            "Start Level 1 (Alpha Invaders)",
            "Start Level 2 (Alpha and Beta Invaders)",
            "Start Level 3 (Alpha, Beta, and Gamma Invaders)",
            "Start Level 4 (Monster and Beta Invaders)",
            "Start Level 5 (Dragon and Gamma Invaders)",
            "Exit"
        };

        for (int i = 0; i < menuTexts.size(); ++i) {
            sf::Text text;
            text.setFont(font);
            text.setString(menuTexts[i]);
            text.setCharacterSize(30);
            text.setFillColor(i == selectedItemIndex ? sf::Color::Red : sf::Color::White);
            text.setPosition(100.0f, 150.0f + i * 60.0f);
            menuItems.push_back(text);
        }
    }

    void moveUp() {
        if (selectedItemIndex > 0) {
            menuItems[selectedItemIndex].setFillColor(sf::Color::White);
            selectedItemIndex--;
            menuItems[selectedItemIndex].setFillColor(sf::Color::Red);
        }
    }

    void moveDown() {
        if (selectedItemIndex < menuItems.size() - 1) {
            menuItems[selectedItemIndex].setFillColor(sf::Color::White);
            selectedItemIndex++;
            menuItems[selectedItemIndex].setFillColor(sf::Color::Red);
        }
    }

    

       /**/ void selectOption(sf::RenderWindow& window) {
            Game g;
            // Stop the menu music before starting the level
            menuMusic.stop();

            switch (selectedItemIndex) {
            case 0:
                g.playLevelMusic("sound/tultron.ogg");
                g.start_level_1();
                break;
            case 1:
                g.playLevelMusic("sound/endgame.ogg");
                g.start_level_2();
                break;
            case 2:
                g.playLevelMusic("sound/theme.ogg");
                g.start_level_3();
                break;
            case 3:
                g.playLevelMusic("sound/metal.ogg");
                g.start_level_4();
                break;
            case 4:
                g.playLevelMusic("sound/bad infinity.ogg");
                g.start_level_5();
                break;
            case 5:
                window.close();
                break;
            default:
                break;
            }
        }

};

#endif // MENU_H

