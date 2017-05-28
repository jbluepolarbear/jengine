#ifndef J_TEXTURE_H
#define J_TEXTURE_H
#include <memory>
#include <string>

class JImage;
class JTexture
{
public:
    JTexture();
    ~JTexture();
    unsigned GetTextureId();
    unsigned GetWidth();
    unsigned GetHeight();
    const std::string &GetFilename() const;
private:
    friend class JTextureManager;
    std::shared_ptr<JImage> mImage;
};

#endif//J_TEXTURE_H