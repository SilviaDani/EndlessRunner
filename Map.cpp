//
// Created by danis on 06/01/2021.
//

#include <iostream>
#include "Map.h"
#include "Player.h"
#include <random>
#include "Game.h"
#include "StateGame.h"


Map::Map() {
    try {
        if (!font.loadFromFile("./Fonts/arial.ttf")){
            throw std::runtime_error("File not found: ./Fonts/arial.ttf");
        }
    }
    catch (const std::runtime_error& exc) {
        std::cerr << exc.what() << std::endl;
        exit(-1);
    }
    distance.setFont(font);
    distance.setCharacterSize(24);
    distance.setFillColor(sf::Color::Black);


    try {
        if (!backgroundTexture.loadFromFile("./Sprites/yoshisbackground.png")) {
            throw std::runtime_error("File not found: ./Sprites/yoshisbackground.png");
        }
    }
    catch (const std::runtime_error& exc) {
        std::cerr << exc.what() << std::endl;
        exit(-1);
    }
    clock.restart();
    sf::Sprite bgSprite1, bgSprite2, lSprite1, lSprite2, gSprite1, gSprite2;
    bgSprite1.setTexture(backgroundTexture);
    bgSprite2.setTexture(backgroundTexture);
    double bgScale = static_cast<double>(SCREENWIDTH)/backgroundTexture.getSize().x;
    bgSprite1.setScale(bgScale,bgScale);
    bgSprite1.setPosition(0,0);
    bgSprite2.setScale(bgScale,bgScale);
    bgSprite2.setPosition(bgSprite1.getLocalBounds().width * bgScale, 0);
    backgroundSprites.push_back(bgSprite1);
    backgroundSprites.push_back(bgSprite2);


    try {
        if (!landTexture.loadFromFile("./Sprites/yoshisland.png")) {
            throw std::runtime_error("File not found: ./Sprites/yoshisland.png");
        }
    }
    catch (const std::runtime_error& exc) {
        std::cerr << exc.what() << std::endl;
        exit(-1);
    }
    lSprite1.setTexture(landTexture);
    lSprite2.setTexture(landTexture);
    double lScale = static_cast<double>(SCREENWIDTH)/landTexture.getSize().x;
    lSprite1.setScale(lScale, lScale);
    lSprite1.setPosition(0, LHEIGHT);
    lSprite2.setScale(lScale,lScale);
    lSprite2.setPosition(lSprite1.getLocalBounds().width * lScale, LHEIGHT);
    landSprites.push_back(lSprite1);
    landSprites.push_back(lSprite2);


    try {
        if (!grassTexture.loadFromFile("./Sprites/yoshisgrass.png")){
            throw std::runtime_error("File not found: ./Sprites/yoshigrass.png");
        }
    }
    catch (const std::runtime_error& exc) {
        std::cerr << exc.what() << std::endl;
        exit(-1);
    }
    gSprite1.setTexture(grassTexture);
    gSprite2.setTexture(grassTexture);
    double gScale = static_cast<double>(SCREENWIDTH)/grassTexture.getSize().x;
    gSprite1.setScale(gScale, gScale);
    gSprite1.setPosition(0, LHEIGHT - grassTexture.getSize().y + 2);
    gSprite2.setScale(gScale,gScale);
    gSprite2.setPosition(gSprite1.getLocalBounds().width * gScale, LHEIGHT - grassTexture.getSize().y + 2);
    grassSprites.push_back(gSprite1);
    grassSprites.push_back(gSprite2);


    try {
        if (!powerUpTexture.loadFromFile("./Sprites/block.png")) {
            throw std::runtime_error("File not found: ./Sprites/block.png");
        }
    }
    catch (const std::runtime_error& exc) {
        std::cerr << exc.what() << std::endl;
        exit(-1);
    }


    try {
        if (!coinTexture.loadFromFile("./Sprites/coin.png")) {
            throw std::runtime_error("File not found: ./Sprites/coin.png");
        }
    }
    catch (const std::runtime_error& exc) {
        std::cerr << exc.what() << std::endl;
        exit(-1);
    }


    try {
        if (!buffer.loadFromFile("./Sounds/parrySound.wav"))
            throw std::runtime_error("File not found: ./Sounds/parrySound.wav");
        parrySound.setBuffer(buffer);
        parrySound.setLoop(false);
    }
    catch (const std::runtime_error& exc) {
        std::cerr << exc.what() << std::endl;
        exit(-1);
    }
}

