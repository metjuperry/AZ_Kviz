#ifndef SFMLDEMO_QUESTIONBOX_H
#define SFMLDEMO_QUESTIONBOX_H


#include <SFML/System/String.hpp>
#include <SFML/Graphics/Image.hpp>

class QuestionBox {
public:
    //Constructor
    QuestionBox();

    //Methods
    bool collision(sf::Vector2i mouseCoords, bool left);
    sf::RectangleShape showBox();
    sf::RectangleShape showButton(bool left);

    //Getters
    bool getVisible();
    bool isSpecial() const;

    //Setters
    void makeVisibile();
    void makeInVisible();
    void setSpecial(bool special);

private:
    int x,y,w,h;
    bool visible = false;
    bool special = false;
};


#endif //SFMLDEMO_QUESTIONBOX_H
