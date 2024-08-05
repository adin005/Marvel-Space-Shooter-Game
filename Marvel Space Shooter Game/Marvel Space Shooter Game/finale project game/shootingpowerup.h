#ifndef SHOOTINGPOWERUP_H
#define SHOOTINGPOWERUP_H

#include "PowerUp.h"
#include <SFML/System/Clock.hpp>

class ShootingPowerUp : public PowerUp {
public:
    ShootingPowerUp(const std::string& imagePath, float scaleX, float scaleY)
        : PowerUp(imagePath, scaleX, scaleY) {
        // Load the image and set the sprite
        if (!texture.loadFromFile(imagePath)) {
            // Handle error
        }
        sprite.setTexture(texture);
        sprite.setScale(scaleX, scaleY);
    }

    void collect(Player& player) {
        std::cout << "Shooting power-up collected!\n";
        player.setShootingPowerUp(true); // Enable shooting power-up mode
        player.shootingPowerUpClock.restart(); // Restart the shooting power-up timer
    }

    void setShootingPowerUp(bool enabled) {
        shootingPowerUp = enabled;
    }
    static constexpr float SHOOTING_POWERUP_DURATION = 10.0f; // Duration of the shooting power-up effect
private:
    // ...

    bool shootingPowerUp = false; // Flag to indicate if shooting power-up is enabled
    sf::Clock shootingPowerUpClock; // Timer to keep track of shooting power-up duration

};


#endif // SHOOTINGPOWERUP_H
