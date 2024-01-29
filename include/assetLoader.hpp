#ifndef ASSETLOADER_H
#define ASSETLOADER_H

#include <cassert>
#include <string>
#include <map>
#include <memory>

// базовое перечисление типов ассетов
namespace AssetType
{
    enum class ID
    {
        None = 0,
    };
};

// абстрактный базовый класс для загрузки 
// ассетов разного типа
template <typename AssetType, typename Enum = AssetType::ID>
class AssetLoader 
{
protected:
    // путь к папке с ассетами текущего типа
    std::string m_FilePath;

    // хранение загруженных ресурсов 
    std::map<Enum, std::unique_ptr<AssetType>> m_LoadedAssets;

public:
    AssetLoader() = delete;
    AssetLoader(const std::string& filepath);
    virtual ~AssetLoader();

    virtual void LoadAsset(const std::string& filename, Enum asset_name) = 0;
    virtual AssetType& GetAsset(Enum asset_name);
};


template <typename AssetType, typename Enum>
inline AssetLoader<AssetType, Enum>::AssetLoader(const std::string& filepath)
    :m_FilePath("assets/"+filepath)
{}

template <typename AssetType, typename Enum>
inline AssetLoader<AssetType, Enum>::~AssetLoader()
{}

template <typename AssetType, typename Enum>
inline AssetType& AssetLoader<AssetType, Enum>::GetAsset(Enum asset_name)
{
    auto found = m_LoadedAssets.find(asset_name);
    assert(found != m_LoadedAssets.end());
    return *(found->second);
}

#endif // ASSETLOADER_H

