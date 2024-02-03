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
protected:

	virtual void ReadConfig(sf::Texture*, const std::string&) override;

public:
    TextureLoader();

    //inline void LoadAsset(
    //    const std::string& filename,
    //    TextureType::ID asset_name
    //) override;
};

#endif //TEXTURELOADER_HPP