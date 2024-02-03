#include "bindLoader.hpp"

BindLoader::BindLoader()
	:AssetLoader("binds/")
{
#define STR(x)#x
#define ADD_STR_ID(str) m_str_to_id[STR(str)] = BindType::ID::str;

	// добавляем типы событий

	/*
	Player_MoveLeft A
	Player_MoveRight D
	Player_MoveUp W
	Player_MoveDown S
	*/

	ADD_STR_ID(Player_MoveLeft);
	//m_str_to_id["Player_MoveLeft"] = BindType::ID::Player_MoveLeft;
	ADD_STR_ID(Player_MoveRight);
	ADD_STR_ID(Player_MoveUp);
	ADD_STR_ID(Player_MoveDown);

	// добавляем кнопки
#define ADD_STR_KEY(str) m_str_to_key[STR(str)] = sf::Keyboard::Key::str;
	//m_str_to_key["A"] = sf::Keyboard::Key::A;
	ADD_STR_KEY(A);
	ADD_STR_KEY(W);
	ADD_STR_KEY(S);
	ADD_STR_KEY(D);


#undef ADD_STR_KEY
#undef ADD_STR_ID
#undef STR
}

void BindLoader::ReadConfig(Action* action, const std::string& filename)
{
	// открываем файл с конфигом спрайта
	std::ifstream fin(m_FilePath + filename);
	if (!fin)
		spdlog::info("Failed to open {0} file", m_FilePath + filename);

	std::string temp;
	// читаем конфиг
	while (std::getline(fin, temp))
	{
		// тег с параметрами в строковом потоке
		std::stringstream sstr(temp);

		// формат команды:
		// <tag> <value>

		// тег
		std::string tag;
		sstr >> tag;

		// если строка не пустая и
		// первый символ # то это комментарий
		if (tag.length() > 0 && tag[0] != '#')
		{
			// если такой тег не существует
			if (m_str_to_id.find(tag) == m_str_to_id.end())
			{
				spdlog::error("Tag '{0}' doesnt exist!", tag);
				throw std::runtime_error("[SpriteLoader::ReadConfig] Failed to find '" + tag + "'!");
			}

			// активация функции обработки соответствующего тега
			//m_tag_to_func[m_str_to_tags[tag]](sp, sstr);
			// настройка события
			ActionConfigure(action, m_str_to_id[tag], sstr);

		}
	}
}

void BindLoader::ActionConfigure(Action* action, BindType::ID id, std::stringstream& sstr)
{
	// получение кнопки
	std::string temp;
	sstr >> temp;

	auto it = m_str_to_key.find(temp);

	// пытаемся найти кнопку в списке доступных кнопок
	if (it == m_str_to_key.end())
	{
		spdlog::error("BindLoader::ActionConfigure incorrect button '{0}'", temp);
		throw std::runtime_error("BindLoader::ActionConfigure incorrect button");
	}

	action->SetKeyboardAction(it->second);

	//action->SetKeyboardAction()
}

