#ifndef BETA_H
#define BETA_H

#include "Invader.h"
#include "BetaBomb.h"

class Beta : public Invader {
public:
    int specialAbility;

    Beta(const std::string& png_path, float scaleX = 1.0f, float scaleY = 1.0f, int pattern = 0, int ability = 0)
        : Invader(png_path, scaleX, scaleY, pattern), specialAbility(ability) {}

    void useSpecialAbility() {
        // Implement Beta-specific special ability logic
    }

    void shootBomb(std::vector<Bomb*>& bombs, float deltaTime) {
        timeSinceLastShot += deltaTime;
        if (timeSinceLastShot >= shootingInterval) {
            // Shoot a bomb
            sf::Vector2f bombVelocity(0, 500); // Adjust the speed as necessary
            BetaBomb* newBomb = new BetaBomb("img/laserRed12.png", 50.0f, bombVelocity);
            sf::Vector2f invaderCenter = sprite.getPosition() + sf::Vector2f(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
            newBomb->sprite.setPosition(invaderCenter.x - newBomb->sprite.getGlobalBounds().width / 2, invaderCenter.y);
            bombs.push_back(newBomb);
            timeSinceLastShot = 0.0f; // Reset the timer
        }
    }
};

#endif








