//
// Created by user on 05/08/2021.
//

#ifndef ENDLESSRUNNER_STATEMAINMENU_H
#define ENDLESSRUNNER_STATEMAINMENU_H
#include "State.h"

class StateMainMenu : public State {
public:
    StateMainMenu(Game *gameptr);
    void draw(sf::RenderWindow& window) override;
    void update() override;
    void changeState(State* nextState) override;
    //TODO void load(std::string path);
private:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Font font;
    sf::Font titleFont;
    sf::Text title;
    sf::Text text;
};


#endif //ENDLESSRUNNER_STATEMAINMENU_H
