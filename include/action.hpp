#ifndef ACTION_HPP
#define ACTION_HPP

#include <SFML/Graphics.hpp>

class Action
{
public:

	enum class Type
	{
		None = 0,
		RealTime = 1,
	};

	Action(sf::Event _event, Type type = Type::RealTime);

	// ������������ ��� ��������� ���������� � ����
	Action(const sf::Keyboard::Key& key, Type type = Type::RealTime);
	Action(const sf::Mouse::Button& key, Type type = Type::RealTime);

	// ���������� �������� ��� ��������,
	// ����� �����, ����� ��� ���������
	bool operator==(const sf::Event& _event) const;
	bool operator==(const Action& _action) const;

	// �������� �������� ���������� �������
	bool operator()()const;

private:

	// ��� ������� � ��������� ����� ����� ������ 
	// �� ������ ActionManager
	friend class ActionManager;

	// ��� ��������
	sf::Event m_event;

	// ��� �������
	Type m_type;
};

#endif //ACTION_HPP

inline Action::Action(sf::Event _event, Type type)
	:m_event(_event), m_type(type)
{}

inline Action::Action(const sf::Keyboard::Key& key, Type type)
	:m_type(type)
{
	m_event.type = sf::Event::EventType::KeyPressed;
	m_event.key.code = key;
}

inline Action::Action(const sf::Mouse::Button& key, Type type)
	:m_type(type)
{
	m_event.type = sf::Event::EventType::MouseButtonPressed;
	m_event.mouseButton.button = key;
}

inline bool Action::operator==(const sf::Event& _event) const
{
	// ��������� ���������
	bool res = false;

	// �������� ��������� �������
	switch (_event.type)
	{
	case sf::Event::EventType::KeyPressed:
	{
		if (m_event.type == _event.type)
			res = _event.key.code == m_event.key.code;
		break;
	}

	case sf::Event::EventType::KeyReleased:
	{
		if (m_event.type == _event.type)
			res = _event.key.code == m_event.key.code;
		break;
	}

	case sf::Event::EventType::MouseButtonPressed:
	{
		if (m_event.type == _event.type)
			res = _event.key.code == m_event.key.code;
		break;
	}

	case sf::Event::EventType::MouseButtonReleased:
	{
		if (m_event.type == _event.type)
			res = _event.key.code == m_event.key.code;
		break;
	}

	default:
		break;
	}

	return res;
}

inline bool Action::operator==(const Action& _action) const
{
	return m_event == _action && m_type == _action.m_type;
}

inline bool Action::operator()()const
{
	bool res = false;

	if (m_event.type == sf::Event::EventType::KeyPressed)
		res = sf::Keyboard::isKeyPressed(m_event.key.code);

	else if (m_event.type == sf::Event::EventType::MouseButtonPressed)
		res = sf::Mouse::isButtonPressed(m_event.mouseButton.button);

	return res;
}

