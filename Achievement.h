//
// Created by user on 22/05/2021.
//

#ifndef ENDLESSRUNNER_ACHIEVEMENT_H
#define ENDLESSRUNNER_ACHIEVEMENT_H

#include <vector>
#include "Observer.h"

class Achievement{
public:
    Achievement(std::string title, std::string text, std::string icon = "../Sprites/trophy.png");
    bool isUnlocked() const;
    void unlock();
    const sf::Text &getTitle() const;
    const sf::Text &getAchievementText() const;
    const sf::Sprite &getSprite() const;

    const sf::RectangleShape &getRect() const;

private:
    sf::Text title;
    bool unlocked = false;
    sf::Text achievementText;
    sf::Font font;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::RectangleShape rect;
};

class AchievementManager : public Observer{
public:
    virtual void onNotify(const Player& player, Event event);
    void draw(sf::RenderWindow& window);
private:
    void unlock(Achievement* achievement);
    std::vector<Achievement*> achUnlocked;
    bool isUnlocked(Achievement *ach);
};



#endif //ENDLESSRUNNER_ACHIEVEMENT_H
