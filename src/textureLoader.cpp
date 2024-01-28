#include "textureLoader.hpp"

TextureLoader::TextureLoader()
    :AssetLoader("textures/src/")
{}

void TextureLoader::LoadAsset(
    const std::string& filename,
    TextureType::ID asset_name
)
{
    std::unique_ptr<sf::Texture> asset = std::make_unique<sf::Texture>();
    if (!asset->loadFromFile(m_FilePath + filename))
        throw std::runtime_error(
            "[AssetLoader::LoadAsset] Failed to load asset " +
            m_FilePath + filename
        );

    auto inserted = m_LoadedAssets.insert(std::make_pair(
        asset_name, std::move(asset)));
    assert(inserted.second);
}