#include "game.hpp"

Game::Game()
	:m_window({ 800, 600 }, "CMake SFML Project"),
	m_min_fps(30), m_fps(0), m_clock(), m_time_since_last_update(), m_time_per_frame(),
	m_texture_loader(std::make_unique<TextureLoader>()),
	m_sprite_loader(std::make_unique<SpriteLoader>(*m_texture_loader))
{
	m_window.setFramerateLimit(60);

#ifndef NDEBUG
	m_window.setPosition({ -1000,50 });
#endif // !NDEBUG



	// loading assets
	m_texture_loader->LoadAsset("Player.png", TextureType::ID::Chel);
	m_sprite_loader->LoadAsset("Chel.txt", SpriteInfo::ID::Chel);

	// создаем игрока
	m_player = std::make_unique<Player>(m_sprite_loader->GetAsset(SpriteInfo::ID::Chel));
}

void Game::Run()
{
	m_time_per_frame = sf::seconds(1.f / m_min_fps);

	while (m_window.isOpen())
	{
		ProcessEvent();
		m_time_since_last_update = m_clock.restart();

		while (m_time_since_last_update > m_time_per_frame)
		{
			m_time_since_last_update -= m_time_per_frame;
			ProcessUpdate(m_time_per_frame);
		}

		ProcessUpdate(m_time_since_last_update);
		ProcessRender();
	}
}

void Game::ProcessEvent()
{
	for (auto event = sf::Event{}; m_window.pollEvent(event);)
	{
		// Close event
		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}
		// Keyboard event
		else if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
				m_window.close();
		}

	}
	// обработка событий игрока
	m_player->ProcessEvent();
}

void Game::ProcessUpdate(const sf::Time& d_time)
{
	m_fps = int(1 / d_time.asSeconds());
	m_window.setTitle(std::to_string(m_fps) + "  "+
		std::to_string(m_time_per_frame.asSeconds())+ " "+
		std::to_string(m_time_since_last_update.asSeconds()));

	// обновление игрока
	m_player->ProcessUpdate(d_time);
}

void Game::ProcessRender()
{
	m_window.clear(sf::Color::Blue);
	
	m_window.draw(*m_player);

	m_window.display();
}
