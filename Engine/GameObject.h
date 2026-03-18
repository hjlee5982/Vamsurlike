#pragma once

class GameObject : public std::enable_shared_from_this<GameObject>
{
public:
	nlohmann::json MakeJson();
	void LoadJson(const nlohmann::json& json);
public:
	void OnCollisionEnter2D(sptr<class Collider> collider);
public:
	template<typename T, typename ...Args>
	sptr<T> AddComponent(Args&& ... args);
	template<typename T, typename ...Args>
	sptr<T> GetComponent();
public:
	void Awake();
	void Start();
	void Update();
	void LateUpdate();
	void FixedUpdate();
public:
	void SetActive(bool active);
private:
	Dictionary<u64, sptr<class Component>> _components;
public:
	sptr<class Transform> transform;
public:
	uint64_t id       = 0;
	bool     isActive = true;
	string   name     = "none";
	string   tag      = "none";
};



template<typename T, typename ...Args>
sptr<T> GameObject::AddComponent(Args&& ... args)
{
	static_assert(std::is_base_of<Component, T>::value, "T must be derived from Component");

	auto idx = typeid(T).hash_code();

	if (_components.find(idx) == _components.end())
	{
		sptr<T> component = makeSptr<T>(args...);

		component->SetOwner(shared_from_this());

		// 컴포넌트 어웨이크 전에 초기화가 필요한 경우
		// ex) 기본 머티리얼이나 기본 매시 생성해줘야 하는 컴포넌트들이 필요
		component->Init();

		_components.emplace(idx, component);

		return component;
	}

	return GetComponent<T>();
}

template<typename T, typename ...Args>
sptr<T> GameObject::GetComponent()
{
	static_assert(std::is_base_of<Component, T>::value, "T must be derived from Component");

	auto it = _components.find(typeid(T).hash_code());

	if (it != _components.end())
	{
		return std::static_pointer_cast<T>(it->second);
	}

	return nullptr;
}