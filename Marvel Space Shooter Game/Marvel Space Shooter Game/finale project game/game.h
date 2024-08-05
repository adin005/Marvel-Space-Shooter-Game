#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp> // Add for music
#include <time.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

#include "Player.h"
#include "Enemy.h"
#include "Invader.h"
#include "Alpha.h"
#include "Beta.h"
#include "Gamma.h"
#include "Bomb.h"
#include "AlphaBomb.h"
#include "BetaBomb.h"
#include "GammaBomb.h"
#include "Monster.h"
#include "Bullet.h"
#include "dragon.h"
#include "Danger.h"
#include "FirePowerUp.h"
#include "LivesPowerUp.h"
#include "ShootingPowerUp.h"
#include "powerup.h"



const char title[] = "OOP-Project, Spring-2024";
using namespace sf;

class Game {
public:
    Sprite background;
    Texture bg_texture;
    Player* p;
    std::vector<Enemy*> enemies;
    std::vector<Bomb*> bombs;
    std::vector<Bullet*> bullets;
    // New vector to store bullets
    std::vector<PowerUp*> powerUps;
    std::vector<Texture> levelBackgrounds;
    Clock clock;
    float spawnTimer;
    float spawnInterval = 2.0f;
    float maxEnemies = 5;
    float elapsedTime = 0;
    float rotationSpeed = 300.0f; // Degrees per second for smooth rotation
    float dangerTimer = 0.0f;
    bool dangerSignSpawnAllowed = true;
    int highScore = 0;
    int lives = 3;
    float livesPowerUpTimer = 0.0f;

    enum GameState { Playing, Paused, Menu } state;

    void spawnPowerUp() {
        // Generate random position for the power-up
        float randomX = static_cast<float>(rand() % 1600);
        float randomY = static_cast<float>(rand() % 600);

        // Randomly choose a type of power-up to spawn
        int powerUpType = rand() % 3; // Change the number based on the number of power-up types

        // Spawn the selected power-up
        PowerUp* powerUp = nullptr;
        if (powerUpType == 0) {
            powerUp = new FirePowerUp("img/R.png", 0.06f, 0.06f);
        }
        else if (powerUpType == 1) {
            powerUp = new LivesPowerUp("img/hammer.png", 0.06f, 0.06f);
        }
        else if (powerUpType == 2) {
            powerUp = new ShootingPowerUp("img/R(3).png", 0.08f, 0.08f);
        }

        if (powerUp) {
            powerUp->setPosition(randomX, randomY);
            powerUps.push_back(powerUp);
        }
    }


    void playLevelMusic(const std::string& musicPath) {
        // Stop any currently playing music
        music.stop();

        // Load and play the specified music
        if (!music.openFromFile(musicPath)) {
            std::cerr << "Error loading level music: " << musicPath << std::endl;
            return;
        }
        music.setLoop(true);
        music.play();
    }

    Game() : state(Menu) {
        p = new Player("img/iron.png", 0.2f, 0.2f);
        loadBackgrounds(); // Load backgrounds for all levels
        setBackgroundForLevel(1); // Set the initial background

        if (!bg_texture.loadFromFile("img/beeg.jpg")) {
            // Handle error
        }

        background.setTexture(bg_texture);
        background.setScale(2, 1.5);

        // Initialize other game variables as needed
        spawnTimer = 0.0f; // Initialize spawnTimer
        elapsedTime = 0.0f; // Initialize elapsedTime
    }


    void loadBackgrounds() {
        levelBackgrounds.resize(2);
        if (!levelBackgrounds[0].loadFromFile("img/purpur1.jpg")) {
            std::cerr << "Error loading level 1 background." << std::endl;
        }
        if (!levelBackgrounds[1].loadFromFile("img/purpur3.png")) {
            std::cerr << "Error loading level 2 background." << std::endl;
        }
        if (!levelBackgrounds[2].loadFromFile("img/blue1.jpg")) {
            std::cerr << "Error loading level 3 background." << std::endl;
        }
        if (!levelBackgrounds[3].loadFromFile("img/red1.jpg")) {
            std::cerr << "Error loading level 4 background." << std::endl;
        }
        if (!levelBackgrounds[4].loadFromFile("img/red1.jpg")) {
            std::cerr << "Error loading level 5 background." << std::endl;
        }

    }

