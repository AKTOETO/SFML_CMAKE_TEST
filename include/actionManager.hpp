#ifndef ACTIONMANAGER_HPP
#define ACTIONMANAGER_HPP

#include <algorithm>
#include <functional>
#include <list>
#include "action.hpp"

// класс связывающий действие с обрабатывающей функцией
class ActionManager
{
public:

	// тип обрабатывающей функции
	using FuncType = std::function<void(const sf::Event&)>;

	ActionManager();

	// для событий, получаемых с pollEvent
	bool ProcessEvent(const sf::Event&) const;
	// для событий получаемых напряму с устройств
	void ProcessEvent() const;

	void bind(const Action& action, const FuncType& callback);
	void unbind(const Action& action);

private:

	// список событий, выполнение 
	// которых можно проверить в любое время
	std::list<std::pair<Action, FuncType>> m_real_time_events;

	// список остальных событий
	std::list<std::pair<Action, FuncType>> m_poll_events;

};


#endif