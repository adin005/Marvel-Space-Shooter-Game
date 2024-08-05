#ifndef FIREPOWERUP_H
#define FIREPOWERUP_H

#include "PowerUp.h"
#include <SFML/System/Clock.hpp>

class FirePowerUp : public PowerUp {
public:
    FirePowerUp(const std::string& imagePath, float scaleX, float scaleY)
        : PowerUp(imagePath, scaleX, scaleY) {
        // Load the image and set the sprite
        if (!texture.loadFromFile(imagePath)) {
            // Handle error
        }
        sprite.setTexture(texture);
        sprite.setScale(scaleX, scaleY);
    }

    void collect(Player& player) override {
        player.setFireMode(true); // Enable fire mode
        player.fireModeClock.restart(); // Restart the fire mode timer
    }
};

#endif // FIREPOWERUP_H


