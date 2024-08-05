#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include "Bomb.h"

using namespace sf;

class Enemy {
public:
    Sprite sprite;
    Texture texture;  // Add a texture member
    float speed;

    Enemy(const std::string& png_path, float scaleX = 1.0f, float scaleY = 1.0f) {
        if (!texture.loadFromFile(png_path)) {
            std::cerr << "Error loading texture from " << png_path << std::endl;
        }
        sprite.setTexture(texture);
        sprite.setScale(scaleX, scaleY);
    }

    virtual void move(Vector2f direction, float deltaTime) {
        sprite.move(direction * speed * deltaTime);
    }

    virtual void update(float deltaTime) {
        // Default implementation
    }

    virtual void shootBomb(std::vector<Bomb*>& bombs, float deltaTime) {
        // Default implementation or pure virtual if no default behavior
    }

    virtual ~Enemy() = default;
};

#endif // ENEMY_H


