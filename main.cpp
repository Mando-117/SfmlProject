#include <SFML/Window.hpp>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include "EntityShapes.h"

struct codedShape
{
    sf::CircleShape circle;
    sf::RectangleShape rect;
    std::string shapeName, shapeType;
    float velocityX, velocityY;

    float getVelocityX() { return velocityX; }
    float getVelocityY() { return velocityY; }
};

int main()
{
    std::fstream fileIn;
    std::string font;
    std::string fileWord;

    unsigned int windowX = 0, windowY= 0;

    std::vector<codedShape> allShapes;
    std::vector<sf::RectangleShape> rectShapes;
    std::vector<sf::CircleShape> circleShapes;


    fileIn.open("config.txt");
    if (!fileIn.is_open())
    {
        std::cerr << "Error opening file" << std::endl;
    }
    while (fileIn >> fileWord) {
        if (fileWord == "Window")
        {
            fileIn >> windowX >> windowY;
        }
        if (fileWord == "Font")
        {
            font = fileWord;
        }
        if (fileWord == "Rectangle")
        {
            std::string shapeType = fileWord;
            std::string rName;
            float rPosX, rPosY, rVelX, rVelY, rRVal, rGVal, rBVal, rWidth, rHeight;

            fileIn >> rName >> rPosX >> rPosY >> rVelX >> rVelY >> rRVal >> rGVal >> rBVal >> rWidth >> rHeight;

            sf::RectangleShape rectangle(sf::Vector2f(rWidth,rHeight));
            rectangle.setPosition(sf::Vector2f(rPosX,rPosY));
            rectangle.setFillColor(sf::Color(rRVal,rGVal,rBVal));
            rectShapes.push_back(rectangle);

            struct codedShape newRectangle;
            newRectangle.shapeType = shapeType;
            newRectangle.rect = rectangle;
            newRectangle.shapeName = rName;
            newRectangle.velocityX = rVelX;
            newRectangle.velocityY = rVelY;
            allShapes.push_back(newRectangle);

        }
        if (fileWord == "Circle")
        {
            std::string shapeType = fileWord;
            std::string cName;
            float cPosX, cPosY, cVelX, cVelY, cRVal, cGVal, cBVal, cRadius;

            fileIn >> cName >> cPosX >> cPosY >> cVelX >> cVelY >> cRVal >> cGVal >> cBVal >> cRadius;


            sf::CircleShape circle(cRadius);
            circle.setPosition(sf::Vector2f(cPosX,cPosY));
            circle.setFillColor(sf::Color(cRVal,cGVal,cBVal));
            circleShapes.push_back(circle);

            struct codedShape newCircle;
            newCircle.shapeType = shapeType;
            newCircle.circle = circle;
            newCircle.shapeName = cName;
            newCircle.velocityX = cVelX;
            newCircle.velocityY = cVelY;
            allShapes.push_back(newCircle);
        }
    }



        sf::RenderWindow window(sf::VideoMode({windowX, windowY}), "First Game");

        window.setFramerateLimit(60);

        // run the program as long as the window is open
        while (window.isOpen())
        {
            // check all the window's events that were triggered since the last iteration of the loop
            while (const std::optional event = window.pollEvent())
            {
                // "close requested" event: we close the window
                if (event->is<sf::Event::Closed>())
                    window.close();
            }

            // clear the window with black color
            window.clear(sf::Color::Black);


            // draw everything here...
            for (auto& shapeToDraw : allShapes)
            {
                if (shapeToDraw.shapeType== "Rectangle")
                {
                    window.draw(shapeToDraw.rect);
                    //shapeToDraw.rect.setPosition(sf::Vector2f(shapeToDraw.rect.getPosition().x + shapeToDraw.getVelocityX(), shapeToDraw.rect.getPosition().y + shapeToDraw.getVelocityY()));
                    shapeToDraw.rect.move(sf::Vector2f(shapeToDraw.getVelocityX(), shapeToDraw.getVelocityY()));
                }
                else if (shapeToDraw.shapeType == "Circle")
                {
                    window.draw(shapeToDraw.circle);
                    //shapeToDraw.circle.setPosition(sf::Vector2f(shapeToDraw.circle.getPosition().x + shapeToDraw.getVelocityX(), shapeToDraw.circle.getPosition().y + shapeToDraw.getVelocityY()));
                }

            }

            // end the current frame
            window.display();
        }

        std::cout<<(sizeof(allShapes))<<std::endl;
        fileIn.close();
}