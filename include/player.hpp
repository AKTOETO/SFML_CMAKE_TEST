#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "actionManager.hpp"
#include <spdlog/spdlog.h>

class Player :
	public ActionManager,
	public sf::Drawable,
	public sf::NonCopyable
{
public:
	
	Player(sf::Sprite& sprite);

	// метод обработки событий
	void ProcessEvent();
	
	// метод обработки состояния
	void ProcessUpdate(const sf::Time& d_time);

protected:

	// движется ли чел
	bool m_is_mooving;

	// вектор движения
	sf::Vector2f m_dir;

	// скорость игрока
	float m_speed;

	// спрайт игрока
	sf::Sprite& m_sprite;

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};


#endif // PLAYER_HPP