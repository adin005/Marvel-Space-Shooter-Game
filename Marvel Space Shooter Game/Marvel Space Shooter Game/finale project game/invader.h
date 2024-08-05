#ifndef INVADER_H
#define INVADER_H

#include "Enemy.h"
#include "Bomb.h"
#include <vector>

class Invader : public Enemy {
public:
    int attackPattern;
    float timeSinceLastShot = 0.0f; // Time since the last bomb was shot
    float shootingInterval = 2.0f; // Interval between shots

    Invader(const std::string& png_path, float scaleX = 1.0f, float scaleY = 1.0f, int pattern = 0)
        : Enemy(png_path, scaleX, scaleY), attackPattern(pattern) {}

    void move(Vector2f direction, float deltaTime) override {
        sprite.move(direction * speed * deltaTime);
    }

    void update(float deltaTime) override {
        timeSinceLastShot += deltaTime;
    }

    void shootBomb(std::vector<Bomb*>& bombs, float deltaTime) override {
        if (timeSinceLastShot >= shootingInterval) {
            // Shoot a bomb
            Vector2f bombVelocity(0, 300); // Bomb moves down with a velocity of 300
            Bomb* bomb = new Bomb("img/bomb.png", 50.0f, bombVelocity); // Replace with your bomb image path
            bomb->sprite.setPosition(sprite.getPosition().x + sprite.getGlobalBounds().width / 2 - bomb->sprite.getGlobalBounds().width / 2,
                sprite.getPosition().y + sprite.getGlobalBounds().height);
            bombs.push_back(bomb);
            timeSinceLastShot = 0.0f; // Reset the timer
        }
    }
};

#endif // INVADER_H



















