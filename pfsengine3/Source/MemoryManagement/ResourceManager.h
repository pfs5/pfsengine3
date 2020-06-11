#pragma once

#include "Misc/PFSEngineString.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <map>
// ----------------------------------------------------------------------------
/**
	Manages all "heavy" external resources for the game and allows easy access by name using the singleton pattern.

	Handles images, fonts, ...
**/
class PResourceManager 
{
	// Folders
	static const PString RESOURCE_MANAGER_DATA;
	static const PString FONT_FOLDER;
	static const PString TEXTURE_FOLDER;
	static const PString AUDIO_FOLDER;
	static const PString RAW_DATA_FOLDER;

	std::map<PString, sf::Font*> _fonts;
	std::map<PString, sf::Texture*> _textures;
	std::map<PString, sf::SoundBuffer*> _sounds;
	std::map<PString, sf::Music*> _music;

	const PString DEFAULT_OBJECT_NAME = "default";

public:
	PResourceManager();

public:
#pragma region Singleton
	static PResourceManager & GetInstance()
	{
		static PResourceManager instance;
		return instance;
	}

	static PResourceManager& ForceInit()
	{
		return GetInstance();
	}
#pragma endregion

	static sf::Font* GetFontStatic(const PString& fontName) { return GetInstance().GetFont(fontName); }
	static sf::Texture* GetTextureStatic(const PString& textureName) { return GetInstance().GetTexture(textureName); }
	static sf::SoundBuffer* GetSoundStatic(const PString& soundName) { return GetInstance().GetSound(soundName); }
	static sf::Music* GetMusicStatic(const PString& musicName) { return GetInstance().GetMusic(musicName); }

	static PString GetRawDataPath(const PString& dataName) { return PResourceManager::GetInstance().RAW_DATA_FOLDER + dataName; }

	sf::Font* GetFont(const PString& fontName) const;
	sf::Texture* GetTexture(const PString& textureName) const;
	sf::SoundBuffer* GetSound(const PString& soundName) const;
	sf::Music* GetMusic(const PString& musicName) const;

private:
	std::map<PString, sf::Font*> LoadFonts();
	sf::Font* LoadFont(const PString& fileName);

	std::map<PString, sf::Texture*> LoadTextures();
	sf::Texture* LoadTexture(const PString& fileName);

	std::map<PString, sf::SoundBuffer*> LoadSounds();
	sf::SoundBuffer* LoadSound(const PString& fileName);

	std::map<PString, sf::Music*> LoadMusic();
	sf::Music* LoadMusicFile(const PString& fileName);
};
// ----------------------------------------------------------------------------