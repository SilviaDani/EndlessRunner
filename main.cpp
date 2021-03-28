#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Map.h"
#include "CONSTANTS.h"
#include "Game.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(SCREENWIDTH,SCREENHEIGHT), "Endless Runner", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(100);

    Game *game= Game::getInstance();

    while(window.isOpen()){
        sf::Event event{};
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }
        window.clear(sf::Color::Blue);
        game->update();
        game->draw(window);
        window.display();

    }
    return 0;
}

