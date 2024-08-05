#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>
using namespace sf;

class Bullet {
public:
    Texture tex;
    Sprite sprite;
    float speed = 3000.0f;  // Increased speed in pixels per second
    float timeSinceLastShot = 0.0f; // Time since the last bullet was fired
    float fireDelay = 0.15f; // Delay between each bullet in seconds
    float distance = 50.0f; // Vertical distance between each bullet

    Vector2f direction; // Direction of the bullet's movement

    Bullet(const std::string& texturePath) {
        // Load bullet texture
        if (!tex.loadFromFile(texturePath)) {
            // Handle error
        }
        sprite.setTexture(tex);
        sprite.setScale(0.5f, 0.5f); // Adjust the scale if necessary
    }

    // Destructor
    ~Bullet() {
        // Clean up resources if needed
    }

    // Update function
    void update(float deltaTime) {
        // Move the bullet
        sprite.move(direction * speed * deltaTime);
    }

    // Fire function
    void fire(float x, float y) {
        // Set bullet position
        sprite.setPosition(x, y);
    }
};

#endif // BULLET_H


