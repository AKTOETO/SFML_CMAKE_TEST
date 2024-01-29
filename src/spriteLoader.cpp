#include "spriteLoader.hpp"

SpriteLoader::SpriteLoader(TextureLoader& txt_loader)
	:AssetLoader("sprites/"), m_txt_loader(txt_loader)
{
	/*
		SetTexture,
        SetTextureRect
        SetColor
        SetPosition
        SetRotation
        SetScale
        SetOrigin
	*/

	// сопоставление строк из файла тегам
	m_str_to_tags["SetTexture"]	    = SpriteInfo::ConfigTag::SetTexture;
	m_str_to_tags["SetTextureRect"] = SpriteInfo::ConfigTag::SetTextureRect;
	m_str_to_tags["SetColor"]       = SpriteInfo::ConfigTag::SetColor;
	m_str_to_tags["SetPosition"]    = SpriteInfo::ConfigTag::SetPosition;
	m_str_to_tags["SetRotation"]    = SpriteInfo::ConfigTag::SetRotation;
	m_str_to_tags["SetScale"]       = SpriteInfo::ConfigTag::SetScale;
	m_str_to_tags["SetOrigin"]      = SpriteInfo::ConfigTag::SetOrigin;

	/*
		SpriteInfo::ConfigTag::SetTexture
		SpriteInfo::ConfigTag::SetTextureRect
		SpriteInfo::ConfigTag::SetColor
		SpriteInfo::ConfigTag::SetPosition
		SpriteInfo::ConfigTag::SetRotation
		SpriteInfo::ConfigTag::SetScale
		SpriteInfo::ConfigTag::SetOrigin
	*/

#define LAMBDA_F(f_name) [&](sf::Sprite* sp, std::stringstream& str)\
								{ SpriteLoader::f_name(sp, str); };

	// сопоставление тегов функциям обработки
	m_tag_to_func[SpriteInfo::ConfigTag::SetTexture]     = LAMBDA_F(SetTexture);
	m_tag_to_func[SpriteInfo::ConfigTag::SetTextureRect] = LAMBDA_F(SetTextureRect);
	m_tag_to_func[SpriteInfo::ConfigTag::SetColor]       = LAMBDA_F(SetColor);
	m_tag_to_func[SpriteInfo::ConfigTag::SetPosition]    = LAMBDA_F(SetPosition);
	m_tag_to_func[SpriteInfo::ConfigTag::SetRotation]    = LAMBDA_F(SetRotation);
	m_tag_to_func[SpriteInfo::ConfigTag::SetScale]       = LAMBDA_F(SetScale);
	m_tag_to_func[SpriteInfo::ConfigTag::SetOrigin]      = LAMBDA_F(SetOrigin);

#undef LAMBDA_F
}


inline void SpriteLoader::LoadAsset(
	const std::string& filename,
	SpriteInfo::ID asset_name
)
{
	// новый спрайт
	std::unique_ptr<sf::Sprite> sprite = std::make_unique<sf::Sprite>();

	//  чтение конфига 
	ReadConfig(sprite.get(), filename);

	// добавляем элемент в мап
	auto inserted = m_LoadedAssets.insert(
		std::make_pair(asset_name, std::move(sprite))
	);

	assert(inserted.second);
};


void SpriteLoader::ReadConfig(sf::Sprite* sp, const std::string& filename)
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

		// если такой тег не существует
		if (m_str_to_tags.find(tag) == m_str_to_tags.end())
		{
			spdlog::error("Tag '{0}' doesnt exist!", tag);
			throw std::runtime_error("[SpriteLoader::ReadConfig] Failed to find '" + tag + "'!");
		}

		// активация функции обработки соответствующего тега
		m_tag_to_func[m_str_to_tags[tag]](sp, sstr);
	}
}

// функции обработки тегов
void SpriteLoader::SetTexture(sf::Sprite* sp, std::stringstream& str)
{
	std::string filepath;
	str >> filepath;
	spdlog::info("Texture filename: {0}", filepath);

	m_txt_loader.LoadAsset(filepath, TextureType::ID::Chel);
	sp->setTexture(m_txt_loader.GetAsset(TextureType::ID::Chel));
}
void SpriteLoader::SetTextureRect(sf::Sprite* sp, std::stringstream& str)
{
	spdlog::info("SetTextureRect set");
}
void SpriteLoader::SetColor(sf::Sprite* sp, std::stringstream& str)
{
	spdlog::info("SetColor set");
}
void SpriteLoader::SetPosition(sf::Sprite* sp, std::stringstream& str)
{
	float x,y;
	str >> x >> y;
	sp->setPosition(x, y);
	spdlog::info("SetPosition [{0}, {1}]", x, y);
}
void SpriteLoader::SetRotation(sf::Sprite* sp, std::stringstream& str)
{
	spdlog::info("SetRotation set");
}
void SpriteLoader::SetScale(sf::Sprite* sp, std::stringstream& str)
{
	float x, y;
	str >> x >> y;
	sp->setScale(x, y);
	spdlog::info("SetScale [{0}, {1}]", x, y);
}
void SpriteLoader::SetOrigin(sf::Sprite* sp, std::stringstream& str)
{
	spdlog::info("SetOrigin set");
}