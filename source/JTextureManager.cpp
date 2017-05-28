#include "JTextureManager.h"
#include <fstream>
#include <iostream>

JTextureManager::JTextureManager(JEngine &jengine)
    : mJEngine(jengine)
{

}

JTextureManager::~JTextureManager()
{

}

auto JTextureManager::GetFilenameFromPath(const std::string &path)
{
    auto lastOfStart = path.find_last_of("\\") + 1;
    return path.substr(lastOfStart, path.size() - lastOfStart);
}

std::shared_ptr<JTexture> JTextureManager::GetTexture(const std::string texturePath)
{
    std::string filename = GetFilenameFromPath(texturePath);
    std::string fullPath = mJEngine.ResourcesPath() + texturePath;

    std::fstream file(fullPath.c_str(), std::fstream::in | std::fstream::binary);
    if (file.is_open())
    {
        std::cout << "Hello file!" << std::endl;
    }

    return nullptr;
}