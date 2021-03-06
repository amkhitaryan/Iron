#include "ResourcesManager.h"
#include "../Core/Log.h"
#include "../Audio/AudioSystem.h"
#include "../Audio/WavLoader.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <GLAD/glad.h>
#include <fstream>
// TODO: remove al dependency into AudioSystem
#include <AL/al.h>

ResourcesManager::~ResourcesManager()
{
    for (auto image : images)
    {
        glDeleteTextures(1, &image->TextureID);
        delete image;
    }

    for (auto audioTrack : audioTracks)
    {
        alDeleteBuffers(1, &audioTrack->BufferID);
        delete audioTrack;
    }

    for (auto animation : animations)
    {
        delete animation;
    }
}

Sprite* ResourcesManager::LoadImage(const char *filePath)
{
    //TODO: completely rework

    std::ifstream infile(filePath);
    if (!infile.good())
    {
        Log::LogError("File does not exist");
        return nullptr;
    }

    int w, h, c;
    unsigned char *imageData = stbi_load(filePath, &w, &h, &c, 4);
    GLuint texture;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(imageData);
    glBindTexture(GL_TEXTURE_2D, 0);

    auto image = new Sprite();
    image->ID = images.size() + 1;
    image->TextureID = (uint64_t)texture;
    image->Path = filePath;
    image->Width = w;
    image->Height = h;

    images.push_back(image);

    Log::LogInfo("Sprite loaded: " + std::string(filePath) + ", " + std::to_string(image->ID));

    return image;
}

Sprite* ResourcesManager::GetImage(uint64_t imageID)
{
    if (imageID == 0)
        return nullptr;

    if (imageID - 1 > images.size() || images[imageID - 1] == nullptr)
    {
        Log::LogError("Sprite does not exist");
        return nullptr;
    }

    return images[imageID - 1];
}

void ResourcesManager::UnloadImage(uint64_t imageID)
{
    auto sprite = GetImage(imageID);
    if (sprite == nullptr)
        return;

    glDeleteTextures(1, &sprite->TextureID);
    //images.erase(images.begin() + imageID); // TODO: remove
    images[imageID - 1] = nullptr;
    delete sprite;
}

static inline ALenum ToALFormat(int channels, int samples)
{
    bool stereo = (channels > 1);

    switch (samples) {
        case 16:
            if (stereo)
                return AL_FORMAT_STEREO16;
            else
                return AL_FORMAT_MONO16;
        case 8:
            if (stereo)
                return AL_FORMAT_STEREO8;
            else
                return AL_FORMAT_MONO8;
        default:
            return -1;
    }
}

AudioTrack* ResourcesManager::LoadAudioTrack(const char *filePath)
{
    std::ifstream infile(filePath);
    if (!infile.good())
    {
        Log::LogError("File does not exist");
        return nullptr;
    }

    if (!AudioSystem::Initialized())
    {
        Log::LogError("Can't load audio: audio system is not initialized");
        return nullptr;
    }

    ALuint audioBuffer;
    char* data;
    auto audioTrack = WavLoader::LoadWav(filePath, &data);
    if (audioTrack == nullptr)
        return nullptr;

    audioTrack->ID = audioTracks.size() + 1;

    alGenBuffers((ALuint)1, &audioBuffer);
    if (AudioSystem::CheckForErrors())
    {
        Log::LogError("Error generating audio buffer");
        return nullptr;
    }
    alBufferData(audioBuffer, ToALFormat(audioTrack->NumberOfChannels, audioTrack->BitsPerSample),
                 data, (ALsizei)audioTrack->NumberOfSamples, audioTrack->SampleRate);
    delete data;
    if (AudioSystem::CheckForErrors())
    {
        Log::LogError("Error loading audio data to buffer");
        delete audioTrack;
        return nullptr;
    }

    audioTrack->BufferID = audioBuffer;
    audioTracks.push_back(audioTrack);

    Log::LogInfo("Audio track loaded: " + std::string(filePath) + ", " + std::to_string(audioTrack->ID));

    return audioTrack;
}

AudioTrack *ResourcesManager::GetAudioTrack(uint64_t audioID)
{
    if (audioID == 0)
        return nullptr;

    if (audioID - 1 > images.size() || images[audioID - 1] == nullptr)
    {
        Log::LogError("Audio track does not exist");
        return nullptr;
    }

    return audioTracks[audioID - 1];
}

void ResourcesManager::UnloadAudioTrack(uint64_t audioID)
{
    auto audioTrack = GetAudioTrack(audioID);
    if (audioTrack == nullptr)
        return;

    alDeleteBuffers(1, &audioTrack->BufferID);
    //audioTracks.erase(audioTracks.begin() + audioID); // TODO: remove
    audioTracks[audioID - 1] = nullptr;
    delete audioTrack;

}

void ResourcesManager::AddAnimation(Animation *animation)
{
    animation->ID = animations.size() + 1;
    animations.push_back(animation);
}

Animation *ResourcesManager::GetAnimation(uint64_t animationID)
{
    if (animationID == 0)
        return nullptr;

    if (animationID - 1 > animations.size() || animations[animationID - 1] == nullptr)
    {
        Log::LogError("Animation does not exist");
        return nullptr;
    }

    return animations[animationID - 1];
}

void ResourcesManager::RemoveAnimation(uint64_t animationID)
{
    auto animation = GetAnimation(animationID);
    if (animation == nullptr)
        return;

    //animations.erase(animations.begin() + animationID); // TODO: remove
    animations[animationID - 1] = nullptr;
    delete animation;
}
