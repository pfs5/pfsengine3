#include "ResourceManager.h"
#include "ThirdParty/json.h"
#include <fstream>
// ----------------------------------------------------------------------------
const PString PResourceManager::RESOURCE_MANAGER_DATA	= "../resources/resource_manager.json";
const PString PResourceManager::AUDIO_FOLDER			= "../resources/audio/";
const PString PResourceManager::TEXTURE_FOLDER			= "../resources/textures/";
const PString PResourceManager::FONT_FOLDER				= "../resources/fonts/";
const PString PResourceManager::RAW_DATA_FOLDER			= "../resources/raw_data/";
// ----------------------------------------------------------------------------
PResourceManager::PResourceManager()
{
	_fonts = LoadFonts();
	_textures = LoadTextures();
	_sounds = LoadSounds();
	_music = LoadMusic();
}
// ----------------------------------------------------------------------------
sf::Font* PResourceManager::GetFont(const PString& fontName) const 
{
	try
	{
		return _fonts.at(fontName);
	}
	catch (std::out_of_range e) 
	{
		return nullptr;
	}
}
// ----------------------------------------------------------------------------
sf::Texture* PResourceManager::GetTexture(const PString& textureName) const
{
	try 
	{
		return _textures.at(textureName);
	}
	catch (std::out_of_range e) 
	{
		try
		{
			return _textures.at(DEFAULT_OBJECT_NAME);
		}
		catch (std::out_of_range e) 
		{
			return nullptr;
		}
	}
}
// ----------------------------------------------------------------------------
sf::SoundBuffer* PResourceManager::GetSound(const PString& soundName) const
{
	try 
	{
		return _sounds.at(soundName);
	}
	catch (std::out_of_range e) 
	{
		return nullptr;
	}
}
// ----------------------------------------------------------------------------
sf::Music* PResourceManager::GetMusic(const PString& musicName) const
{
	try 
	{
		return _music.at(musicName);
	}
	catch (std::out_of_range e) 
	{
		return nullptr;
	}
}
// ----------------------------------------------------------------------------
std::map<PString, sf::Font*> PResourceManager::LoadFonts()
{
	std::map<PString, sf::Font*> fonts;

	// Load fonts
	std::ifstream file{ RESOURCE_MANAGER_DATA.CStr() };
	if (file.is_open()) 
	{
		nlohmann::json data;
		file >> data;
		for (auto font : data["fonts"]) 
		{
			fonts.emplace(font["name"], LoadFont(font["path"].get<std::string>()));
		}

		file.close();
	}

	return fonts;
}
// ----------------------------------------------------------------------------
sf::Font* PResourceManager::LoadFont(const PString& fileName)
{
	sf::Font * f = new sf::Font();
	if (!f->loadFromFile(FONT_FOLDER + fileName))
	{
		// #TODO
		//Debug::logError("Error loading font " + fileName);
	}

	return f;
}
// ----------------------------------------------------------------------------
std::map<PString, sf::Texture*> PResourceManager::LoadTextures()
{
	std::map<PString, sf::Texture*> textures;

	// Load textures
	std::ifstream file{ RESOURCE_MANAGER_DATA.CStr() };
	if (file.is_open()) 
	{
		nlohmann::json data;
		file >> data;
		for (auto tex : data["textures"]) 
		{
			textures.emplace(tex["name"], LoadTexture(tex["path"].get<std::string>()));
		}

		file.close();
	}

	return textures;
}
// ----------------------------------------------------------------------------
sf::Texture* PResourceManager::LoadTexture(const PString& _fileName)
{
	sf::Texture * t = new sf::Texture();
	if (!t->loadFromFile(TEXTURE_FOLDER + _fileName)) 
	{
		// #TODO
		//Debug::logError("Error loading texture " + _fileName);
	}

	return t;
}
// ----------------------------------------------------------------------------
std::map<PString, sf::SoundBuffer*> PResourceManager::LoadSounds()
{
	std::map<PString, sf::SoundBuffer*> sounds;

	// Load sounds
	std::ifstream file{ RESOURCE_MANAGER_DATA.CStr() };
	if (file.is_open()) 
	{
		nlohmann::json data;
		file >> data;
		for (auto sound : data["sounds"]) 
		{
			sounds.emplace(sound["name"], LoadSound(sound["path"].get<std::string>()));
		}

		file.close();
	}

	return sounds;
}
// ----------------------------------------------------------------------------
sf::SoundBuffer* PResourceManager::LoadSound(const PString& _fileName)
{
	sf::SoundBuffer * b = new sf::SoundBuffer();
	if (!b->loadFromFile(AUDIO_FOLDER + _fileName)) 
	{
		// #TODO
		//Debug::logError("Error load audio " + _fileName);
	}

	return b;
}
// ----------------------------------------------------------------------------
std::map<PString, sf::Music*> PResourceManager::LoadMusic() 
{
	std::map<PString, sf::Music*> music;

	// Load sounds
	std::ifstream file{ RESOURCE_MANAGER_DATA.CStr() };
	if (file.is_open()) 
	{
		nlohmann::json data;
		file >> data;
		for (auto sound : data["music"]) 
		{
			music.emplace(sound["name"], LoadMusicFile(sound["path"].get<std::string>()));
		}

		file.close();
	}

	return music;
}
// ----------------------------------------------------------------------------
sf::Music* PResourceManager::LoadMusicFile(const PString& fileName)
{
	sf::Music * m = new sf::Music();
	if (!m->openFromFile(AUDIO_FOLDER + fileName)) 
	{
		// #TODO
		//Debug::logError("Error load audio " + _fileName);
	}

	return m;
}
// ----------------------------------------------------------------------------