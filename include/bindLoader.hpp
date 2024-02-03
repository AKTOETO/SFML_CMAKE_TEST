#ifndef BINDLOADER_HPP
#define BINDLOADER_HPP

#include <functional>
#include <strstream>
#include <fstream>
#include <spdlog/spdlog.h>

#include "assetLoader.hpp"
#include "action.hpp"

// типы событий объектов
namespace BindType
{
	enum class ID
	{
		None = 0,
		Player_MoveLeft,
		Player_MoveRight,
		Player_MoveUp,
		Player_MoveDown,

		AllIds
	};
};

// загрузчик клавиш
class BindLoader :
	public AssetLoader<Action, BindType::ID>
{
protected:

	virtual void ReadConfig(Action*, const std::string&) override;

	// преобразование из тега в перечисление
	std::map<std::string, BindType::ID> m_str_to_id;

	// преобразование из строки клавиши в клавишу
	std::map<std::string, sf::Keyboard::Key> m_str_to_key;

private:
	// настройка события
	void ActionConfigure(Action* action, BindType::ID id, std::stringstream& sstr);

public: 
	BindLoader();

	//virtual void LoadAsset(const std::string& filename, BindType::ID asset_name) override;
};

#endif // BINDLOADER_HPP