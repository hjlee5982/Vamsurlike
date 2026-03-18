#pragma once

template<typename T>
class Singleton abstract
{
protected:
	Singleton() {}
	Singleton(const Singleton&) = delete;
	Singleton& operator = (const Singleton&) = delete;
public:
	virtual ~Singleton() = default;
public:
	virtual void Awake() {};
public:
	static T& Instance()
	{
		static T instance;
		return instance;
	}
};

#define DIRECTX Device::Instance()
#define DEVICE  Device::Instance().GetDevice()
#define CONTEXT Device::Instance().GetContext()

#define LOG		   Log				::Instance()
#define FONT	   FontManager		::Instance()
#define EVENT      EventManager
#define ASSET      AssetManager     ::Instance()
#define TIMER      Timer            ::Instance()
#define INPUT      InputSystem      ::Instance()
#define SCENE	   SceneManager     ::Instance()
#define SOUND	   SoundManager     ::Instance()
#define ENGINE     Engine           ::Instance()
#define RANDOM	   Random			::Instance()
#define RENDERER   RenderManager    ::Instance()
#define COLLISION  CollisionManager ::Instance()
#define GAMEOBJECT GameObjectManager::Instance()
