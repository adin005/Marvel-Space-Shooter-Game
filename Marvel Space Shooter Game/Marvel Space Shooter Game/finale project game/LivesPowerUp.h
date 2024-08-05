#ifndef LIVESPOWERUP_H
#define LIVESPOWERUP_H

#include "PowerUp.h"
#include "Player.h"

class LivesPowerUp : public PowerUp {
public:
    LivesPowerUp(const std::string& imagePath, float scaleX, float scaleY);
    void collect(Player& player) override;

    sf::Sprite sprite; // Declare sprite member

private:
    // You can add any additional members or functions as needed
};

LivesPowerUp::LivesPowerUp(const std::string& imagePath, float scaleX, float scaleY)
    : PowerUp(imagePath, scaleX, scaleY) {
    // Load the image and set the sprite
    if (!texture.loadFromFile(imagePath)) {
        // Handle error
    }
    sprite.setTexture(texture);
    sprite.setScale(scaleX, scaleY);
}

void LivesPowerUp::collect(Player& player) {
    player.addLife();
}

#endif // LIVESPOWERUP_H