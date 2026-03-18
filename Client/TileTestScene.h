#pragma once

#include "Scene.h"

class TileTestScene : public Scene
{
public:
	virtual void Initialize() override;
protected:
	virtual void LoadResources()  override;
	virtual void SetInputSystem() override;
	virtual void AddGameObject()  override;
	virtual void EngineSetting()  override;
};

