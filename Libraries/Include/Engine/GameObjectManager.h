#pragma once

class GameObjectManager : public Singleton<GameObjectManager>
{
public:
	void AddGameObject(sptr<class GameObject> go);
	void AddUIObject  (sptr<class GameObject> go);
public:
	void Awake();
	void Start();
	void Update();
	void LateUpdate();
	void FixedUpdate();
private:
	List<sptr<class GameObject>> _gameObjects;
	List<sptr<class GameObject>> _uiObject;
private:
	List<sptr<class GameObject>> _newObjects;
	List<sptr<class GameObject>> _pendingAwake;
	List<sptr<class GameObject>> _pendingStart;
};

