#pragma once

#include "FMOD/fmod.hpp"

class SoundManager : public Singleton<SoundManager>
{
public:
	virtual void Awake() override;
public:
	void Update();
	void Destroy();
public:
	void LoadSound(const string& name, bool loop = false);
public:
	void PlayBGM(const string& name, f32 volume = 1.f);
	void StopBGM();
public:
	void PlaySFX(const string& name, f32 volume = 1.f);
private:
	FMOD::System*  _FMODSystem = nullptr;
	FMOD::Channel* _bgmChannel = nullptr;
	Dictionary<string, FMOD::Sound*> _sounds;
private:
	const string _path = "../Assets/Sound/";
};

