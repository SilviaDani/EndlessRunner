//
// Created by user on 10/08/2021.
//

#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite(sf::Texture &texture, int frameHeight, int frameWidth, int nFrames) {
    intRect = sf::IntRect(0, 0, frameWidth, frameHeight);
    sprite = sf::Sprite(texture, intRect);
    frames = nFrames -1;
}

void AnimatedSprite::draw(sf::RenderWindow &window, int frequency) {
    if (clock.getElapsedTime().asMilliseconds() >= 1000/frequency){
        if (intRect.left == intRect.width * frames)
            intRect.left = 0;
        else
            intRect.left += intRect.width;
        sprite.setTextureRect(intRect);
        clock.restart();
    }
    window.draw(sprite);
}

void AnimatedSprite::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}

sf::Rect<float> AnimatedSprite::getGlobalBounds() {
    return sprite.getGlobalBounds();
}

const sf::Sprite AnimatedSprite::getSprite() const {
    return sprite;
}

void AnimatedSprite::setScale(float x, float y) {
    sprite.setScale(x, y);
}

void AnimatedSprite::move(float x, float y) {
    sprite.move(x, y);
}

sf::Vector2f AnimatedSprite::getPosition() {
    return sprite.getPosition();
}

void AnimatedSprite::setOrigin(float x, float y) {
    sprite.setOrigin(x, y);
}

sf::Vector2f AnimatedSprite::getOrigin() {
    return sprite.getOrigin();
}

sf::Rect<float> AnimatedSprite::getLocalBounds() {
    return sprite.getLocalBounds();
}

sf::Vector2f AnimatedSprite::getScale() {
    return sprite.getScale();
}

void AnimatedSprite::setPosition(sf::Vector2f vector2) {
    sprite.setPosition(vector2);
}


