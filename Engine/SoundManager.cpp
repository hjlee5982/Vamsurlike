#include "pch.h"
#include "SoundManager.h"

void SoundManager::Awake()
{
	FMOD_RESULT result;

	// FMOD System 생성
	result = FMOD::System_Create(&_FMODSystem);
	if (result != FMOD_OK)
	{
		return;
	}

	// 초기화
	result = _FMODSystem->init(512, FMOD_INIT_NORMAL, nullptr);
	if (result != FMOD_OK)
	{
		return;
	}
}

void SoundManager::Update()
{
	_FMODSystem->update();
}

void SoundManager::Destroy()
{
	for (auto& pair : _sounds)
	{
		pair.second->release();
	}
	_sounds.clear();

	_FMODSystem->close();
	_FMODSystem->release();
	_FMODSystem = nullptr;
}

void SoundManager::LoadSound(const string& name, bool loop)
{
	FMOD_MODE mode = FMOD_DEFAULT;

	if (loop == true)
	{
		mode |= FMOD_LOOP_NORMAL;
	}
	else
	{
		mode |= FMOD_LOOP_OFF;
	}

	string path = _path + name;

	FMOD::Sound* sound = nullptr;
	if (_FMODSystem->createSound(path.c_str(), mode, nullptr, &sound) != FMOD_OK)
	{
		LOG_ERROR("사운드 로드 실패");
		return;
	}

	_sounds[name.substr(0, name.find('.'))] = sound;
}

void SoundManager::PlayBGM(const string& name, f32 volume)
{
	auto it = _sounds.find(name);
	if (it == _sounds.end())
	{
		LOG_WARNING("사운드가 없음");
		return;
	}

	if (_bgmChannel)
	{
		_bgmChannel->stop();
		_bgmChannel = nullptr;
	}

	_FMODSystem->playSound(it->second, nullptr, false, &_bgmChannel);
	_bgmChannel->setVolume(volume);
}

void SoundManager::StopBGM()
{
	if (_bgmChannel)
	{
		_bgmChannel->stop();
		_bgmChannel = nullptr;
	}
}

void SoundManager::PlaySFX(const string& name, f32 volume)
{
	auto it = _sounds.find(name);
	if (it == _sounds.end())
	{
		LOG_WARNING("사운드가 없음");
		return;
	}

	FMOD::Channel* channel = nullptr;
	_FMODSystem->playSound(it->second, nullptr, false, &channel);
	channel->setVolume(volume);
}
