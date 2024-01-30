#ifndef ACTIONMANAGER_HPP
#define ACTIONMANAGER_HPP

#include <functional>
#include <unordered_map>
#include "action.hpp"

// класс связывающий действие с обрабатывающей функцией
class ActionManager
{
public:

	// тип обрабатывающей функции
	using FuncType = std::function<void(const sf::Event&)>;

	ActionManager();

	bool ProcessEvent();

	void bind(const Action& action, const FuncType& callback);
	void unbind(const Action& action);

private:

	// список функций и возможных действий
	std::unordered_map<Action, FuncType> m_callbacks;

};


#endif