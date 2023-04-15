#pragma once
#include <SDL_mixer.h>
#include <string>
#include <iostream>

class SoundEffect
{
	Mix_Chunk* m_sound = nullptr;
	int m_volume = (MIX_MAX_VOLUME * 80) / 100;
	int m_channel;

public:

	SoundEffect(std::string path);
	~SoundEffect();

	bool Load(std::string path);
	void Play(int loop);
};

