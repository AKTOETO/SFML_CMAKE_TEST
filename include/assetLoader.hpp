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

    // загрузить ассет с диска в память
    virtual void LoadAsset(const std::string& filename, Enum asset_name) = 0;
    // получить ассет
    virtual AssetType& GetAsset(Enum asset_name);
    // удалить ассет
    virtual void DeleteAsset(Enum asset_name);
    // удалить все ассеты
    virtual void DeleteAllAsset();
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

template<typename AssetType, typename Enum>
inline void AssetLoader<AssetType, Enum>::DeleteAsset(Enum asset_name)
{
    auto found = m_LoadedAssets.find(asset_name);
    assert(found != m_LoadedAssets.end());
    m_LoadedAssets.erase(found);
}

template<typename AssetType, typename Enum>
inline void AssetLoader<AssetType, Enum>::DeleteAllAsset()
{
    m_LoadedAssets.clear();
}

#endif // ASSETLOADER_H

