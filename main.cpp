#include <SFML/Window.hpp>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>

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
    std::string fileWord;

    sf::Font font;
    float fontSize , fontRVal, fontGVal, fontBVal;

    unsigned int windowX = 0, windowY= 0;

    std::vector<codedShape> allShapes;
    std::vector<sf::RectangleShape> rectShapes;
    std::vector<sf::CircleShape> circleShapes;


    fileIn.open("../config.txt");
    if (!fileIn.is_open())
    {
        std::cerr << "Error opening file" << std::endl;
    }
    while (fileIn >> fileWord)
    {
        if (fileWord == "Window")
        {
            fileIn >> windowX >> windowY;
        }
        if (fileWord == "Font")
        {
            std::string fontLoc, fontFormat;
            fileIn >> fontLoc;;
            fontFormat = "../"+ fontLoc;

            std::cout<<fontFormat;
            if (!font.openFromFile(fontFormat))
            {
                std::cout<<"Error opening file"<<std::endl;
                return -1;
            }

            fileIn >> fontSize >> fontRVal >> fontGVal >> fontBVal;

        }
        if (fileWord == "Circle")
        {
            std::string shapeType = fileWord;
            std::string cName;

            float cPosX, cPosY, cVelX, cVelY, cRVal, cGVal, cBVal, cRadius;

            fileIn >> cName >> cPosX >> cPosY >> cVelX >> cVelY >> cRVal >> cGVal >> cBVal >> cRadius;

            sf::Text circleText(font);

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
    }



        sf::RenderWindow window(sf::VideoMode({windowX, windowY}), "First Sfml Project");

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


            // draw everything here
            for (auto& shapeToDraw : allShapes)
            {
                if (shapeToDraw.shapeType== "Rectangle")
                {
                    sf::Text rectText(font);
                    rectText.setCharacterSize(fontSize);
                    rectText.setString(shapeToDraw.shapeName);
                    rectText.setFillColor(sf::Color(fontRVal,fontGVal,fontBVal));

                    sf::FloatRect textBounds = rectText.getLocalBounds();
                    rectText.setOrigin(sf::Vector2f(textBounds.position.x + textBounds.size.x / 2.f,
                                                        textBounds.position.y + textBounds.size.y / 2.f));
                    rectText.setPosition(sf::Vector2f(shapeToDraw.rect.getPosition().x + shapeToDraw.rect.getSize().x/2.f,
                                                        shapeToDraw.rect.getPosition().y + shapeToDraw.rect.getSize().y/2.f));

                    window.draw(shapeToDraw.rect);
                    window.draw(rectText);

                    sf::FloatRect bounceBounds = shapeToDraw.rect.getGlobalBounds();

                    if (bounceBounds.position.y + bounceBounds.size.y > windowY || bounceBounds.position.y < 0)
                    {
                        shapeToDraw.velocityY *= -1;
                    }
                    if (bounceBounds.position.x + bounceBounds.size.x > windowX || bounceBounds.position.x < 0)
                    {
                        shapeToDraw.velocityX *= -1;
                    }

                    shapeToDraw.rect.move(sf::Vector2f(shapeToDraw.getVelocityX(), shapeToDraw.getVelocityY()));
                }
                else if (shapeToDraw.shapeType == "Circle") {
                    sf::Text circleText(font);
                    circleText.setCharacterSize(fontSize);
                    circleText.setString(shapeToDraw.shapeName);
                    circleText.setFillColor(sf::Color(fontRVal,fontGVal,fontBVal));

                    sf::FloatRect textBounds = circleText.getLocalBounds();
                    circleText.setOrigin(sf::Vector2f(textBounds.position.x + textBounds.size.x / 2.f,
                                                        textBounds.position.y + textBounds.size.y/2.f));

                    circleText.setPosition(sf::Vector2f(shapeToDraw.circle.getPosition().x + shapeToDraw.circle.getRadius(),
                                            shapeToDraw.circle.getPosition().y + shapeToDraw.circle.getRadius()));

                    window.draw(shapeToDraw.circle);
                    window.draw(circleText);

                    sf::FloatRect bounceBounds = shapeToDraw.circle.getGlobalBounds();


                    if (bounceBounds.position.y + bounceBounds.size.y > windowY|| bounceBounds.position.y < 0)
                    {
                        shapeToDraw.velocityY *= -1;
                    }
                    if (bounceBounds.position.x + bounceBounds.size.x > windowX || bounceBounds.position.x < 0)
                    {
                        shapeToDraw.velocityX *= -1;
                    }

                    shapeToDraw.circle.move(sf::Vector2f(shapeToDraw.getVelocityX(), shapeToDraw.getVelocityY()));

                }
            }

            window.display();
        }

        std::cout<<(sizeof(allShapes))<<std::endl;
        fileIn.close();
}