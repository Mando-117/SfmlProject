#include <SFML/Window.hpp>

int main()
{
    sf::Window window(sf::VideoMode({800,800}), "SFML Window");

    // change the position of the window (relatively to the desktop)
    window.setPosition({1000, 400});

    // change window size
    //window.setSize({800, 800});

    // get the size of the window
    sf::Vector2u size = window.getSize();
    auto [width, height] = size;

    // change the title
    window.setTitle("First Game");

    // see if window has focus
    //bool focus = window.hasFocus();


    while (window.isOpen())
    {
        bool focus = window.hasFocus();

        if (focus)
            window.setTitle("This is a focused window");
        else
            window.setTitle("This is a unfocused window");

        while (const std::optional event = window.pollEvent())
        {
            bool focus = window.hasFocus();
            if (event->is<sf::Event::Closed>())
                window.close();
        }
    }

    window.setFramerateLimit(60);
}