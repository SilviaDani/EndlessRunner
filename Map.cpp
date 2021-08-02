//
// Created by danis on 06/01/2021.
//

#include <iostream>
#include "Map.h"
#include "Player.h"
#include <random>
#include "Game.h"


Map::Map() {
    if(!font.loadFromFile("../arial.ttf")){
        //TODO handle exception
    }
    distance.setFont(font);
    distance.setCharacterSize(24);
    distance.setFillColor(sf::Color::Black);

    if (!backgroundTexture.loadFromFile("../Sprites/yoshisbackground.png")) {
            //TODO handle exception
    }
    clock.restart();
    sf::Sprite bgSprite1, bgSprite2, lSprite1, lSprite2, gSprite1, gSprite2, pSprite;
    bgSprite1.setTexture(backgroundTexture);
    bgSprite2.setTexture(backgroundTexture);
    double bgScale = static_cast<double>(SCREENWIDTH)/backgroundTexture.getSize().x;
    bgSprite1.setScale(bgScale,bgScale);
    bgSprite1.setPosition(0,0);
    bgSprite2.setScale(bgScale,bgScale);
    bgSprite2.setPosition(bgSprite1.getLocalBounds().width * bgScale, 0);
    backgroundSprites.push_back(bgSprite1);
    backgroundSprites.push_back(bgSprite2);

    if (!landTexture.loadFromFile("../Sprites/yoshisland.png")) {
       //TODO handle exception
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

    if (!grassTexture.loadFromFile("../Sprites/yoshisgrass.png")){
        //TODO handle exception
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

    if (!powerUpTexture.loadFromFile("../Sprites/block.png")) {
        //TODO handle exception
    }
    pSprite.setTexture(powerUpTexture);
    pSprite.setPosition(SCREENWIDTH + 2, SCREENHEIGHT/6);
    pSprite.setScale(2.5,2.5);
    powerUpSprite.push_back(pSprite);
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
    coveredDistance = clock.getElapsedTime().asSeconds() * INIT_SPEEDL; //TODO aggiungi accelerazione
    if (coveredDistance >= 100)
        notify(Game::getInstance()->player, Event::EVENT_100DISTANCE);
    distance.setString(std::to_string(coveredDistance));
    window.draw(distance);
    //if ()
}


void Map::moveBackground() {
    for (unsigned short int i = 0; i < backgroundSprites.size(); i++){
        float movement = INIT_SPEEDB;
        backgroundSprites.at(i).move(-movement,0.0f);
        if (backgroundSprites.at(i).getPosition().x <= 0 - backgroundSprites.at(i).getLocalBounds().width * backgroundSprites.at(i).getScale().x){
            sf::Vector2f position(backgroundSprites.at((i+1)%backgroundSprites.size()).getPosition().x - 1
                    + backgroundSprites.at((i+1)%backgroundSprites.size()).getLocalBounds().width * backgroundSprites.at((i+1)%backgroundSprites.size()).getScale().x - 1, 0.0f);
            backgroundSprites.at(i).setPosition(position);
        }
    }
}


void Map::moveLand() {
    for (unsigned short int j = 0; j < landSprites.size(); j++){
        float movement =INIT_SPEEDL;
        landSprites.at(j).move(-movement, 0);
        if (landSprites.at(j).getPosition().x <= 0 - landSprites.at(j).getLocalBounds().width * landSprites.at(j).getScale().x){
           sf::Vector2f position(landSprites.at((j+1)%landSprites.size()).getPosition().x - 2
                    + landSprites.at((j+1)%landSprites.size()).getLocalBounds().width * landSprites.at((j+1)%landSprites.size()).getScale().x-1, LHEIGHT);
           landSprites.at(j).setPosition(position);
        }
    }
}

void Map::moveGrass() {
    for (unsigned short int k = 0; k < grassSprites.size(); k++){
        float movement =INIT_SPEEDL;
        grassSprites.at(k).move(-movement, 0);
        if (grassSprites.at(k).getPosition().x <= 0 - grassSprites.at(k).getLocalBounds().width * grassSprites.at(k).getScale().x){
            sf::Vector2f position(grassSprites.at((k+1)%grassSprites.size()).getPosition().x
                                  + grassSprites.at((k+1)%grassSprites.size()).getLocalBounds().width * grassSprites.at((k+1)%grassSprites.size()).getScale().x-1, LHEIGHT - grassTexture.getSize().y + 2);
            grassSprites.at(k).setPosition(position);
        }
    }
}


void Map::checkCollisions(Player& player) {
    if (Giant* form = dynamic_cast<Giant*>(player.form)){ //TODO cambia i limiti del gigante
        if (player.getPosition().y - (player.getGlobalBounds().height)/2 < 0)
            player.setPosition(player.getPosition().x, (player.getGlobalBounds().height)/2);
        if (player.getPosition().y + (player.getGlobalBounds().height)  > LHEIGHT + 2)
            player.setPosition(player.getPosition().x, LHEIGHT - (player.getGlobalBounds().height) + 2);
    }
    else if (GravityInverter* form = dynamic_cast<GravityInverter*>(player.form)){
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
            std::cout << "power up" << std::endl;
            powerUpSprite.pop_back();
            player.changeForm();
        }
    }
    for (auto i : obstacles) {
        Giant* form = dynamic_cast<Giant*>(player.form);
        if (player.getGlobalBounds().intersects(i->getObstacleSprite().getGlobalBounds())) {
            if (form) {
                std::cerr << "hai parato un missile" << std::endl;
                obstacles.pop_back();
            }
            else {
                if (Yoshi *form = dynamic_cast<Yoshi *>(player.form)) {
                    player.kill();
                    notify(player, Event::EVENT_DEATH);
                    std::cerr << "sei morto" << std::endl;
                    if (coveredDistance > highscore) {
                        highscore = coveredDistance; //TODO AGGIUNGI MONETE AL PUNTEGGIO
                        std::cerr << "new highscore!!"<< coveredDistance << std::endl;
                    }
                }
                else
                    player.changeForm(); //TODO implementa codice per vivere se pari i missili da gigante
                for (auto k : obstacles)
                    obstacles.pop_back();
            }
        }
    }
}

void Map::moveObstacle() {
    float movement =INIT_SPEEDL;
    for (int j = 0; j < obstacles.size(); j++)
        obstacles.at(j)->move(-movement, 0);
    for (auto i : obstacles){
        i->doAction();
    }
}

void Map::instantiateObstacle() {
    Obstacle* tmp;
    int rndm = rand() % 100;
    Giant* form = dynamic_cast<Giant*>(Game::getInstance()->player.form);
    if (rndm < 50 || form)
        tmp = rocketFactory.factoryMethod();
    else
        tmp = stoneFactory.factoryMethod();
    obstacles.push_back(tmp);

}

void Map::movePowerUp() {
    for (int m = 0; m < powerUpSprite.size(); m++){
        powerUpSprite.at(m).move(-INIT_SPEEDL,0);
        if (powerUpSprite.at(m).getPosition().x < 0 - powerUpSprite.at(m).getGlobalBounds().width - 3)
            powerUpSprite.pop_back();
    }
}

void Map::instantiatePowerUp(Player& player) {
    if (Yoshi* form = dynamic_cast<Yoshi*>(player.form)) {
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

