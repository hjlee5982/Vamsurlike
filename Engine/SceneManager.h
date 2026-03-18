#pragma once

class SceneManager : public Singleton<SceneManager>
{
public:
	virtual void Awake() override;
public:
	void Start();
	void Update();
	void LateUpdate();
	void FixedUpdate();
public:
	void Destroy(sptr<class GameObject> go);
public:
	void LoadScene();
	void SaveScene();
public:
	void AddScene(const string& name, sptr<class Scene> scene);
	void AddGameObject(sptr<class GameObject> go);
private:
	Dictionary<string, sptr<class Scene>> _scenes;
	wptr<class Scene> _currentScene;
};

