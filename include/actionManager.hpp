#ifndef ACTIONMANAGER_HPP
#define ACTIONMANAGER_HPP

#include <functional>
#include <unordered_map>
#include "action.hpp"

// ����� ����������� �������� � �������������� ��������
class ActionManager
{
public:

	// ��� �������������� �������
	using FuncType = std::function<void(const sf::Event&)>;

	ActionManager();

	bool ProcessEvent();

	void bind(const Action& action, const FuncType& callback);
	void unbind(const Action& action);

private:

	// ������ ������� � ��������� ��������
	std::unordered_map<Action, FuncType> m_callbacks;

};


#endif