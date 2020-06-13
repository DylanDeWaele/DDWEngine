#pragma once
#include "Singleton.h"

	class Texture2D;
	class Font;
	class Music;
	class SoundEffect;
	class ResourceManager final : public Singleton<ResourceManager>
	{
	public:
		void Init(const std::string& data);
		Texture2D* LoadTexture(const std::string& file) const;
		Font* LoadFont(const std::string& file, unsigned int size) const;
		Music* LoadMusic(const std::string& file, bool playOnStart = false) const;
		SoundEffect* LoadSoundEffect(const std::string& file, bool playOnStart = false) const;

	private:
		friend class Singleton<ResourceManager>;
		ResourceManager() = default;
		std::string m_DataPath;
	};

