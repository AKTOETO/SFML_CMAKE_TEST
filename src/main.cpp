#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#include "textureLoader.hpp"
#include "spriteLoader.hpp"

// главная функция
int main()
{
    //using func = std::function<void(sf::Sprite*)>;
    //std::map<int, func> mp;
    //sf::Sprite sp;
    //mp[0] = std::bind([](sf::Sprite* sp) {sp->move(1, 1); }, &sp);
    //
    //spdlog::info("pos {0}, {1}", sp.getPosition().x, sp.getPosition().y);
    //    
    //mp[0](&sp);
    //
    ////f();
    //spdlog::info("pos {0}, {1}", sp.getPosition().x, sp.getPosition().y);

    TextureLoader tl;
    //tl.LoadAsset("src/Player.png", TextureType::ID::Chel);
    
    SpriteLoader sl(tl);
    sl.LoadAsset("Chel.txt", SpriteInfo::ID::Chel);
    
    //sf::Sprite sp(tl.GetAsset(TextureType::ID::Chel));
    //sp.setPosition(200,200);
    //sp.setScale(10,10);
    
    auto window = sf::RenderWindow{ { 800, 600 }, "CMake SFML Project" };
    window.setFramerateLimit(60);
    window.setPosition({ -1000,50 });
    
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
        window.draw(sl.GetAsset(SpriteInfo::ID::Chel));
        window.display();
    }
}