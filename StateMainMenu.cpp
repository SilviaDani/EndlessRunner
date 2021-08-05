//
// Created by user on 05/08/2021.
//

#include "StateMainMenu.h"
#include "StateGame.h"


StateMainMenu::StateMainMenu(Game *gameptr) {
    game = gameptr;
    if (!texture.loadFromFile("../Sprites/mainMenuBackground.jpg")) {
        //TODO handle exception
    }

    sprite.setTexture(texture);
    sprite.setPosition(0, 0);
    sprite.setScale(3,3.2);

    if(!font.loadFromFile("../Fonts/arial.ttf")){
        //TODO handle exception
    }
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);
    text.setPosition(SCREENWIDTH/2 - 30, SCREENHEIGHT - 60);
    text.setString("Press SPACE\nto play");

    if(!titleFont.loadFromFile("../Fonts/pixel.TTF")){
        //TODO handle exception
    }
    title.setFont(titleFont);
    title.setCharacterSize(40);
    title.setFillColor(sf::Color::Red);
    title.setPosition(SCREENWIDTH/2 - 80, 30);
    title.setString("YOSHI RUN");
}

void StateMainMenu::draw(sf::RenderWindow &window) {
    window.draw(sprite);
    window.draw(title);
    window.draw(text);
}

void StateMainMenu::update() {}

void StateMainMenu::changeState(State *nextState) {
    State* tmpState = game->getState();
    game->setState(nextState);
    game->map.reset();
    delete tmpState;
}
