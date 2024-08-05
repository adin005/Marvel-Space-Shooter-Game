#ifndef MONSTER_H
#define MONSTER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Enemy.h"
#include "Bomb.h" // Include the Bomb class for shooting laser beam

class Monster : public Enemy {
public:
    Monster(const std::string& png_path, float scaleX = 0.5f, float scaleY = 0.5f)
        : Enemy(png_path, scaleX, scaleY), moveRight(true), shootTimer(0.0f), shootInterval(5.0f), beamActive(false) {
        if (!texture.loadFromFile(png_path)) {
            std::cerr << "Failed to load monster image: " << png_path << std::endl;
        }
        sprite.setTexture(texture);
        sprite.setScale(scaleX, scaleY);
        sprite.setPosition(600, 200);
        speed = 200.0f;
    }

    void move(Vector2f direction, float deltaTime) override {
        if (moveRight) {
            sprite.move(speed * deltaTime, 0.0f);
        }
        else {
            sprite.move(-speed * deltaTime, 0.0f);
        }

        if (sprite.getPosition().x >= 1600 - sprite.getGlobalBounds().width) {
            moveRight = false;
        }
        else if (sprite.getPosition().x <= 0) {
            moveRight = true;
        }

        // Update the beam's position to follow the monster
        if (beamActive) {
            float monsterCenterX = sprite.getPosition().x + sprite.getGlobalBounds().width / 2;
            float monsterCenterY = sprite.getPosition().y + sprite.getGlobalBounds().height;
            beam->sprite.setPosition(monsterCenterX - beam->sprite.getGlobalBounds().width / 2, monsterCenterY);
        }
    }

    void shootBeam(std::vector<Bomb*>& bombs, float deltaTime) {
        shootTimer += deltaTime;

        if (shootTimer >= shootInterval) {
            if (!beamActive) {
                // Create a new beam bomb if it's not already active
                beam = new Bomb("img/missi.png", 50.0f, Vector2f(0.0f, 0.0f));

                // Position the beam to appear from the middle of the monster
                float monsterCenterX = sprite.getPosition().x + sprite.getGlobalBounds().width / 2;
                float monsterCenterY = sprite.getPosition().y + sprite.getGlobalBounds().height;
                beam->sprite.setPosition(monsterCenterX - beam->sprite.getGlobalBounds().width / 2, monsterCenterY);

                bombs.push_back(beam);
                beamActive = true;
            }
            shootTimer = 0.0f;
        }

        // Check if the beam should disappear after the interval
        if (beamActive && shootTimer >= shootInterval / 2) {
            beam->isActive = false;
            beamActive = false;
        }
    }

private:
    sf::Texture texture;
    bool moveRight;
    float shootTimer;
    float shootInterval;
    bool beamActive;
    Bomb* beam; // Pointer to hold the active beam
};

#endif // MONSTER_H




