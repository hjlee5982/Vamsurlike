#pragma once

enum class InputState
{
	None,
	Down,
	Hold,
	Up
};


struct InputAction
{
	string name;
	List<int> keys;
	InputState state = InputState::None;

	std::function<void()> started;
	std::function<void()> performed;
	std::function<void()> canceled;
};


class InputMap
{
public:
	void AddAction(const string& name, const List<int>& keys)
	{
		InputAction action;
		{
			action.name = name;
			action.keys = keys;
		}
		_actions.push_back(action);
	}
	InputAction* FindAction(const string& name)
	{
		for (auto& action : _actions)
		{
			if (action.name == name)
			{
				return &action;
			}
		}

		return nullptr;
	}
	List<InputAction>& GetActions()
	{
		return _actions;
	}
private:
	List<InputAction> _actions;
};


class InputSystem : public Singleton<InputSystem>
{
public:
	virtual void Awake() override
	{
		InputMap map;
		{
			map.AddAction("Console", { 'Q', VK_F1});
		}
		INPUT.AddMap(map);
	}
public:
	InputAction* FindAction(const string& name)
	{
		for (auto& map : _maps)
		{
			if (auto* action = map.FindAction(name))
			{
				return action;
			}
		}

		return nullptr;
	}
public:
	void Update()
	{
		for (int i = 0; i < 256; ++i)
		{
			bool isDown = GetAsyncKeyState(i) & 0x8000;

			if (isDown == true)
			{
				if (_prevKeys[i] == false)
				{
					_keyState[i] = InputState::Down;
				}
				else
				{
					_keyState[i] = InputState::Hold;
				}
			}
			else
			{
				if (_prevKeys[i] == true)
				{
					_keyState[i] = InputState::Up;
				}
				else
				{
					_keyState[i] = InputState::None;
				}
			}

			_prevKeys[i] = isDown;
		}

		for (auto& map : _maps)
		{
			for (auto& action : map.GetActions())
			{
				InputState newState = InputState::None;

				for (int key : action.keys)
				{
					if (_keyState[key] == InputState::Down)
					{
						newState = InputState::Down;
					}
					else if (_keyState[key] == InputState::Hold && newState != InputState::Down)
					{
						newState = InputState::Hold;
					}
					else if (_keyState[key] == InputState::Up && newState == InputState::None)
					{
						newState = InputState::Up;
					}
				}

				if (newState != action.state)
				{
					switch (newState)
					{
					case InputState::Down:

						if (action.started)
						{
							action.started();
						}
						if (action.performed)
						{
							action.performed();
						}
						break;

					case InputState::Up:

						if (action.canceled)
						{
							action.canceled();
						}
						break;

					default:
						break;
					}
				}

				if (newState == InputState::Hold)
				{
					if (action.performed)
					{
						action.performed();
					}
				}

				action.state = newState;
			}
		}
	}
private:
	InputState GetActionState(const string& name)
	{
		for (auto& map : _maps)
		{
			if (auto* action = map.FindAction(name))
			{
				return action->state;
			}
		}
	}
public:
	void AddMap(const InputMap& map)
	{
		_maps.push_back(map);
	}
	bool IsActionDown(const string& name)
	{
		return GetActionState(name) == InputState::Down;
	}
	bool IsActionHold(const string& name)
	{
		return GetActionState(name) == InputState::Hold;
	}
	bool IsActionUp(const string& name)
	{
		return GetActionState(name) == InputState::Up;
	}
private:
	bool           _prevKeys[256];
	InputState     _keyState[256];
	List<InputMap> _maps;
};