    void setBackgroundForLevel(int level) {
        if (level >= 1 && level <= 5) {
            background.setTexture(levelBackgrounds[level - 1]);
        }
    }

    void spawnEnemy() {
        float randomX = static_cast<float>(rand() % 1600);
        float randomSpeed = 100.0f + static_cast<float>(rand() % 200);

        Invader* invader = nullptr;

        if (currentLevel == 1) {
            // Only spawn Alpha enemies for level 1
            invader = new Alpha("img/alpha1.png", 0.06f, 0.06f, 1, 10);
        }
        else if (currentLevel == 2) {
            // Only spawn Beta enemies for level 2
            invader = new Beta("img/beta1.png", 0.06f, 0.06f, 1, 10);
        }
        else if (currentLevel == 3) {
            // Spawn a mix of Alpha, Beta, and Gamma enemies for level 3
            int randomType = rand() % 3;
            if (randomType == 0) {
                invader = new Alpha("img/alpha1.png", 0.06f, 0.06f, 1, 10);
            }
            else if (randomType == 1) {
                invader = new Beta("img/beta1.png", 0.06f, 0.06f, 1, 10);
            }
            else {
                invader = new Gamma("img/gamma4.png", 0.06f, 0.06f, 1, 10);
            }
        }
        else if (currentLevel == 4) {
            // Spawn Beta enemies for level 4
            invader = new Beta("img/beta1.png", 0.06f, 0.06f, 1, 10);
        }
        else if (currentLevel == 5) {
            // Spawn Gamma enemies for level 5
            invader = new Gamma("img/gamma4.png", 0.06f, 0.06f, 1, 10);
        }

        invader->sprite.setPosition(randomX, 100);
        invader->speed = randomSpeed;
        enemies.push_back(invader);
    }

