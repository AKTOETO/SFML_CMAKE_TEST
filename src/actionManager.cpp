#include "actionManager.hpp"

ActionManager::ActionManager()
{
}

bool ActionManager::ProcessEvent(const sf::Event& _event) const
{
	// выполнилось ли какое-либо событие
	bool res = false;

	for (auto& action : m_poll_events)
	{
		// если произошло событие, которое нужно обработать
		if (action.first == _event)
		{
			action.second(_event);
			res = 1;
			break;
		}
	}

	return res;
}

void ActionManager::ProcessEvent() const
{
	// проверка выполнения всех событий,
	// получаемых с устройств напрямую
	for (auto& action : m_real_time_events)
	{
		// если событие произошло
		if (action.first())
		{
			// вызываем функцию-обработчик этого события
			action.second(action.first.m_event);
		}
	}
}

void ActionManager::bind(const Action& action, const FuncType& callback)
{
	// если действие получается напрямую с устройства
	if (action.m_type == Action::Type::RealTime)
		// кладем его в один мап
		m_real_time_events.emplace_back(action, callback);
	
	// если действие получается из функции pollEvent
	else
		// кладем его в другой мап
		m_poll_events.emplace_back(action, callback);

}

void ActionManager::unbind(const Action& action)
{
	auto remover = [&action](const std::pair<Action, FuncType>& data)
		{
			return action == data.first;
		};

	// если действие получается напрямую с устройства
	if (action.m_type == Action::Type::RealTime)
		std::erase_if(m_real_time_events, remover);
		
	// если действие получается из функции pollEvent
	else
		std::erase_if(m_poll_events, remover);
}
