// AlphaBomb.h
#ifndef ALPHA_BOMB_H
#define ALPHA_BOMB_H

#include "Bomb.h"

class AlphaBomb : public Bomb {
public:
    // Constructor that matches the Bomb base class constructor
    AlphaBomb(const std::string& png_path, float damage, Vector2f velocity)
        : Bomb(png_path, damage, velocity) {}

    // Override the update method
    void update(float deltaTime) override {
        // Specific update logic for AlphaBomb
        Bomb::update(deltaTime); // Call the base class update
    }
};

#endif