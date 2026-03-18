#pragma once

#include "EngineEvent.h"

class EventManager : public Singleton<EventManager>
{
public:
	virtual ~EventManager()
	{
		/*for (auto& unsub : _callbackCache)
		{
			unsub();
		}*/
	}
public:
	using CallbackID = size_t;
private:
	static inline CallbackID _globalID = 0;
private:
	List<std::function<void()>> _callbackCache;
public:
	template<typename T>
	static CallbackID Subscribe(std::function<bool(const T&)> callback)
	{
		auto& data = GetData<T>();

		CallbackID id = ++_globalID;
		data.callbacks.push_back({ id, callback });

		return id;
	}

	template<typename T, typename C>
	static void Subscribe(bool (C::* method)(const T&), C* instance)
	{
		auto id = Subscribe<T>([=](const T& e)
			{
				return (instance->*method)(e);
			});

		EventManager::Instance()._callbackCache.push_back([id]() {
			Unsubscribe<T>(id);
			});
	}

	template<typename T>
	static void Unsubscribe(CallbackID id)
	{
		auto& data = GetData<T>();
		std::erase_if(data.callbacks, [id](const CallbackEntry<T>& entry) {return entry.id == id; });
	}

	template<typename T>
	static bool SendEvent(const T& e)
	{
		auto& data = GetData<T>();

		bool result = true;

		for (auto& entry : data.callbacks)
		{
			result &= entry.callback(e);
		}

		return result;
	}
private:
	template<typename T>
	struct CallbackEntry
	{
		CallbackID id;
		std::function<bool(const T&)> callback;
	};

	template<typename T>
	struct CallbackData
	{
		List<CallbackEntry<T>> callbacks;
		CallbackID lastID = 0;
	};

	template<typename T>
	static CallbackData<T>& GetData()
	{
		static CallbackData<T> data;
		return data;
	}
};

