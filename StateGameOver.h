//
// Created by user on 05/08/2021.
//

#ifndef ENDLESSRUNNER_STATEGAMEOVER_H
#define ENDLESSRUNNER_STATEGAMEOVER_H
#include "State.h"

class StateGameOver : public State {
public:
    StateGameOver(Game* gameptr);
    void draw(sf::RenderWindow& window) override;
    void update() override;
    void changeState(State* nextState) override;
private:
   // sf::Sprite sprite;
   // sf::Texture texture;
    sf::Font font;
    sf::Font titleFont;
    sf::Text title;
    sf::Text score;
    sf::Text text;
};


#endif //ENDLESSRUNNER_STATEGAMEOVER_H
