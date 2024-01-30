#include "actionManager.hpp"

ActionManager::ActionManager()
{
}

bool ActionManager::ProcessEvent()
{
	return false;
}

void ActionManager::bind(const Action& action, const FuncType& callback)
{
}

void ActionManager::unbind(const Action& action)
{
}
