//
// Created by danis on 06/01/2021.
//

#ifndef ENDLESSRUNNER_MAP_H
#define ENDLESSRUNNER_MAP_H
#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.h"
#include "Obstacle.h"
#include "ObstacleFactory.h"
#include "Subject.h"


class Map : public Subject {
public:
    Map();
    void draw(sf::RenderWindow &window);
    void moveBackground();
    void moveLand();
    void moveGrass();
    void checkCollisions(Player& player);
    void moveObstacle();
    void instantiateObstacle();
    void movePowerUp();
    void instantiatePowerUp(Player& player);
    void instantiateCoin();
    void moveCoin();
    void reset();
    int getHighscore() const;
    void setHighscore(int highscore);
    int getTotalDistance() const;
    void setTotalDistance(int totalDistance);
    int getCurrentScore() const;
    int getCoveredDistance() const;
    const sf::Clock &getClock() const;
    std::vector<AnimatedSprite>getCoins() const;
    void setPositionCoin(int i, float x, float y);
    std::vector<Obstacle*> getObstacles() const;
    std::vector<sf::Sprite> getPowerUp() const;
    void setPowerUpPosition(float x, float y);
    int getPickedCoins() const;

private:
    sf::Texture backgroundTexture;
    std::vector <sf::Sprite>backgroundSprites;
    sf::Texture landTexture;
    std::vector <sf::Sprite>landSprites;
    sf::Texture grassTexture;
    std::vector <sf::Sprite>grassSprites;
    std::vector <Obstacle*>obstacles;
    ObstacleFactory obstacleFactory;
    sf::Texture powerUpTexture;
    std::vector <sf::Sprite>powerUpSprite;
    sf::Texture coinTexture;
    std::vector <AnimatedSprite>coins;
    sf::Clock clock;
    sf::Text distance;
    sf::Font font;
    sf::SoundBuffer buffer;
    sf::Sound parrySound;
    int coveredDistance = 0;
    int highscore = 0;
    int totalDistance = 0;
    int currentScore = 0;
    int pickedCoins = 0;
    float acceleration = 1.0f;
};


#endif //ENDLESSRUNNER_MAP_H
