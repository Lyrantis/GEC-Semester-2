#include "SoundEffect.h"

SoundEffect::SoundEffect(std::string path)
{
	Load(path);
}

SoundEffect::~SoundEffect()
{

}

bool SoundEffect::Load(std::string path)
{
	m_sound = Mix_LoadWAV(path.c_str());

	if (m_sound == NULL)
	{
		std::cout << "Failed to load " << path << ". Error: " << Mix_GetError() << std::endl;
		return false;
	}
	return true;
}

void SoundEffect::Play(int loop)
{
	Mix_PlayChannel(-1, m_sound, loop);
}
