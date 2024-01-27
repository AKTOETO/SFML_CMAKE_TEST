#include <SFML/Graphics.hpp>
#include <memory>
#include "textureLoader.hpp"

// главная функция
int main()
{
    TextureLoader tl;
    tl.LoadAsset("src/Player.png", TextureType::ID::Chel);

    sf::Sprite sp(tl.GetAsset(TextureType::ID::Chel));
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