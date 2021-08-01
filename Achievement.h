//
// Created by user on 22/05/2021.
//

#ifndef ENDLESSRUNNER_ACHIEVEMENT_H
#define ENDLESSRUNNER_ACHIEVEMENT_H

#include <vector>
#include "Observer.h"

class Achievement{
public:
    Achievement(std::string title, std::string icon = "icon.png"); //TODO scegliere e salvare icona tipo trofeino
    bool isUnlocked() const;
    void unlock();
    const sf::Text &getTitle() const;
protected:
    sf:: Texture texture;
    sf:: Sprite sprite;
private:
    sf:: Text title;
    bool unlocked = false;
};

class AchievementManager : public Observer{
public:
    virtual void onNotify(const Player& player, Event event);
private:
    void unlock(Achievement* achievement);
    std::vector<Achievement*> achUnlocked;
    bool isUnlocked(Achievement *ach);
};



#endif //ENDLESSRUNNER_ACHIEVEMENT_H
