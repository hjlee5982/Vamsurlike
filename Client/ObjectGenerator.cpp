#include "pch.h"
#include "ObjectGenerator.h"
#include "Obstacle.h"
#include "BoxCollider2D.h"
#include "AssetManager.h"
#include "SpriteRenderer.h"
#include "Texture.h"
#include "Transform.h"
#include "EventManager.h"
#include "Event.h"
#include "Checker.h"
#include "CircleCollider2D.h"

void ObjectGenerator::Start()
{
	ObstaclePooling();
	CheckerPooling();
}

void ObjectGenerator::Update()
{
	Generate();
}

void ObjectGenerator::ReturnPool(sptr<class GameObject> obj, int idx)
{
	if (idx == 0)
	{
		_obstacles.push(obj);
		obj->SetActive(false);
	}
	else if (idx == 1)
	{
		_checkers.push(obj);
		obj->SetActive(false);
	}
}

void ObjectGenerator::Reset()
{
	_elapsed = 0.f;
}

void ObjectGenerator::Generate()
{
	_elapsed += TIMER.DeltaTime();

	if (_elapsed >= _frequency)
	{
		_elapsed = 0.f;

		f32 height = RANDOM.Range(-2.f, 2.f);
		f32 gap    = RANDOM.Range(3.6f, 3.9f);

		f32 topPos = 0.f;
		f32 btmPos = 0.f;

		auto top = _obstacles.front(); _obstacles.pop();
		top->GetComponent<Obstacle>()->_isColliding = false;
		top->SetActive(true);
		{
			auto tf = top->GetComponent<Transform>();
			{
				tf->SetScale(Vector3(1.f, gap + height, 1.f));

				f32 y = tf->GetScale().y;
				tf->SetPosition(Vector3(5.f, 5.f - y / 2.f, 0.f));
			}
			auto ctf = tf->GetChild(0)->GetComponent<Transform>();
			{
				ctf->SetParent(tf);
				ctf->SetScale(Vector3(1.1f, 0.7f, 1.f));
				ctf->SetLocalPosition(Vector3(0.f, -0.5f, 0.f));

				topPos = ctf->GetPosition().y;
			}
		}
		auto btm = _obstacles.front(); _obstacles.pop();
		btm->GetComponent<Obstacle>()->_isColliding = false;
		btm->SetActive(true);
		{
			auto tf = btm->GetComponent<Transform>();
			{
				tf->SetScale(Vector3(1.f, gap - height, 1.f));

				f32 y = tf->GetScale().y;
				tf->SetPosition(Vector3(5.f, -5.f + y / 2.f, 0.f));
			}
			auto ctf = tf->GetChild(0)->GetComponent<Transform>();
			{
				ctf->SetParent(tf);
				ctf->SetScale(Vector3(1.1f, 0.7f, 1.f));
				ctf->SetLocalPosition(Vector3(0.f, 0.5f, 0.f));

				btmPos = ctf->GetPosition().y;
			}
		}

		f32 avg = (topPos + btmPos) / 2.f;
		f32 scl = topPos - btmPos;

		auto ckr = _checkers.front(); _checkers.pop();
		ckr->GetComponent<Checker>()->_isColliding = false;
		ckr->SetActive(true);
		{
			auto tf = ckr->GetComponent<Transform>();
			{
				tf->SetScale(Vector3(0.3f, scl - 0.8f, 1.f));
				tf->SetPosition(Vector3(6.f, avg, 0.f));
			}
		}
	}
}

void ObjectGenerator::ObstaclePooling()
{
	for (int i = 0; i < _poolSize; ++i)
	{
		auto obstacle = Instantiate();
		{
			{
				obstacle->tag = "Obstacle";
			}
			auto tf = obstacle->AddComponent<Transform>();
			auto sr = obstacle->AddComponent<SpriteRenderer>();
			{
				sr->SetTexture(L"Texture_Rope");
			}
			auto bc = obstacle->AddComponent<BoxCollider2D>();
			{
				bc->Size(Vector3(0.5f, 1.f, 1.f));
			}
			auto ot = obstacle->AddComponent<Obstacle>();
			{
				ot->SetGenerator(shared_from_this());
			}

			auto cloud = Instantiate();
			{
				{
					cloud->name = "Cloud";
					cloud->tag  = "Obstacle";
				}
				auto cloudTf = cloud->AddComponent<Transform>();
				{
					cloudTf->SetParent(tf);
					cloudTf->SetScale(Vector3(1.f, 0.5f, 1.f));
					cloudTf->SetLocalPosition(Vector3(0.f, -0.5f, 0.f));
				}
				auto sr = cloud->AddComponent<SpriteRenderer>();
				{
					sr->SetTexture(L"Texture_Cloud");
					sr->OrderInLayer = 15;
				}
				auto bc = cloud->AddComponent<BoxCollider2D>();
				{
					bc->Size(Vector3(0.8f, 0.8f, 1.f));
				}
			}
		}
		obstacle->SetActive(false);

		_obstacles.push(obstacle);
	}
}

void ObjectGenerator::CheckerPooling()
{
	for (int i = 0; i < _poolSize; ++i)
	{
		auto checker = Instantiate();
		{
			{
				checker->tag = "Checker";
			}
			auto ck = checker->AddComponent<Checker>();
			{
				ck->SetGenerator(shared_from_this());
			}
			checker->AddComponent<Transform>();
			checker->AddComponent<BoxCollider2D>();
		}

		checker->SetActive(false);

		_checkers.push(checker);
	}
}