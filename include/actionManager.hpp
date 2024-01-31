#ifndef ACTIONMANAGER_HPP
#define ACTIONMANAGER_HPP

#include <algorithm>
#include <functional>
#include <list>
#include "action.hpp"

// ����� ����������� �������� � �������������� ��������
class ActionManager
{
public:

	// ��� �������������� �������
	using FuncType = std::function<void(const sf::Event&)>;

	ActionManager();

	// ��� �������, ���������� � pollEvent
	bool ProcessEvent(const sf::Event&) const;
	// ��� ������� ���������� ������� � ���������
	void ProcessEvent() const;

	void bind(const Action& action, const FuncType& callback);
	void unbind(const Action& action);

private:

	// ������ �������, ���������� 
	// ������� ����� ��������� � ����� �����
	std::list<std::pair<Action, FuncType>> m_real_time_events;

	// ������ ��������� �������
	std::list<std::pair<Action, FuncType>> m_poll_events;

};


#endif