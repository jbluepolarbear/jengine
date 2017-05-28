#ifndef JTEXTURE_MANAGER_H
#define JTEXTURE_MANAGER_H

#include "jengine.h"
#include <memory>
#include <map>

class JTexture;
class JTextureManager
{
public:
    JTextureManager(JEngine &jengine);
    ~JTextureManager();
    std::shared_ptr<JTexture> GetTexture(const std::string texturePath);
private:
    auto GetFilenameFromPath(const std::string &path);
    JEngine &mJEngine;
    std::map<std::string, std::shared_ptr<JTexture> > mJTextures;
};

#endif//JTEXTURE_MANAGER_H