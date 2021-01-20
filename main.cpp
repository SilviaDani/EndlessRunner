#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Yoshi.h"
#include "Map.h"
#include "CONSTANTS.h"
int main() {
    sf::RenderWindow window(sf::VideoMode(SCREENWIDTH,SCREENHEIGHT), "Endless Runner", sf::Style::Titlebar | sf::Style::Close);
    Yoshi player;
    Map map;
    while(window.isOpen()){
        sf::Event event{};
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }
        player.move();
        map.checkCollisions(player);
        map.moveBackground();
        map.moveLand();
        map.moveGrass();
        window.clear(sf::Color::Blue);
        map.draw(window);
        player.draw(window);
        //player.printPosition();

        window.display();

    }
    return 0;
}
