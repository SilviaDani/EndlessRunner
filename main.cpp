#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(800,600), "Jetpack", sf::Style::Titlebar | sf::Style::Close);
    while(window.isOpen()){
        sf::Event event{};
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }
       window.clear(sf::Color::Red);

        //window.draw(sprite1);
        // uno per ciascuna sprite
        // se lo scrivo prima lo vedo sotto (contrario dei layer)
        window.display();
    }
    return 0;
}
