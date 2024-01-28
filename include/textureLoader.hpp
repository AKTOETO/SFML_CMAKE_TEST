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
    inline void LoadAsset(
        const std::string& filename,
        TextureType::ID asset_name
    ) override;
    //{
    //    std::unique_ptr<sf::Texture> asset = std::make_unique<sf::Texture>();
    //    if (!asset->loadFromFile(m_FilePath + filename))
    //        throw std::runtime_error(
    //            "[AssetLoader::LoadAsset] Failed to load asset " +
    //            m_FilePath + filename
    //        );
    //
    //    auto inserted = m_LoadedAssets.insert(std::make_pair(
    //        asset_name, std::move(asset)));
    //    assert(inserted.second);
    //}
};

#endif //TEXTURELOADER_HPP