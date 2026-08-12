#pragma once
#include "../Engine/Actor.h"
struct BulletDesc : public nu::ActorDesc {
	int ammo = 0;
	float speed = 0.0f;
};
class Bullet : public nu::Actor {
public:
	Bullet() = default;
	Bullet(const BulletDesc& enemyDesc) : Actor{ enemyDesc } {
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

	virtual void OnCollision(Actor* other) override;


	float GetSpeed() { return m_speed; }

private:
	int m_ammo = 0;
	float m_speed = 400.0f;
};