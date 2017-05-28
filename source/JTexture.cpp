#include "JTexture.h"
#include "JImage.h"

JTexture::JTexture()
{

}

JTexture::~JTexture()
{

}

unsigned JTexture::GetTextureId()
{
    return mImage->mTextureId;
}

unsigned JTexture::GetWidth()
{
    return mImage->mWidth;
}

unsigned JTexture::GetHeight()
{
    return mImage->mHeight;
}

const std::string &JTexture::GetFilename() const
{
    return mImage->mFilename;
}