void Map::draw(sf::RenderWindow &window){
    for (auto i : backgroundSprites)
        window.draw(i);
    for (auto j : landSprites)
        window.draw(j);
    for (auto k : grassSprites)
        window.draw(k);
    for (auto l : obstacles)
        l->draw(window);
    for (auto m : powerUpSprite)
        window.draw(m);
    for (int n = 0; n < coins.size(); n++)
        coins.at(n).draw(window, 5);
    if(StateGame* sg = dynamic_cast<StateGame*>(Game::getInstance()->getState())){
        acceleration = 1/sg->getAcceleration() *0.5f ;
        coveredDistance = clock.getElapsedTime().asSeconds() * INIT_SPEEDL * acceleration;
    }

    totalDistance += coveredDistance;
    if (coveredDistance >= 100)
        notify(Game::getInstance()->getPlayer(), EventType::EVENT_100DISTANCE);
    distance.setString(std::to_string(coveredDistance));
    window.draw(distance);
}


void Map::moveBackground() {
    for (unsigned short int i = 0; i < backgroundSprites.size(); i++){
        if (StateGame* sg = dynamic_cast<StateGame*>(Game::getInstance()->getState())) {
            float movement = INIT_SPEEDB * acceleration;
            backgroundSprites.at(i).move(-movement,0.0f);
            if (backgroundSprites.at(i).getPosition().x < 0 - backgroundSprites.at(i).getGlobalBounds().width) {
                sf::Vector2f position(backgroundSprites.at((i + 1) % backgroundSprites.size()).getPosition().x
                                  + backgroundSprites.at((i + 1) % backgroundSprites.size()).getGlobalBounds().width - 5.0f, 0.0f);
                backgroundSprites.at(i).setPosition(position);
            }
        }
    }
}


void Map::moveLand() {
    for (unsigned short int j = 0; j < landSprites.size(); j++){
        if (dynamic_cast<StateGame*>(Game::getInstance()->getState())) {
            float movement = INIT_SPEEDL * acceleration;
            landSprites.at(j).move(-movement, 0);
            if (landSprites.at(j).getPosition().x <= 0 - landSprites.at(j).getGlobalBounds().width){
                sf::Vector2f position(landSprites.at((j+1)%landSprites.size()).getPosition().x - 5.0f
                + landSprites.at((j+1)%landSprites.size()).getGlobalBounds().width, LHEIGHT);
                landSprites.at(j).setPosition(position);
            }
        }
    }
}

void Map::moveGrass() {
    for (unsigned short int k = 0; k < grassSprites.size(); k++){
        if (dynamic_cast<StateGame*>(Game::getInstance()->getState())){
            float movement =INIT_SPEEDL * acceleration;
            grassSprites.at(k).move(-movement, 0);
            if (grassSprites.at(k).getPosition().x <= 0 - grassSprites.at(k).getGlobalBounds().width) {
                sf::Vector2f position(grassSprites.at((k + 1) % grassSprites.size()).getPosition().x
                                      + grassSprites.at((k + 1) % grassSprites.size()).getGlobalBounds().width - 5.0f,
                                      LHEIGHT - grassTexture.getSize().y + 2);
                grassSprites.at(k).setPosition(position);
            }
        }
    }
}


void Map::checkCollisions(Player& player) {
    if (dynamic_cast<Giant*>(player.getForm())){
        if (player.getPosition().y - (player.getGlobalBounds().height)/2 < 0)
            player.setPosition(player.getPosition().x, (player.getGlobalBounds().height)/2);
        if (player.getPosition().y + (player.getGlobalBounds().height)  > LHEIGHT + 2)
            player.setPosition(player.getPosition().x, LHEIGHT - (player.getGlobalBounds().height) + 2);
    }
    else if (dynamic_cast<GravityInverter*>(player.getForm())){
        if (player.getPosition().y - (player.getGlobalBounds().height)/2 < 0)
            player.setPosition(player.getPosition().x, (player.getGlobalBounds().height)/2);
        if (player.getPosition().y + (player.getGlobalBounds().height)/2  > LHEIGHT + 2)
            player.setPosition(player.getPosition().x, LHEIGHT - (player.getGlobalBounds().height)/2 + 2);
    }
    else{
        if (player.getPosition().y < 0)
            player.setPosition(player.getPosition().x, 0.0f);
        if (player.getPosition().y + player.getGlobalBounds().height  > LHEIGHT + 2)
            player.setPosition(player.getPosition().x, LHEIGHT - player.getGlobalBounds().height + 2);
    }
    for (auto k : powerUpSprite){
        if (player.getGlobalBounds().intersects(k.getGlobalBounds())) {
            powerUpSprite.pop_back();
            player.changeForm();
            obstacles.clear();
        }
    }
    for (int i = 0; i<coins.size(); i++){
        if (player.getGlobalBounds().intersects(coins.at(i).getGlobalBounds())) {
            coins.erase(coins.begin() + i);
            pickedCoins++;
        }
    }
    for (auto i : obstacles) {
        Giant* form = dynamic_cast<Giant*>(player.getForm());
        if (form){
            if (form->getBodySprite().getGlobalBounds().intersects(i->getObstacleSprite().getGlobalBounds())
            || form->getTongueSprite().getGlobalBounds().intersects(i->getObstacleSprite().getGlobalBounds())) {
                player.changeForm();
                obstacles.clear();
            }
        }
        if (player.getGlobalBounds().intersects(i->getObstacleSprite().getGlobalBounds())) {
            if (form) {
                parrySound.play();
                for (int n = 0; n<obstacles.size(); n++) {
                    if (player.getGlobalBounds().intersects(obstacles.at(n)->getObstacleSprite().getGlobalBounds())) {
                        obstacles.erase(obstacles.begin() + n);
                    }
                }
            }
            else {
                if (dynamic_cast<Yoshi *>(player.getForm())) {
                    player.kill();
                    obstacles.clear();
                    currentScore = coveredDistance + pickedCoins;
                    notify(player, EventType::EVENT_DEATH);
                    Game::getInstance()->save();
                    if (currentScore > highscore) {
                        highscore = currentScore;
                    }
                }
                else {
                    player.changeForm();
                    obstacles.clear();
                }
            }
        }
    }
}

