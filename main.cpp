#include <iostream>
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Game.h"
#include "StateMainMenu.h"
#include "StateGameOver.h"
#include "StateGame.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(SCREENWIDTH,SCREENHEIGHT), "Endless Runner", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(100);
    Game *game= Game::getInstance();
    game->setWindow(&window);
    while (window.isOpen()){
        sf::Event event{};
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space){
                if (GravityInverter* form = dynamic_cast<GravityInverter*>(game->getPlayer().getForm())){
                    form->invertGravity();
                }
            }
            if (State* state = dynamic_cast<StateMainMenu*>(game->getState())){
                if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space)
                    state->changeState(new StateGame(game));
            }
            if (State* state = dynamic_cast<StateGameOver*>(game->getState())) {
                if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space)
                    state->changeState(new StateGame(game));
                if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
                    state->changeState(nullptr);
            }
        }
        window.clear(sf::Color::Blue);
        game->update();
        game->draw(window);
        window.display();
    }
    return 0;
}

