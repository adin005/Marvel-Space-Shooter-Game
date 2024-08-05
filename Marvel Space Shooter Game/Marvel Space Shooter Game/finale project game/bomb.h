// Bomb.h
#ifndef BOMB_H
#define BOMB_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Bomb {
public:
    Sprite sprite;
    float damage;
    bool isActive;
    Vector2f velocity;

    // Constructor with an additional argument for velocity
    Bomb(const std::string& png_path, float damage, Vector2f velocity)
        : damage(damage), isActive(true), velocity(velocity) {
        Texture* texture = new Texture();
        if (!texture->loadFromFile(png_path)) {
            // Handle error
        }
        sprite.setTexture(*texture);
    }

    // Update method to be overridden by derived classes
    virtual void update(float deltaTime) {
        sprite.move(velocity * deltaTime);

    }

    virtual void explode() {
        // Explosion logic
    }

    virtual ~Bomb() {
        delete sprite.getTexture();
    }
};

#endif





