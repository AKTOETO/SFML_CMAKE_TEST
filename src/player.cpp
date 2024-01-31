#include "player.hpp"

Player::Player(sf::Sprite& sprite)
	: m_dir(0.,0.), m_speed(10), m_is_mooving(0), m_sprite(sprite)
{
	// при нажатии на D чел двигается направо
	bind(Action(sf::Keyboard::Key::D), [this](const sf::Event&)
		{
			m_is_mooving = 1;
			m_dir = { 1.,0. };
		});

	// при нажатии на A чел двигается налево
	bind(Action(sf::Keyboard::Key::A), [this](const sf::Event&)
		{
			m_is_mooving = 1;
			m_dir = { -1.,0. };
		});

	// при нажатии на W чел двигается вверх
	bind(Action(sf::Keyboard::Key::W), [this](const sf::Event&)
		{
			m_is_mooving = 1;
			m_dir = { 0.,-1. };
		});

	// при нажатии на S чел двигается вниз
	bind(Action(sf::Keyboard::Key::S), [this](const sf::Event&)
		{
			m_is_mooving = 1;
			m_dir = { 0.,1. };
		});

	// при нажатии на F1 скорость увеличивается
	bind(Action(sf::Keyboard::Key::F1), [this](const sf::Event&)
		{
			if(m_speed + 3 < 100)
				m_speed += 3;
		});

	// при нажатии на F2 скорость уменьшается
	bind(Action(sf::Keyboard::Key::F2), [this](const sf::Event&)
		{
			if(m_speed - 3 > 0)
				m_speed -= 3;
		});
}

void Player::ProcessEvent()
{
	m_is_mooving = 0;
	m_dir = { 0.,0. };
	ActionManager::ProcessEvent();
}

void Player::ProcessUpdate(const sf::Time& d_time)
{
	float sec = d_time.asSeconds();
	if (m_is_mooving)
	{
		m_sprite.move(m_dir * m_speed);
	}
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_sprite, states);
}
