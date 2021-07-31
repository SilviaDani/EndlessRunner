//
// Created by user on 22/05/2021.
//

#ifndef ENDLESSRUNNER_ACHIEVEMENT_H
#define ENDLESSRUNNER_ACHIEVEMENT_H


#include "Observer.h"

class Achievement{
public:
    Achievement(std::string title, std::string icon = "icon.png"); //TODO scegliere e salvare icona tipo trofeino
    bool isUnlocked() const;
    void unlock();

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
};



#endif //ENDLESSRUNNER_ACHIEVEMENT_H
