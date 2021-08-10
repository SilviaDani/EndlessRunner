//
// Created by user on 10/08/2021.
//

#ifndef ENDLESSRUNNER_ANIMATEDSPRITE_H
#define ENDLESSRUNNER_ANIMATEDSPRITE_H
#include <SFML/Graphics.hpp>

class AnimatedSprite {
public:
    AnimatedSprite() = default;
    AnimatedSprite(sf::Texture &texture, int frameHeight, int frameWidth, int nFrames);
    void draw(sf::RenderWindow &window, int frequency);
    void setPosition(float x, float y);
    sf::Rect<float> getGlobalBounds();
    const sf::Sprite getSprite() const;
    void setScale(float x, float y);
    void move(float x, float y);

    sf::Vector2f getPosition();

    void setOrigin(float x, float y);

    sf::Vector2f getOrigin();

    sf::Rect<float> getLocalBounds();

    sf::Vector2f getScale();

    void setPosition(sf::Vector2f vector2);

private:
    int frames;
    sf::IntRect intRect;
    sf::Sprite sprite;
    sf::Clock clock;
};


#endif //ENDLESSRUNNER_ANIMATEDSPRITE_H
