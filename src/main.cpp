#include<stdio.h>

#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>

#include<entt/entt.hpp>

struct Position {
    float x;
    float y;
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 360), "My window");
    // If key repeat is not disabled, then the key will repeat at a frequency determined by the OS,
    // which is not practical for this code to predict.
    window.setKeyRepeatEnabled(false);
    auto main_registry{ entt::registry{} };

    auto player_entity = main_registry.create();
    main_registry.assign<Position>(player_entity);

    sf::RectangleShape rectangle(sf::Vector2(80.f, 50.f));
    rectangle.setPosition(10.5, 50.f);
    rectangle.setFillColor(sf::Color::Red);

    bool quit{ false };
    while (!quit)
    {

        // check all the window's events that were triggered since the loop's last iteration
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                quit = true;
            }
        }

        window.clear(sf::Color::Black);

        window.draw(rectangle);

        window.display();
    }

    return 0;
}