    void start_game() {
        srand(static_cast<unsigned int>(time(0)));
        RenderWindow window(VideoMode(1000, 700), title);
        dangerTimer = 0.0f;
        dangerSignSpawnAllowed = true;
        float SpawnPowerUpTimer = 0.0f;


        while (window.isOpen()) {
            float deltaTime = clock.restart().asSeconds(); // Declare deltaTime here
            if (state == Playing) {
                handleCollisions();
                elapsedTime += deltaTime;
                dragonTimer += deltaTime;
                SpawnPowerUpTimer += deltaTime; // Update SpawnPowerUpTimer separately

            }


            Event e;
            while (window.pollEvent(e)) {
                if (e.type == Event::Closed)
                    window.close();
                if (e.type == Event::KeyPressed) {
                    if (e.key.code == Keyboard::P) {
                        if (state == Playing)
                            state = Paused;
                        else if (state == Paused)
                            state = Playing;
                    }
                    else if (e.key.code == Keyboard::Escape) {
                        if (state == Playing || state == Paused)
                            state = Menu; // Change state to Menu when Escape is pressed
                        else if (state == Menu)
                            state = Playing;
                    }
                    else if (e.key.code == Keyboard::R) {
                        resetGame(); // Restart the game
                    }
                }
            }

            if (state == Playing) {
                if (elapsedTime >= spawnTimer) {
                    if (enemies.size() < maxEnemies) {
                        spawnEnemy();
                        spawnTimer = spawnInterval + static_cast<float>(rand() % 3);
                        elapsedTime = 0;
                    }
                }


                if (SpawnPowerUpTimer >= 10.0f) {
                    spawnPowerUp();
                    SpawnPowerUpTimer = 0.0f; // Reset SpawnPowerUpTimer after spawning
                }



                if (dangerSignSpawnAllowed) {
                    if (rand() % 100 == 0) {
                        float randomX = static_cast<float>(rand() % 1600);
                        Danger* danger = new Danger("img/monster.png", 0.02f, 0.02f);
                        danger->sprite.setPosition(randomX, 0);
                        enemies.push_back(danger);
                        dangerSignSpawnAllowed = false;
                        dangerTimer = 0.0f;
                    }
                }
                else {
                    dangerTimer += deltaTime;
                    if (dangerTimer >= 10.0f) {
                        dangerSignSpawnAllowed = true;
                    }
                }


                Vector2f direction(0, 0);
                if (Keyboard::isKeyPressed(Keyboard::A))
                    direction.x -= 1;
                if (Keyboard::isKeyPressed(Keyboard::D))
                    direction.x += 1;
                if (Keyboard::isKeyPressed(Keyboard::W))
                    direction.y -= 1;
                if (Keyboard::isKeyPressed(Keyboard::S))
                    direction.y += 1;

                // Normalize diagonal movement to ensure constant speed
                if (direction != Vector2f(0, 0)) {
                    float length = sqrt(direction.x * direction.x + direction.y * direction.y);
                    direction /= length;
                }

                // Calculate the desired rotation angle
                float desiredAngle = p->sprite.getRotation();
                if (direction.x != 0 || direction.y != 0) {
                    desiredAngle = atan2(direction.y, direction.x) * 180 / 3.14159f + 90; // Adjust angle to match the sprite's orientation
                }

                // Smoothly interpolate to the desired angle
                float currentAngle = p->sprite.getRotation();
                if (currentAngle != desiredAngle) {
                    float angleDifference = desiredAngle - currentAngle;
                    if (angleDifference > 180) angleDifference -= 360;
                    if (angleDifference < -180) angleDifference += 360;
                    float rotationAmount = rotationSpeed * deltaTime;
                    if (abs(angleDifference) < rotationAmount) {
                        currentAngle = desiredAngle;
                    }
                    else {
                        currentAngle += rotationAmount * (angleDifference > 0 ? 1 : -1);
                    }
                    p->sprite.setRotation(currentAngle);
                }

                p->move(direction, deltaTime);
                p->update(deltaTime);

                // Handle shooting
                if (Keyboard::isKeyPressed(Keyboard::Space)) {
                    shoot();
                }

                updateBullets(deltaTime);

                // Invaders shooting bombs logic
                for (auto& enemy : enemies) {
                    enemy->shootBomb(bombs, deltaTime); // Call the shootBomb method with deltaTime
                }

                for (auto& enemy : enemies) {
                    if (dynamic_cast<Monster*>(enemy) != nullptr) {
                        Monster* monsterEnemy = dynamic_cast<Monster*>(enemy);
                        monsterEnemy->shootBeam(bombs, deltaTime);
                    }
                }

                for (auto& enemy : enemies) {
                    if (dynamic_cast<Dragon*>(enemy) != nullptr) {
                        Dragon* dragonEnemy = dynamic_cast<Dragon*>(enemy);
                        dragonEnemy->shootBomb(bombs, deltaTime, *p); // Pass the player object
                    }
                }

                // Update bombs
                for (auto& bomb : bombs) {
                    bomb->update(deltaTime);
                }

                updatePowerUps(deltaTime);



                // Remove inactive bombs
                bombs.erase(std::remove_if(bombs.begin(), bombs.end(), [](Bomb* bomb) {
                    return !bomb->isActive;
                    }), bombs.end());

                // Update enemies
                for (auto& enemy : enemies) {
                    Vector2f enemyDirection(0, 1);
                    enemy->move(enemyDirection, deltaTime);
                    enemy->update(deltaTime);
                }

                // Remove off-screen enemies
                enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [](Enemy* enemy) {
                    return enemy->sprite.getPosition().y > 1200;
                    }), enemies.end());

                // Update dragon logic if in level 5
                if (currentLevel == 5) {
                    updateDragon(deltaTime);

                }


            }

            window.clear();
            window.draw(background);
            window.draw(p->sprite);

            for (auto& bullet : bullets) {
                window.draw(bullet->sprite);
            }

            for (auto& bomb : bombs) {
                window.draw(bomb->sprite);
            }

            for (auto& enemy : enemies) {
                window.draw(enemy->sprite);
            }

            // Draw power-ups
            for (auto& powerUp : powerUps) {
                window.draw(powerUp->getSprite());
            }


            if (state == Paused) {
                // Display pause message
                Text pauseText;
                Font font;
                if (!font.loadFromFile("fonts/tech.ttf")) {
                    // Handle error
                }
                pauseText.setFont(font);
                pauseText.setString("Game Paused\nPress 'P' to Resume");
                pauseText.setCharacterSize(30);
                pauseText.setFillColor(Color::White);
                pauseText.setPosition(450, 250);
                window.draw(pauseText);
            }

