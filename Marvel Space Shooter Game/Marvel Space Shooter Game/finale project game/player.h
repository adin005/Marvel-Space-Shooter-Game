#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <string>
#include <cmath>
#include "Bullet.h"
#include "FireBullet.h"

using namespace sf;

const float INVINCIBILITY_DURATION = 10.0f; // Define the duration of invincibility
const float FIRE_MODE_DURATION = 5.0f;
const float SHOOTING_POWERUP_DURATION = 10.0f; // Duration of fire mode

class Player {
public:
    Texture tex;
    Sprite sprite;
    float speed = 1000.0f;  // Speed in pixels per second
    Vector2f velocity;
    int lives = 3;  // Number of lives
    float fireDelay = 0.15f; // Fire delay for bullets

    bool fireMode = false;   // Flag to check if fire mode is active
    Clock fireModeClock;     // Clock to keep track of fire mode duration

    bool shootingPowerUp = false; // Flag to check if shooting power-up is active
    Clock shootingPowerUpClock;   // Clock to keep track of shooting power-up duration

    bool invincible = false;  // Flag to check if player is invincible

    Player(const std::string& png_path, float scaleX = 1.0f, float scaleY = 1.0f) {
        tex.loadFromFile(png_path);
        sprite.setTexture(tex);
        sprite.setPosition(340, 700);
        sprite.setScale(scaleX, scaleY);
        velocity = Vector2f(0, 0);
        lives = 3;  // Initialize the player with 3 lives
    }

    void firefire(std::vector<Bullet*>& bullets, std::vector<FireBullet*>& fireBullets) {
        if (fireMode) {
            FireBullet* fireBullet = new FireBullet("img/missi.png");
            fireBullet->fire(sprite.getPosition().x, sprite.getPosition().y);
            fireBullet->direction = Vector2f(0, -1);
            fireBullets.push_back(fireBullet);
        }
        else if (shootingPowerUp) {
            // Fire bullets in seven directions
            std::vector<Vector2f> directions = {
                {0, -1}, {0.7, -0.7}, {1, 0}, {0.7, 0.7},
                {0, 1}, {-0.7, 0.7}, {-1, 0}, {-0.7, -0.7}
            };
            for (const auto& dir : directions) {
                Bullet* bullet = new Bullet("img/missi.png");
                bullet->fire(sprite.getPosition().x, sprite.getPosition().y);
                bullet->direction = dir;
                bullets.push_back(bullet);
            }
        }
        else {
            Bullet* bullet = new Bullet("img/missi.png");
            bullet->fire(sprite.getPosition().x, sprite.getPosition().y);
            bullet->direction = Vector2f(0, -1);
            bullets.push_back(bullet);
        }
    }

    void move(Vector2f direction, float deltaTime) {
        velocity = direction * speed * deltaTime;
        // Wrap around the screen edges
        if (sprite.getPosition().x < 0) {
            sprite.setPosition(1300, sprite.getPosition().y);
        }
        else if (sprite.getPosition().x > 1300) {
            sprite.setPosition(0, sprite.getPosition().y);
        }

        if (sprite.getPosition().y < 0) {
            sprite.setPosition(sprite.getPosition().x, 400);
        }
        else if (sprite.getPosition().y > 600) {
            sprite.setPosition(sprite.getPosition().x, 0);
        }
    }

    void update(float deltaTime) {
        sprite.move(velocity);
        velocity *= 0.95f;  // Apply some damping to stop movement over time

        // Check if fire mode duration is over
        if (fireMode && fireModeClock.getElapsedTime().asSeconds() > FIRE_MODE_DURATION) {
            fireMode = false;
        }

        // Check if shooting power-up duration is over
        if (shootingPowerUp && shootingPowerUpClock.getElapsedTime().asSeconds() > SHOOTING_POWERUP_DURATION) {
            shootingPowerUp = false;
            invincible = false;
        }
    }

    // Increment the player's lives by one
    void addLife() {
        lives++;
    }

    void decrementLives() {
        if (!invincible) {
            lives--;
        }
    }

    void setFireMode(bool mode) {
        fireMode = mode;
    }

    void setShootingPowerUp(bool mode) {
        shootingPowerUp = mode;
        if (mode) {
            invincible = true;
            shootingPowerUpClock.restart();  // Ensure the power-up timer is restarted
        }
        else {
            invincible = false;
        }
    }
};



#endif // PLAYER_H