void Map::moveObstacle() {
    float movement =INIT_SPEEDL*(1+acceleration*0.1f);
    for (int j = 0; j < obstacles.size(); j++)
        obstacles.at(j)->move(-movement, 0);
    for (auto i : obstacles){
        i->doAction();
    }
}

void Map::instantiateObstacle() {
    Obstacle* tmp;
    int rndm = rand() % 100;
    Giant* formg = dynamic_cast<Giant*>(Game::getInstance()->getPlayer().getForm());
    Bike* formb = dynamic_cast<Bike*>(Game::getInstance()->getPlayer().getForm());
    if (rndm < 50 || formg || formb)
        tmp = obstacleFactory.factoryMethod(ObstacleType::Rocket);
    else
        tmp = obstacleFactory.factoryMethod(ObstacleType::Stone);
    obstacles.push_back(tmp);
}

void Map::movePowerUp() {
    for (int m = 0; m < powerUpSprite.size(); m++){
        powerUpSprite.at(m).move(-INIT_SPEEDL*(1+acceleration*0.1f),0);
        if (powerUpSprite.at(m).getPosition().x < 0 - powerUpSprite.at(m).getGlobalBounds().width - 3)
            powerUpSprite.pop_back();
    }
}

void Map::instantiatePowerUp(Player& player) {
    if (Yoshi* form = dynamic_cast<Yoshi*>(player.getForm())) {
        if (form->getClock().getElapsedTime().asSeconds() >= 5) {
            sf:: Sprite pSprite;
            pSprite.setTexture(powerUpTexture);
            pSprite.setPosition(SCREENWIDTH + 2, SCREENHEIGHT/6);
            pSprite.setScale(2.5,2.5);
            powerUpSprite.push_back(pSprite);
            form->resetClock();
        }
    }
}


void Map::instantiateCoin() {
    int nFrames = 4;
    AnimatedSprite coinSprite = AnimatedSprite(coinTexture, coinTexture.getSize().y, coinTexture.getSize().x/nFrames, nFrames);
    coinSprite.setPosition(SCREENWIDTH + 2,  rand()%((int)(LHEIGHT - coinSprite.getGlobalBounds().height*2) - 1));
    coinSprite.setScale(2.3,2.3);
    coins.push_back(coinSprite);
}

void Map::moveCoin() {
    for (int n = 0; n < coins.size(); n++){
        coins.at(n).move(-INIT_SPEEDL*(1+acceleration*0.1f),0);
        if (coins.at(n).getPosition().x < 0 - coins.at(n).getGlobalBounds().width - 3)
            coins.erase(coins.begin());
    }
}

void Map::reset() {
    obstacles.clear();
    powerUpSprite.clear();
    coins.clear();
    currentScore = 0;
    coveredDistance = 0;
    pickedCoins = 0;
    clock.restart();
}

int Map::getHighscore() const {
    return highscore;
}

void Map::setHighscore(int highscore) {
    Map::highscore = highscore;
}

int Map::getTotalDistance() const {
    return totalDistance;
}

void Map::setTotalDistance(int totalDistance) {
    Map::totalDistance = totalDistance;
}

int Map::getCurrentScore() const {
    return currentScore;
}

int Map::getCoveredDistance() const {
    return coveredDistance;
}

const sf::Clock &Map::getClock() const {
    return clock;
}

std::vector<Obstacle *> Map::getObstacles() const {
    return obstacles;
}

std::vector<AnimatedSprite> Map::getCoins() const {
    return coins;
}

void Map::setPositionCoin(int i, float x, float y) {
    coins.at(i).setPosition(x, y);
}

std::vector<sf::Sprite> Map::getPowerUp() const{
    return powerUpSprite;
}

void Map::setPowerUpPosition(float x, float y) {
    powerUpSprite.at(0).setPosition(x, y);
}

int Map::getPickedCoins() const {
    return pickedCoins;
}