            if (state == Menu) {
                // Display menu options
                Text menuText;
                Font font;
                if (!font.loadFromFile("fonts/tech.ttf")) {
                    // Handle error
                }
                menuText.setFont(font);
                menuText.setString("Menu:\nPress 'P' to Resume\nPress 'R' to Restart\nPress 'Esc' to Return to Game");
                menuText.setCharacterSize(30);
                menuText.setFillColor(Color::White);
                menuText.setPosition(450, 250);
                window.draw(menuText);
            }

            drawHighScore(window);
            drawPlayer(window);

            window.display();
        }
    }

    void start_level_1() {
        enemies.clear();
        currentLevel = 1; // Set current level
        setBackgroundForLevel(currentLevel); // Set background for level 1
        for (int i = 0; i < maxEnemies; ++i) {
            spawnAlpha(); // Alpha invaders
        }
        start_game();
    }

    void start_level_2() {
        enemies.clear();
        currentLevel = 2; // Set current level
        setBackgroundForLevel(currentLevel); // Set background for level 2
        for (int i = 0; i < maxEnemies; ++i) {
            spawnBeta();  // Beta invaders
        }
        start_game();
    }

    void start_level_3() {
        enemies.clear();
        currentLevel = 3; // Set current level
        setBackgroundForLevel(currentLevel); // Set background for level 3
        for (int i = 0; i < maxEnemies / 3; ++i) {
            spawnAlpha(); // One-third Alpha invaders
            spawnBeta();  // One-third Beta invaders
            spawnGamma(); // One-third Gamma invaders
        }
        start_game();
    }

    void start_level_4() {
        enemies.clear();
        currentLevel = 4; // Set current level
        setBackgroundForLevel(currentLevel); // Set background for level 4
        spawnMonster(); // Spawn the Monster
        for (int i = 0; i < maxEnemies; ++i) {
            spawnBeta();  // Beta invaders
        }

        // Wait for 1 second before starting the game to ensure the monster is added to the window
        sf::sleep(sf::seconds(1.0f));

        start_game();
    }

    void start_level_5() {
        enemies.clear();
        currentLevel = 5; // Set current level
        setBackgroundForLevel(currentLevel); // Set background for level 5
        spawnDragon(); // Spawn the Dragon
        setRandomDragonAppearance(); // Set random dragon appearance duration
        for (int i = 0; i < maxEnemies; ++i) {
            spawnGamma(); // Gamma invaders
        }
        start_game();
    }



