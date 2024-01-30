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

	Action(sf::Event _event);

	// необходимо сравнить тип действия,
	// чтобы знать, когда его выполнять
	bool operator==(const sf::Event& _event) const;

	// оператор проверки выполнения события
	bool operator()()const;

private:

	// тип действия
	sf::Event m_event;

	// сравнение sf::Event
	bool IsEqual(const sf::Event& ev1, const sf::Event& ev2);
};

#endif //ACTION_HPP

inline Action::Action(sf::Event _event)
	:m_event(_event)
{
}

inline bool Action::operator==(const sf::Event& _event) const
{
	// результат сравнения
	bool res = false;

	// проверка вариантов события
	switch (_event.type)
	{
	case sf::Event::EventType::KeyPressed:
	{
		res = IsEqual(m_event, _event);
		break;
	}

	case sf::Event::EventType::KeyReleased:
	{
		res = IsEqual(m_event, _event);
		break;
	}

	case sf::Event::EventType::MouseButtonPressed:
	{
		res = IsEqual(m_event, _event);
		break;		
	}

	case sf::Event::EventType::MouseButtonReleased:
	{
		res = IsEqual(m_event, _event);
		break;
	}

	default:
		break;
	}

	return res;
}

inline bool Action::operator()()const
{
	bool res = false;

	if (m_event.type == sf::Event::EventType::KeyPressed)
		res = sf::Keyboard::isKeyPressed(m_event.key.code);

	else if (m_event.type == sf::Event::EventType::MouseButtonPressed)
		res = sf::Mouse::isButtonPressed(m_event.key.code);

	return res;
}

inline bool Action::IsEqual(const sf::Event& ev1, const sf::Event& ev2)
{
	bool res = false;
	if (m_event.type == _event.type)
		res = _event.key.code == m_event.key.code;
	return res;
}

