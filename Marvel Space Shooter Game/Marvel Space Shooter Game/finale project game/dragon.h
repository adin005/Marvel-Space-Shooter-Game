#ifndef DRAGON_H
#define DRAGON_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Enemy.h"
#include "Bomb.h"
#include "Player.h"

class Dragon : public Enemy {
public:
    Dragon(const std::string& png_path, float scaleX = 0.5f, float scaleY = 0.5f)
        : Enemy(png_path, scaleX, scaleY), shootTimer(0.0f), shootInterval(static_cast<float>(rand() % 5 + 1)) {
        if (!texture.loadFromFile(png_path)) {
            std::cerr << "Failed to load dragon image: " << png_path << std::endl;
        }
        sprite.setTexture(texture);
        sprite.setScale(scaleX, scaleY);
        sprite.setPosition(600, 200);
        speed = 0.0f;
    }

    void shootBomb(std::vector<Bomb*>& bombs, float deltaTime, const Player& player) {
        shootTimer += deltaTime;

        if (shootTimer >= shootInterval) {
            // Calculate direction vector from dragon to player
            sf::Vector2f dragonCenter = sprite.getPosition() + sf::Vector2f(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
            sf::Vector2f playerCenter = player.sprite.getPosition() + sf::Vector2f(player.sprite.getGlobalBounds().width / 2, player.sprite.getGlobalBounds().height / 2);
            sf::Vector2f direction = playerCenter - dragonCenter;
            float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
            sf::Vector2f normalizedDirection = direction / length;

            // Adjust the bomb velocity based on direction
            sf::Vector2f bombVelocity = normalizedDirection * 500.0f; // Adjust the speed as necessary
            Bomb* newBomb = new Bomb("img/l4.png", 50.0f, bombVelocity);
            newBomb->sprite.setPosition(dragonCenter.x - newBomb->sprite.getGlobalBounds().width / 2, dragonCenter.y);
            bombs.push_back(newBomb);

            shootTimer = 0.0f; // Reset the timer
            shootInterval = static_cast<float>(rand() % 5 + 1); // Randomize the shoot interval again
        }
    }

private:
    sf::Texture texture;
    float shootTimer;
    float shootInterval;
};

#endif










