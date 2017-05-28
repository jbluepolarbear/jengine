#ifndef J_IMAGE_H
#define J_IMAGE_H
#include <vector>

class JImage
{
public:
    std::vector<unsigned char> mData;
    unsigned mWidth;
    unsigned mHeight;
    unsigned mTextureId;
    unsigned mError;
    std::string mFilename;
};

#endif//J_IMAGE_H