#include <SFML/Graphics/RectangleShape.hpp>
#include "Pole.h"

Pole::Pole(float _x, float _y, int _num,sf::String _otazka) {
    x = _x - w/2;
    y = _y;
    num = _num;
    otazka = _otazka;
}

Pole::Pole(float _x, float _y, int _num, sf::String _otazka, int _myRow, Placement _position) {
    x = _x - w/2;
    y = _y;
    num = _num;
    otazka = _otazka;

    myRow = _myRow;
    position = _position;
}

sf::RectangleShape Pole::show() {
    sf::RectangleShape box(sf::Vector2f(w,h));
    box.setPosition(x, y);
    switch (owner){
        case PLAYER1:
            box.setFillColor(sf::Color::Red);
            break;
        case PLAYER2:
            box.setFillColor(sf::Color::Blue);
            break;
        case WRONG:
            box.setFillColor(sf::Color::Black);
            break;
        case NONE:
            box.setFillColor(sf::Color::White);
            break;
    }

    return box;
}

sf::CircleShape Pole::circleShow() {
    sf::CircleShape Octagon(40, 8);
    Octagon.setPosition(x, y);
    switch (owner){
        case PLAYER1:
            Octagon.setFillColor(sf::Color::Red);
            break;
        case PLAYER2:
            Octagon.setFillColor(sf::Color::Blue);
            break;
        case WRONG:
            Octagon.setFillColor(sf::Color::Black);
            break;
        case NONE:
            Octagon.setFillColor(sf::Color::White);
            break;
    }

    return Octagon;
}

bool Pole::collision(sf::Vector2i mouseCoords) {
    sf::IntRect colisionArea(static_cast<int>(x), static_cast<int>(y), w, h);
    return colisionArea.contains(mouseCoords);
}


void Pole::setOwner(Owner newPlayer){
    owner = newPlayer;
}

Owner Pole::getOwner() const {
    return owner;
}

const sf::String &Pole::getOtazka() const {
    return otazka;
}

int Pole::getNum() const{
    return num;
}

sf::Vector2f Pole::getTextCoords() {
    return {x + w * 1/2, y + (h * 1/3)};
}

Placement Pole::getPlacement() {
    return position;
}

int Pole::getRow() {
    return myRow;
}
