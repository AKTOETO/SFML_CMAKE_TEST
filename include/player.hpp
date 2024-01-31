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

	// ����� ��������� �������
	void ProcessEvent();
	
	// ����� ��������� ���������
	void ProcessUpdate(const sf::Time& d_time);

protected:

	// �������� �� ���
	bool m_is_mooving;

	// ������ ��������
	sf::Vector2f m_dir;

	// �������� ������
	float m_speed;

	// ������ ������
	sf::Sprite& m_sprite;

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};


#endif // PLAYER_HPP