#ifndef SFMLDEMO_POLE_H
#define SFMLDEMO_POLE_H


#include "SFML/Graphics.hpp"

enum Owner {PLAYER1, PLAYER2, WRONG, NONE};
enum Placement {MID, LEFT_SIDE, RIGHT_SIDE, BOTTOM_SIDE, CORNER, TOP_CORNER, LEFT_CORNER, RIGHT_CORNER};

class Pole {
public:
    //Constructor
    Pole(float _x, float _y, int _num,sf::String _otazka);
    Pole(float _x, float _y, int _num,sf::String _otazka, int _myRow, Placement _position);

    //Methods
    sf::RectangleShape show();
    sf::CircleShape circleShow();
    bool collision(sf::Vector2i mouseCoords);

    //Setters
    void setOwner(Owner newPlayer);

    //Getters
    Placement getPlacement();
    int getRow();
    Owner getOwner() const;
    const sf::String &getOtazka() const;
    int getNum() const;
    sf::Vector2f getTextCoords();

private:
    float x;
    float y;

    int w = 60;
    int h = 60;

    int num;
    int myRow;
    sf::String otazka;

    Placement position;
    Owner owner = NONE;
};


#endif //SFMLDEMO_POLE_H
