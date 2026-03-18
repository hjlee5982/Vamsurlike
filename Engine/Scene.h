#pragma once

class Scene abstract
{
	friend class SceneManager;
public:
	virtual void Initialize() = 0;
	virtual void Save(const string& path);
protected:
	virtual void LoadResources()  = 0;
	virtual void SetInputSystem() = 0;
	virtual void AddGameObject()  = 0;
	virtual void EngineSetting()  = 0;
public:
	void AddGameObject(sptr<class GameObject> go);
private:
	void Awake();
	void Start();
	void Update();
	void LateUpdate();
	void FixedUpdate();
private:
	void Destroy(sptr<class GameObject> go);
private:
	List<sptr<class GameObject>> _gameObjects;
	List<sptr<class GameObject>> _uiObjects;
private:
	List<sptr<class GameObject>> _newObjects;
	List<sptr<class GameObject>> _pendingAwake;
	List<sptr<class GameObject>> _pendingStart;
private:
	List<sptr<class GameObject>> _destroyObjects;
private:
	List<sptr<Scene>> _scenes;
	sptr<Scene> _currentScene;
};

