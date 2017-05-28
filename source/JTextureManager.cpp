#include "JTextureManager.h"
#include <fstream>
#include <iostream>
#include "gl/glew.h"
#include "SDL/SDL_opengl.h"
#include "JMathUtils.h"
#include "lodepng.h"
#include "JImage.h"
#include "JTexture.h"

void FreeOpenGLTexture(unsigned textureId)
{
    glDeleteTextures(1, &textureId);
}

unsigned CreateOpenGLTexture(std::shared_ptr<JImage> jImage, bool powerOf2 = false)
{
    std::vector<unsigned char> data2 = jImage->mData;
    unsigned width2 = jImage->mWidth;
    unsigned height2 = jImage->mHeight;

    const unsigned bytesPerPixel = 4;

    if (powerOf2)
    {
        width2 = nextPowerOf2(width2);
        height2 = nextPowerOf2(height2);
        data2.clear();
        data2.resize(width2 * height2 * bytesPerPixel);

        for (size_t y = 0; y < jImage->mHeight; y++)
        {
            for (size_t x = 0; x < jImage->mWidth; x++)
            {
                for (size_t c = 0; c < 4; c++)
                {
                    data2[4 * width2 * y + 4 * x + c] = jImage->mData[4 * jImage->mWidth * y + 4 * x + c];
                }
            }
        }
    }

    // Enable the texture for OpenGL.
    glEnable(GL_TEXTURE_2D);
    unsigned textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //GL_NEAREST = no smoothing
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, bytesPerPixel, width2, height2, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2.data());

    return textureId;
}

JTextureManager::JTextureManager(JEngine &jengine)
    : mJEngine(jengine)
{
    // Load file and decode image.
    mDefaultImage = std::make_shared<JImage>();
    mDefaultImage->mData = {255, 255, 255, 255};
    mDefaultImage->mWidth = 1;
    mDefaultImage->mHeight = 1;
    mDefaultImage->mError = 0;
    mDefaultImage->mTextureId = CreateOpenGLTexture(mDefaultImage, false);
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
    std::string fullPath = mJEngine.ResourcesPath() + texturePath;

    auto jTexture = std::make_shared<JTexture>();
    jTexture->mImage = mDefaultImage;

    mJEngine.ThreadPool().enqueue(std::bind([this](const std::string &fullPath, std::shared_ptr<JTexture> jTexture)
    {
        // Load file and decode image.
        auto image = std::make_shared<JImage>();
        image->mFilename = GetFilenameFromPath(fullPath);
        image->mError = lodepng::decode(image->mData, image->mWidth, image->mHeight, fullPath);

        return std::bind([this](std::shared_ptr<JImage> image, std::shared_ptr<JTexture> jTexture)
        {
            jTexture->mImage = image;
            jTexture->mImage->mTextureId = CreateOpenGLTexture(jTexture->mImage, false);
        }, image, jTexture);
    }, fullPath, jTexture));

    return jTexture;
}