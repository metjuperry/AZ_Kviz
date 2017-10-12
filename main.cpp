#include "SFML/Graphics.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Pole.h"
#include "QuestionBox.h"

//Extract questions from .txt and make an array out of them
std::vector<sf::String> getQuestions(const sf::String &path) {
    std::vector<sf::String> targetArray;

    std::string oneQuestion;
    std::ifstream infile;
    infile.open(path);
    while (!infile.eof()) // To get you all the lines.
    {
        getline(infile, oneQuestion); // Saves one question
        targetArray.emplace_back(oneQuestion);
    }
    infile.close();

    return targetArray;
}

Owner switchPlayers(Owner player) {
    return player == PLAYER1 ? PLAYER2 : PLAYER1;
}

int main(int argc, char **argv) {
    sf::RenderWindow renderWindow(sf::VideoMode(800, 600), "Az kviz");
    sf::Vector2u screenSize = renderWindow.getSize();

    sf::Color background(sf::Uint8(160), sf::Uint8(160), sf::Uint8(235));

    sf::Font font;
    font.loadFromFile("OpenSans-Bold.ttf");

    std::vector<sf::String> Otazky = getQuestions("otazky.txt");
    std::vector<Pole> Fields;

    sf::Event event{};

    int numInRow = 1;
    int current = 1;
    int rowSpace = 100;

    Owner CurrentPlayer;
    Pole *QuestionInUse = nullptr;

    sf::Text number("X", font, 30);
    sf::Text otazka("Test", font, 35);
    sf::Text hrac("Hraje hrac cislo ", font, 35);
    sf::Text hracCislo("jedna", font, 35);

    hracCislo.setPosition(0, 40);
    hracCislo.setFillColor(sf::Color::Red);

    otazka.setFillColor(sf::Color::Black);
    otazka.setPosition(80, 150);

    QuestionBox OtazkaBox;

    //Pyramid algorithm
    for (int questions = 0; questions != 6; questions++) {
        // If its the top one
        if (numInRow == 1) {
            Fields.emplace_back(
                    Pole(screenSize.x / 2, rowSpace * questions + 10, current, Otazky[current - 1], numInRow,
                         TOP_CORNER));
            current++;
        } else if (numInRow % 2 != 0) { // if we are on the row with odd fields

            //calculate how many are "off the side"
            int notMid = (numInRow - 1) / 2;

            //print notMid amount of boxes to the left
            for (int left = notMid; left != 0; left--) {
                if (left == notMid) {
                    Fields.emplace_back(
                            Pole(screenSize.x / 2 - 120 * left, rowSpace * questions, current, Otazky[current - 1],
                                 numInRow, LEFT_SIDE));
                } else {
                    Fields.emplace_back(
                            Pole(screenSize.x / 2 - 120 * left, rowSpace * questions, current, Otazky[current - 1],
                                 numInRow, MID));
                }
                current++;
            }
            //print the middle one
            Fields.emplace_back(
                    Pole(screenSize.x / 2, rowSpace * questions, current, Otazky[current - 1], numInRow, MID));
            current++;

            //print notMid amount boxes to the right
            //TODO: Fix that thing, it doesn't work
            for (int right = 0; right != notMid; right++) {
                if (right == 0) {
                    Fields.emplace_back(
                            Pole(screenSize.x / 2 + 120 * (right + 1), rowSpace * questions, current,
                                 Otazky[current - 1],
                                 numInRow, RIGHT_SIDE));
                } else {
                    Fields.emplace_back(
                            Pole(screenSize.x / 2 + 120 * (right + 1), rowSpace * questions, current,
                                 Otazky[current - 1],
                                 numInRow, MID));
                    current++;
                }
                current++;
            }
        } else { // handle the even rows

            // How many are there on each side from mid?
            // For some reason, the closest to middle is only one time, others are 1.5
            int side = numInRow / 2;

            // Print side amount of boxes to the left
            for (int left = side; left != 0; left--) {
                if (left == 1) {
                    if(left == side){
                        Fields.emplace_back(
                                Pole(screenSize.x / 2 - 60 * left, rowSpace * questions, current, Otazky[current - 1],
                                     numInRow, LEFT_SIDE));
                    } else {
                        Fields.emplace_back(
                                Pole(screenSize.x / 2 - 60 * left, rowSpace * questions, current, Otazky[current - 1],
                                     numInRow, MID));
                    }
                } else {
                    if (left == side) {
                        Fields.emplace_back(
                                Pole(screenSize.x / 2 - 60 * left * 1.5f, rowSpace * questions, current,
                                     Otazky[current - 1], numInRow, LEFT_SIDE));
                    } else {
                        Fields.emplace_back(
                                Pole(screenSize.x / 2 - 60 * left * 1.5f, rowSpace * questions, current,
                                     Otazky[current - 1], numInRow, MID));
                    }
                }
                current++;
            }

            for (int right = 0; right != side; right++) {
                if (right == 0) {
                    if (right == side) {
                        Fields.emplace_back(
                                Pole(screenSize.x / 2 + 60 * (right + 1), rowSpace * questions, current,
                                     Otazky[current - 1], numInRow, MID));
                    } else {
                        Fields.emplace_back(
                                Pole(screenSize.x / 2 + 60 * (right + 1), rowSpace * questions, current,
                                     Otazky[current - 1], numInRow, RIGHT_SIDE));
                    }
                } else {
                    if (right == side - 1) {
                        Fields.emplace_back(
                                Pole(screenSize.x / 2 + 60 * (right + 1) * 1.5f, rowSpace * questions, current,
                                     Otazky[current - 1], numInRow, RIGHT_SIDE));
                    } else {
                        Fields.emplace_back(
                                Pole(screenSize.x / 2 + 60 * (right + 1) * 1.5f, rowSpace * questions, current,
                                     Otazky[current - 1], numInRow, MID));
                    }
                }
                current++;
            }
        }
        // Next row has one more
        numInRow++;
    }

    while (renderWindow.isOpen()) {

        //Mouse coords relative to renderWindow
        sf::Vector2i mouseCoords = (sf::Mouse::getPosition(renderWindow));

        // Check for all the events that occured since the last frame.
        while (renderWindow.pollEvent(event)) {
            //Handle events here
            if (event.type == sf::Event::EventType::Closed)
                renderWindow.close();

            else if (event.type == sf::Event::EventType::MouseButtonPressed &&
                     sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (OtazkaBox.getVisible()) {
                    if (OtazkaBox.collision(mouseCoords, true) || (OtazkaBox.collision(mouseCoords, false))) {
                        if (!OtazkaBox.isSpecial()) {
                            if (OtazkaBox.collision(mouseCoords, true)) {
                                QuestionInUse->setOwner(CurrentPlayer);
                            } else if (OtazkaBox.collision(mouseCoords, false)) {
                                QuestionInUse->setOwner(WRONG);
                            }
                        } else {
                            if (OtazkaBox.collision(mouseCoords, true)) {
                                QuestionInUse->setOwner(PLAYER1);
                            } else if (OtazkaBox.collision(mouseCoords, false)) {
                                QuestionInUse->setOwner(PLAYER2);
                            }
                        }
                        OtazkaBox.makeInVisible();
                        CurrentPlayer = switchPlayers(CurrentPlayer);

                        if (CurrentPlayer == PLAYER1) {
                            hracCislo.setString("jedna");
                            hracCislo.setFillColor(sf::Color::Red);
                        } else {
                            hracCislo.setString("dva");
                            hracCislo.setFillColor(sf::Color::Blue);
                        }
                    }
                } else {
                    for (auto &box: Fields) {

                        //Check collisions
                        if (box.collision(mouseCoords) && !OtazkaBox.getVisible() &&
                            (box.getOwner() != PLAYER1 && box.getOwner() != PLAYER2) &&
                            sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                            OtazkaBox.makeVisibile();
                            std::cout << box.getPlacement() << std::endl;
                            if (box.getOwner() == NONE) {
                                OtazkaBox.setSpecial(false);
                                otazka.setString(box.getOtazka());
                            } else if (box.getOwner() == WRONG) {
                                OtazkaBox.setSpecial(true);
                                otazka.setString("Specialni ukol!!");
                            }
                            QuestionInUse = &box;
                        }
                    }
                }
            }
        }

        renderWindow.clear(background);

        // for each loop to iterate through the boxes
        for (auto &box: Fields) {
            //Render boxes themselves
            renderWindow.draw(box.circleShow());

            //Add the numbers
            std::stringstream boxNumber;
            boxNumber << box.getNum();
            number.setString(boxNumber.str());
            if (box.getOwner() != WRONG) {
                number.setFillColor(sf::Color::Black);
            } else {
                number.setFillColor(sf::Color::White);
            }
            number.setPosition(box.getTextCoords());
            renderWindow.draw(number);
        }

        if (OtazkaBox.getVisible()) {
            renderWindow.draw(OtazkaBox.showBox());
            renderWindow.draw(otazka);

            renderWindow.draw(OtazkaBox.showButton(true));
            renderWindow.draw(OtazkaBox.showButton(false));
        }

        renderWindow.draw(hrac);
        renderWindow.draw(hracCislo);
        renderWindow.display();
    }
}