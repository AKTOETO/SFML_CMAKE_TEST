#ifndef SPRITELOADER_HPP
#define SPRITELOADER_HPP

#include "textureLoader.hpp"
#include <fstream>
#include <spdlog/spdlog.h>
#include <functional>
#include <strstream>

namespace SpriteInfo
{
    enum class ID
    {
        None = 0,
        Chel,



        AllTypes
    };

    enum class ConfigTag
    {
        None = 0,
        SetTexture,
        SetTextureRect,
        SetColor,
        SetPosition,
        SetRotation,
        SetScale,
        SetOriginInCenter,

        AllTags
    };
};

// ��������� ��������
class SpriteLoader :
    public AssetLoader<sf::Sprite, SpriteInfo::ID>
{
private:
    TextureLoader& m_txt_loader;
    // ��� �� ������� - ��� �� ConfigTag
    std::map<std::string, SpriteInfo::ConfigTag> m_str_to_tags;

    // ������� ��������� ����
    using TagHandleFunc = std::function<void(sf::Sprite*, std::stringstream&)>;

    // ��� �� ConfigTag - ��������� ����
    std::map<SpriteInfo::ConfigTag, TagHandleFunc> m_tag_to_func;

public:
    SpriteLoader() = delete;
    SpriteLoader(TextureLoader& txt_loader);

    virtual void LoadAsset(const std::string& filename, SpriteInfo::ID asset_name) override;

private:

    // ������ �������
    void ReadConfig(sf::Sprite*, const std::string&);

    // ������� ��������� �����
    void SetTexture        (sf::Sprite* sp, std::stringstream& str);
    void SetTextureRect    (sf::Sprite* sp, std::stringstream& str);
    void SetColor          (sf::Sprite* sp, std::stringstream& str);
    void SetPosition       (sf::Sprite* sp, std::stringstream& str);
    void SetRotation       (sf::Sprite* sp, std::stringstream& str);
    void SetScale          (sf::Sprite* sp, std::stringstream& str);
    void SetOriginInCenter (sf::Sprite* sp, std::stringstream& str);

};

#endif //SPRITELOADER_HPP