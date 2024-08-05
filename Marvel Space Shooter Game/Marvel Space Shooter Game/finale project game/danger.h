#ifndef DANGER_H
#define DANGER_H

#include <SFML/Graphics.hpp>
#include "Enemy.h"

class Danger : public Enemy {
public:
    Danger(const std::string& texturePath, float scaleX = 1.0f, float scaleY = 1.0f)
        : Enemy(texturePath, scaleX, scaleY) {
        // Initialize the danger sign's properties
        speed = 50.0f;
    }

    void update(float deltaTime) override {
        // Update the danger sign's position
        sprite.move(0, speed * deltaTime);

        // Check if the danger sign is off-screen and remove it if necessary
        if (sprite.getPosition().y > 1200) {
            delete this;
        }
    }
};

#endif // DANGER_H


