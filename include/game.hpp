#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>

#include "textureLoader.hpp"
#include "spriteLoader.hpp"
// класс игры
class Game : public sf::NonCopyable
{
public:
	Game();
	void Run();

private:
	void ProcessEvent();
	void ProcessUpdate(const sf::Time & d_time);
	void ProcessRender();

	sf::RenderWindow m_window;
	float m_min_fps;

	// asset loaders
	std::unique_ptr<TextureLoader> m_texture_loader;
	std::unique_ptr<SpriteLoader> m_sprite_loader;

	// time managing
	sf::Clock m_clock;
	sf::Time m_time_since_last_update;
	sf::Time m_time_per_frame;
	int m_fps;
};


#endif //GAME_HPP
