//
// Created by user on 22/05/2021.
//

#include <iostream>
#include "Achievement.h"

Achievement::Achievement(std::string title, std::string text, std::string icon) {
    if (!texture.loadFromFile(icon)) {
        //TODO handle exception
    }
    sprite.setTexture(texture);
    sprite.setScale(3,3);
    sprite.setPosition(SCREENWIDTH/2 - sprite.getGlobalBounds().width - 6 , 5);
    Achievement::title.setString(title);
    achievementText.setString(text);
    rect = sf::RectangleShape(sf::Vector2f(SCREENWIDTH/2,100));
    rect.setPosition(SCREENWIDTH/2 - sprite.getGlobalBounds().width - 16, 0);
    rect.setFillColor(sf::Color::Blue);
    if(!font.loadFromFile("../Fonts/arial.ttf")){
        //TODO handle exception
    }
    Achievement::title.setFont(font);
    Achievement::title.setCharacterSize(30);
    Achievement::title.setFillColor(sf::Color::Red);
    Achievement::title.setPosition(SCREENWIDTH/2, 0);
    achievementText.setFont(font);
    achievementText.setCharacterSize(24);
    achievementText.setFillColor(sf::Color::White);
    achievementText.setPosition(SCREENWIDTH/2, 40);
}

bool Achievement::isUnlocked() const {
    return unlocked;
}

void Achievement::unlock() {
    Achievement::unlocked = true;
}

const sf::Text &Achievement::getTitle() const {
    return title;
}

const sf::Text &Achievement::getAchievementText() const {
    return achievementText;
}

const sf::Sprite &Achievement::getSprite() const {
    return sprite;
}

const sf::RectangleShape &Achievement::getRect() const {
    return rect;
}

void AchievementManager::onNotify(const Player &player, Event event) {
    switch (event)
       {
           case Event::EVENT_DEATH:
               if (!player.isAlive())
               {
                   Achievement* ach = new Achievement("First death", "You've died for the first time");
                   if(!isUnlocked(ach)){
                       unlock(ach);
                       achUnlocked.push_back(ach);
                   }
               }
               break;
           case Event::EVENT_100DISTANCE:
               Achievement* ach = new Achievement("Runner 100", "You've run 100 m");
               if(!isUnlocked(ach)){
                   unlock(ach);
                   achUnlocked.push_back(ach);
               }
        }
}

void AchievementManager::unlock(Achievement* achievement) {
    if (!achievement->isUnlocked()) {
        achievement->unlock();
        clock.restart();
        isLoading = false;
    }
}

bool AchievementManager::isUnlocked(Achievement* ach){
    for(auto i : achUnlocked){
        if (ach->getTitle().getString() == i->getTitle().getString()){
            //Già sbloccato
            delete ach;
            return true;
        }
    }
    return false;
}

void AchievementManager::draw(sf::RenderWindow &window) {
    if(achUnlocked.size() != 0 && clock.getElapsedTime().asSeconds() <= 3){
        if(!isLoading){
            window.draw(achUnlocked.back()->getRect());
            window.draw(achUnlocked.back()->getTitle());
            window.draw(achUnlocked.back()->getAchievementText());
            window.draw(achUnlocked.back()->getSprite());
        }
    }
}

const std::vector<Achievement *> &AchievementManager::getAchUnlocked() const {
    return achUnlocked;
}

void AchievementManager::setAchUnlocked(Achievement *achievement) {
    achUnlocked.push_back(achievement);
}