private:
    int currentLevel = 1; // Track the current level
    bool dragonAppeared = false;
    float dragonTimer = 0.0f;
    const float dragonAppearanceInterval = 5.0f; // Fixed appearance interval of 5 seconds
    float dragonDuration;

    sf::Music music;

    void spawnAlpha() {
        float randomX = static_cast<float>(rand() % 1600);
        float randomSpeed = 100.0f + static_cast<float>(rand() % 200);

        Invader* invader = nullptr;

        invader = new Alpha("img/alpha1.png", 0.06f, 0.06f, 1, 10);

        invader->sprite.setPosition(randomX, 100);
        invader->speed = randomSpeed;
        enemies.push_back(invader);
    }

    void spawnBeta() {
        float randomX = static_cast<float>(rand() % 1600);
        float randomSpeed = 100.0f + static_cast<float>(rand() % 200);

        Invader* invader = nullptr;

        invader = new Beta("img/beta1.png", 0.06f, 0.06f, 1, 10);

        invader->sprite.setPosition(randomX, 100);
        invader->speed = randomSpeed;
        enemies.push_back(invader);
    }

    void spawnGamma() {
        float randomX = static_cast<float>(rand() % 1600);
        float randomSpeed = 100.0f + static_cast<float>(rand() % 200);

        Invader* invader = nullptr;

        invader = new Gamma("img/gamma4.png", 0.06f, 0.06f, 1, 10);

        invader->sprite.setPosition(randomX, 100);
        invader->speed = randomSpeed;
        enemies.push_back(invader);
    }

    void spawnMonster() {
        float randomX = static_cast<float>(rand() % 1600); // Random x position for the monster
        Monster* monster = new Monster("img/ultron 2.png", 0.2f, 0.2f);
        monster->sprite.setPosition(100, 80); // Ensure the monster has a starting position
        enemies.push_back(monster);
    }

    void spawnDragon() {
        // Spawn a Dragon instance
        Dragon* dragon = new Dragon("img/tha3.png", 0.2f, 0.2f); // Adjust scale as needed
        enemies.push_back(dragon);
    }


    void shoot() {
        // Get the position of the player's hand, adjust these values as needed
        float handOffsetX = p->sprite.getGlobalBounds().width * 0.001f; // Hand's X offset from the center of the sprite
        float handOffsetY = p->sprite.getGlobalBounds().height * 0.5f; // Hand's Y offset from the center of the sprite

        // Calculate the hand's position based on the player's rotation
        float rotationRadians = (p->sprite.getRotation() - 90) * 3.14159f / 180.0f; // Convert degrees to radians and adjust angle
        Vector2f handPosition(
            p->sprite.getPosition().x + cos(rotationRadians) * handOffsetX - sin(rotationRadians) * handOffsetY,
            p->sprite.getPosition().y + sin(rotationRadians) * handOffsetX + cos(rotationRadians) * handOffsetY
        );

        // Calculate the shooting direction based on the player's rotation
        Vector2f shootingDirection(cos(rotationRadians), sin(rotationRadians));

        // Create a new bullet and set its initial position and direction
        Bullet* bullet = new Bullet("img/l4.png");
        bullet->sprite.setPosition(handPosition);
        bullet->direction = shootingDirection; // Set the bullet's direction
        bullets.push_back(bullet);
    }

    void updateBullets(float deltaTime) {

        for (auto it = bullets.begin(); it != bullets.end();) {
            Bullet* bullet = *it;
            bullet->update(deltaTime);
            if (bullet->sprite.getPosition().y < 0) {
                // Bullet has left the screen, remove it
                delete bullet;
                it = bullets.erase(it);
            }
            else {
                ++it;
            }
        }
    }

    void setRandomDragonAppearance() {
        // Generate random duration within the specified limits (0 to 100 seconds)
        dragonDuration = 5.0f; // Duration between 0 and 100 seconds
    }

    void updateDragon(float deltaTime) {
        // Ensure dragon updates only in level 5
        if (!dragonAppeared && dragonTimer >= dragonAppearanceInterval) {
            spawnDragon(); // Spawn the dragon
            dragonAppeared = true; // Set flag to indicate dragon appeared
            dragonTimer = 0.0f; // Reset timer
        }

        // Check if it's time to make the dragon disappear
        if (dragonAppeared && dragonTimer >= dragonDuration) {
            // Remove the dragon from the enemies vector
            enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [](Enemy* enemy) {
                return dynamic_cast<Dragon*>(enemy) != nullptr;
                }), enemies.end());
            dragonAppeared = false; // Set flag to indicate dragon disappeared
            dragonTimer = 0.0f; // Reset timer
        }
    }

    /**
  * Check collision between two sprites with adjustable hitbox shrink amounts.
  *
  * @param sprite1 The first sprite's bounding box, intended to be the player.
  * @param sprite2 The second sprite's bounding box, intended to be the bullet.
  * @param shrinkAmount1 The amount to shrink the first sprite's hitbox.
  * @param shrinkAmount2 The amount to shrink the second sprite's hitbox.
  * @return True if the bounding boxes intersect, false otherwise.
  */
    bool checkCollision(const sf::Sprite& sprite1, const sf::Sprite& sprite2) {
        // Calculate the bounding box of both sprites
        sf::FloatRect bounds1 = sprite1.getGlobalBounds();
        sf::FloatRect bounds2 = sprite2.getGlobalBounds();


        // Check for intersection
        return bounds1.intersects(bounds2);
    }

    void handleCollisions() {
        bool playerHit = false; // Flag to track if the player is hit in this frame

        // Check for collisions between player and enemy bombs
        for (auto it = bombs.begin(); it != bombs.end();) {
            Bomb* bomb = *it;
            if (checkCollision(p->sprite, bomb->sprite)) {
                playerHit = true; // Set flag to true if collision occurs
                delete bomb;
                it = bombs.erase(it); // Remove the bomb
            }
            else {
                ++it;
            }
        }

        // Check for collisions between player and danger signs
        for (auto dangerIt = enemies.begin(); dangerIt != enemies.end();) {
            Danger* danger = dynamic_cast<Danger*>(*dangerIt);
            if (danger && checkCollision(p->sprite, danger->sprite)) {
                playerHit = true; // Set flag to true if collision occurs
                delete danger;
                dangerIt = enemies.erase(dangerIt); // Remove the danger sign
            }
            else {
                ++dangerIt;
            }
        }

        // If the player is hit, decrement lives once and reset position
        if (playerHit) {
            p->decrementLives(); // Use player's decrementLives method
            if (p->lives <= 0) {
                endGame();
            }
            else {
                resetPlayer(); // Reset player position
            }
        }
        else {
            // Increment high score for dodging bombs and danger signs
            highScore += 5; // Increase high score by 5 points when the player dodges
        }

        // Check for collisions between player bullets and enemies
        for (auto bulletIt = bullets.begin(); bulletIt != bullets.end();) {
            Bullet* bullet = *bulletIt;
            bool bulletRemoved = false;
            for (auto enemyIt = enemies.begin(); enemyIt != enemies.end();) {
                Enemy* enemy = *enemyIt;
                if (dynamic_cast<Danger*>(enemy) == nullptr) { // Skip Danger objects
                    if (checkCollision(bullet->sprite, enemy->sprite)) {
                        // Bullet hit an enemy, remove both bullet and enemy
                        delete bullet;
                        bulletIt = bullets.erase(bulletIt);
                        delete enemy;
                        enemyIt = enemies.erase(enemyIt);
                        bulletRemoved = true;
                        highScore += 10; // Increase high score by 10 points for hitting an enemy
                        break;
                    }
                    else {
                        ++enemyIt;
                    }
                }
                else {
                    ++enemyIt;
                }
            }
            if (!bulletRemoved) {
                ++bulletIt;
            }
        }
    }



    void updatePowerUps(float deltaTime) {
        for (auto it = powerUps.begin(); it != powerUps.end();) {
            PowerUp* powerUp = *it;
            // Check if player collects the power-up based on its type
            if (checkCollision(p->sprite, powerUp->getSprite())) {
                // Player collected the power-up
                if (dynamic_cast<ShootingPowerUp*>(powerUp) != nullptr) {
                    // Call the collect() function of the ShootingPowerUp class
                    dynamic_cast<ShootingPowerUp*>(powerUp)->collect(*p);
                }
                delete powerUp;
                it = powerUps.erase(it);
            }
            else {
                ++it;
            }
        }
    }


    void resetPlayer() {
        p->sprite.setPosition(Vector2f(500, 500)); // Reset player position
        p->sprite.setRotation(0); // Reset player rotation
    }


    void drawHighScore(RenderWindow& window) {
        Font font;
        if (!font.loadFromFile("fonts/tech.ttf")) {
            // Handle error
        }

        Text highScoreText;
        highScoreText.setFont(font);
        highScoreText.setString("Highscore: " + std::to_string(highScore));
        highScoreText.setCharacterSize(30);
        highScoreText.setFillColor(Color::White);
        highScoreText.setPosition(10, 10);
        window.draw(highScoreText);
    }

    void drawPlayer(RenderWindow& window) {
        // ...
        window.draw(p->sprite);
        // Draw the number of lives
        Font font;
        if (!font.loadFromFile("fonts/tech.ttf")) {
            // Handle error
        }

        Text livesText;
        livesText.setFont(font);
        livesText.setString("Lives: " + std::to_string(p->lives));
        livesText.setCharacterSize(30);
        livesText.setFillColor(Color::White);
        livesText.setPosition(10, 50);
        window.draw(livesText);


    }


    void endGame() {
        // Implement game over logic here
        std::cout << "Game Over\n";
        state = Menu;
        // Additional logic can be added, such as displaying a game over screen, resetting the game, etc.
    }

    void resetGame() {
        bombs.clear();
        bullets.clear();
        lives = 3; // Reset lives
        highScore = 0; // Reset high score
        resetPlayer(); // Reset player position
        elapsedTime = 0;
        dragonTimer = 0;
        dragonAppeared = false;
        state = Playing;
    }
};



#endif; // GAME_H