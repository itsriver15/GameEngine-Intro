#pragma once
#include "../Engine/Actor.h"
struct EnemyDesc : public nu::ActorDesc {
	int ammo = 0;
	float speed = 0.0f;
};
class Enemy : public nu::Actor {
public:
	Enemy() = default;
	Enemy(const EnemyDesc& enemyDesc) : Actor{ enemyDesc } {	
		m_ammo = enemyDesc.ammo;
		m_speed = enemyDesc.speed;
	}

	void Update(float dt) override;
	void SetSpeed(float speed) {
		m_speed = speed;
	}

	float GetSpeed() const {
		return m_speed;
	}

	void OnCollision(Actor* other) override;


	virtual void Read(const json::value_t& value) override;

private:
	int m_ammo = 0;
	float m_speed = 0.0f;
};