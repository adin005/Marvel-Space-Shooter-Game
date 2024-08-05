#ifndef POWERUP_H
#define POWERUP_H

#include <SFML/Graphics.hpp>
#include "Player.h"

class PowerUp {
public:
    PowerUp(const std::string& imagePath, float scaleX, float scaleY) {
        if (!texture.loadFromFile(imagePath)) {
            // Handle error
        }
        sprite.setTexture(texture);
        sprite.setScale(scaleX, scaleY);
    }

    virtual void collect(Player& player) = 0; // Pure virtual function to be implemented by derived classes

    // Method to set the position of the power-up
    void setPosition(float x, float y) {
        sprite.setPosition(x, y);
    }

    // Method to get the position of the power-up
    sf::Vector2f getPosition() const {
        return sprite.getPosition();
    }

    // Method to get the sprite of the power-up
    const sf::Sprite& getSprite() const {
        return sprite;
    }

    // Method to draw the power-up
    void draw(sf::RenderWindow& window) const {
        window.draw(sprite);
    }

protected:
    sf::Texture texture;
    sf::Sprite sprite;
};

#endif // POWERUP_H
