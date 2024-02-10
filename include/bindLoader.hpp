#ifndef BINDLOADER_HPP
#define BINDLOADER_HPP

#include <functional>
#include <sstream>
#include <fstream>
#include <spdlog/spdlog.h>

#include "assetLoader.hpp"
#include "action.hpp"

// ���� ������� ��������
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

// ��������� ������
class BindLoader :
	public AssetLoader<Action, BindType::ID>
{
protected:

	virtual void ReadConfig(Action*, const std::string&) override;

	// �������������� �� ���� � ������������
	std::map<std::string, BindType::ID> m_str_to_id;

	// �������������� �� ������ ������� � �������
	std::map<std::string, sf::Keyboard::Key> m_str_to_key;

private:
	// ��������� �������
	void ActionConfigure(Action* action, BindType::ID id, std::stringstream& sstr);

public: 
	BindLoader();

	//virtual void LoadAsset(const std::string& filename, BindType::ID asset_name) override;
};

#endif // BINDLOADER_HPP