//
// Created by user on 05/08/2021.
//

#include "StateGameOver.h"
#include "StateGame.h"

StateGameOver::StateGameOver(Game *gameptr) {
    game = gameptr;
    if(!font.loadFromFile("../Fonts/arial.ttf")){
        //TODO handle exception
    }
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setPosition(SCREENWIDTH/2 - 90, SCREENHEIGHT - 35);
    text.setString("Press SPACE to play again, ESC to quit");
    score.setFont(font);
    score.setCharacterSize(24);
    score.setFillColor(sf::Color::White);
    score.setPosition(SCREENWIDTH/2 - 70, SCREENHEIGHT/2 - 60);
    score.setString("Current score:" + std::to_string(game->getMap().getCurrentScore())
            + "\nCovered distance:" + std::to_string(game->getMap().getCoveredDistance())
            + "\nHighscore:" + std::to_string(game->getMap().getHighscore()));

    if(!titleFont.loadFromFile("../Fonts/pixel.TTF")){
        //TODO handle exception
    }
    title.setFont(titleFont);
    title.setCharacterSize(40);
    title.setFillColor(sf::Color::Red);
    title.setPosition(SCREENWIDTH/2 - 100, 30);
    title.setString("GAME OVER");

}

void StateGameOver::draw(sf::RenderWindow &window) {
    window.clear(sf::Color::Black);
    window.draw(title);
    window.draw(score);
    window.draw(text);
}

void StateGameOver::update() {}

void StateGameOver::changeState(State *nextState) {
    if (State* s = dynamic_cast<StateGame*>(nextState)){
        game->getMap().reset();
        game->getPlayer().reset();
    }
    else
        game->getWindow()->close();
    if (nextState!= nullptr) {
        State* tmpState = game->getState();
        game->setState(nextState);
        delete tmpState;
    }
}

