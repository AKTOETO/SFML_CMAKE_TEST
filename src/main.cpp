#include <SFML/Graphics.hpp>
#include <memory>

// главная функция
int main()
{
    sf::Texture text;
    text.loadFromFile("assets/textures/src/Player.png");

    sf::Sprite sp(text);
    sp.setPosition(200,200);
    sp.setScale(10,10);

    auto window = sf::RenderWindow{ { 800, 600 }, "CMake SFML Project" };
    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear(sf::Color::Blue);
        window.draw(sp);
        window.display();
    }
}