#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "QuestionBox.h"

QuestionBox::QuestionBox() {
    x = 50;
    y = 50;
    w = 700;
    h = 400;
}

//Checks for collisions of the answer buttons
bool QuestionBox::collision(sf::Vector2i mouseCoords, bool left) {
    sf::IntRect inCorrectButtonArea(x + w - 140, y + h - 80, 80, 60);
    sf::IntRect correctButtonArea(x + 60, y + 320, 80, 60);

    if(left){
        if (correctButtonArea.contains(mouseCoords)){
            return true;
        }
    }
    else{
        if(inCorrectButtonArea.contains(mouseCoords)) {
            return true;
        }
    }
    return false;
}

sf::RectangleShape QuestionBox::showBox(){
    sf::RectangleShape box(sf::Vector2f(w,h));
    box.setPosition(x, y);
    return box;
}

sf::RectangleShape QuestionBox::showButton(bool left){
    sf::RectangleShape button(sf::Vector2f(80, 60));
    if(left){
        button.setPosition(x + w -140, y + h - 80);
        if (isSpecial()){
            button.setFillColor(sf::Color::Blue);
        } else {
            button.setFillColor(sf::Color::Red);
        }

    } else {
        button.setPosition(x + 60, y + 320);
        if (isSpecial()){
            button.setFillColor(sf::Color::Red);
        } else {
            button.setFillColor(sf::Color::Green);
        }
    }
    return button;
}

bool QuestionBox::getVisible() {
    return visible;
}

bool QuestionBox::isSpecial() const {
    return special;
}

void QuestionBox::makeVisibile() {
    if(!visible){
        visible = true;
    }
}

void QuestionBox::makeInVisible(){
    if(visible){
        visible = false;
    }
}

void QuestionBox::setSpecial(bool special) {
    QuestionBox::special = special;
}
