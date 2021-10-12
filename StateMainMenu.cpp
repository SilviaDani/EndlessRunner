//
// Created by user on 05/08/2021.
//

#include "StateMainMenu.h"


StateMainMenu::StateMainMenu(Game *gameptr) {
    game = gameptr;
    try {
        if (!texture.loadFromFile("../Sprites/mainMenuBackground.jpg")){
            throw std::runtime_error("File not found: ../Sprites/mainMenuBackground.jpg");
        }
    }
    catch (const std::runtime_error& exc) {
        std::cerr << exc.what() << std::endl;
        exit(-1);
    }
    sprite.setTexture(texture);
    sprite.setPosition(0, 0);
    sprite.setScale(3,3.2);


    try {
        if (!font.loadFromFile("../Fonts/arial.ttf")){
            throw std::runtime_error("File not found: ../Fonts/arial.ttf");
        }
    }
    catch (const std::runtime_error& exc) {
        std::cerr << exc.what() << std::endl;
        exit(-1);
    }
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);
    text.setPosition(SCREENWIDTH/2 - 30, SCREENHEIGHT - 60);
    text.setString("Press SPACE\nto play");


    try {
        if (!titleFont.loadFromFile("../Fonts/pixel.TTF")){
            throw std::runtime_error("File not found: ../Fonts/pixel.TTF");
        }
    }
    catch (const std::runtime_error& exc) {
        std::cerr << exc.what() << std::endl;
        exit(-1);
    }
    title.setFont(titleFont);
    title.setCharacterSize(40);
    title.setFillColor(sf::Color::Red);
    title.setPosition(SCREENWIDTH/2 - 80, 30);
    title.setString("YOSHI RUN");


    try {
        if (!buffer.loadFromFile("../Sounds/mainMenuMusic.wav"))
            throw std::runtime_error("File not found: ../Sounds/mainMenuMusic.wav");
        mainMenuMusic.setBuffer(buffer);
        mainMenuMusic.setLoop(true);
    }
    catch (const std::runtime_error& exc) {
        std::cerr << exc.what() << std::endl;
        exit(-1);
    }

    playMusic();
}

void StateMainMenu::draw(sf::RenderWindow &window) {
    window.draw(sprite);
    window.draw(title);
    window.draw(text);
}

void StateMainMenu::update() {}

void StateMainMenu::changeState(State *nextState) {
    game->load();
    State* tmpState = game->getState();
    game->setState(nextState);
    game->getMap().reset();
    delete tmpState;
}

void StateMainMenu::playMusic() {
    mainMenuMusic.play();
}

void StateMainMenu::stopMusic() {
    mainMenuMusic.stop();
}
