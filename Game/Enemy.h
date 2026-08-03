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
	Enemy(float speed, const nu::Transform& transform) : Actor{ transform }, m_speed{ speed } {};
	Enemy(float speed, const nu::Transform& transform, const Model& model) : Actor{ transform, model }, m_speed{ speed } {};

	void Update(float dt) override;
	void SetSpeed(float speed) override {
		m_speed = speed;
	}

	float GetSpeed() const override {
		return m_speed;
	}

	void OnCollision(Actor* other) override;

private:
	int m_ammo = 0;
	float m_speed = 0.0f;
};