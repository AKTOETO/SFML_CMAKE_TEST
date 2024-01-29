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
#define STR(x) #x
#define ADD_STR_TO_TAGS(tag) m_str_to_tags[STR(tag)] = SpriteInfo::ConfigTag::tag;

	ADD_STR_TO_TAGS(SetTexture);
	ADD_STR_TO_TAGS(SetTextureRect);
	ADD_STR_TO_TAGS(SetColor);
	ADD_STR_TO_TAGS(SetPosition);
	ADD_STR_TO_TAGS(SetRotation);
	ADD_STR_TO_TAGS(SetScale);
	ADD_STR_TO_TAGS(SetOriginInCenter);


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
#define ADD_TAG_TO_FUNC(tag) m_tag_to_func[SpriteInfo::ConfigTag::tag] = LAMBDA_F(tag);

	// сопоставление тегов функциям обработки
	ADD_TAG_TO_FUNC(SetTexture);
	ADD_TAG_TO_FUNC(SetTextureRect);
	ADD_TAG_TO_FUNC(SetColor);
	ADD_TAG_TO_FUNC(SetPosition);
	ADD_TAG_TO_FUNC(SetRotation);
	ADD_TAG_TO_FUNC(SetScale);
	ADD_TAG_TO_FUNC(SetOriginInCenter);

#undef STR
#undef ADD_STR_TO_TAGS
#undef ADD_TAG_TO_FUNC
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

		// если строка не пустая и
		// первый символ # то это комментарий
		if(tag.length() > 0 && tag[0] != '#')
		{
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
	sf::IntRect rect;
	
	// left top width height
	if (str.peek() == EOF) spdlog::error("[SpriteLoader::SetTextureRect] There is no params for rectangle (left top width height)");
	str >> rect.left;
	if (str.peek() == EOF) spdlog::error("[SpriteLoader::SetTextureRect] There is not enough params");
	str >> rect.top;
	if (str.peek() == EOF) spdlog::error("[SpriteLoader::SetTextureRect] There is not enough params");
	str >> rect.width;
	if (str.peek() == EOF) spdlog::error("[SpriteLoader::SetTextureRect] There is not enough params");
	str >> rect.height;

	spdlog::info("SetTextureRect [{0}, {1}, {2}, {3}]",
		rect.left, rect.top, rect.width, rect.height);

	sp->setTextureRect(rect);
}
void SpriteLoader::SetColor(sf::Sprite* sp, std::stringstream& str)
{
	unsigned short cl[4];

	// red green blue alpha
	if (str.peek() == EOF) spdlog::error("[SpriteLoader::SetColor] There is no params for color (r g b a) in [0, 255]");
	str >> cl[0];
	if (str.peek() == EOF) spdlog::error("[SpriteLoader::SetColor] There is not enough params");
	str >> cl[1];
	if (str.peek() == EOF) spdlog::error("[SpriteLoader::SetColor] There is not enough params");
	str >> cl[2];
	if (str.peek() == EOF) spdlog::error("[SpriteLoader::SetColor] There is not enough params");
	str >> cl[3];

	spdlog::info("SetColor [{0}, {1}, {2}, {3}]", cl[0], cl[1], cl[2], cl[3]);

	sp->setColor({ 
		static_cast<sf::Uint8>(cl[0]),
		static_cast<sf::Uint8>(cl[1]),
		static_cast<sf::Uint8>(cl[2]),
		static_cast<sf::Uint8>(cl[3])
		});
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
	float angle;
	str >> angle;

	spdlog::info("SetRotation [{0}]", angle);

	sp->setRotation(angle);
}
void SpriteLoader::SetScale(sf::Sprite* sp, std::stringstream& str)
{
	float x, y;
	str >> x >> y;
	sp->setScale(x, y);
	spdlog::info("SetScale [{0}, {1}]", x, y);
}
void SpriteLoader::SetOriginInCenter(sf::Sprite* sp, std::stringstream& str)
{
	auto bounds = sp->getLocalBounds();
	sf::Vector2f center(bounds.width / 2., bounds.height / 2.);

	spdlog::info("SetOriginInCenter [{0}, {1}]", center.x, center.y);

	sp->setOrigin(center);
}