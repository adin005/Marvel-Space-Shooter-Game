#ifndef GAMMA_BOMB_H
#define GAMMA_BOMB_H

#include "Bomb.h"

class GammaBomb : public Bomb {
public:
    GammaBomb(const std::string& png_path, float damage, Vector2f velocity)
        : Bomb(png_path, damage, velocity) {}

    // Override the update method
    void update(float deltaTime) override {
        // Specific update logic for AlphaBomb
        Bomb::update(deltaTime); // Call the base class update
    }
};

#endif
