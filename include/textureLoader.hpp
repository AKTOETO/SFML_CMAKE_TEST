#ifndef TEXTURELOADER_HPP
#define TEXTURELOADER_HPP

#include <SFML/Graphics.hpp>
#include "assetLoader.hpp"

namespace TextureType
{
    enum class ID
    {
        None = 0,
        Chel,



        AllTypes
    };
};

// загрузчик текстур
class TextureLoader :
    public AssetLoader<sf::Texture, TextureType::ID>
{
public:
    TextureLoader();
};

#endif //TEXTURELOADER_HPP