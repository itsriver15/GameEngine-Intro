#include "Bullet.h"
#include "../Engine/MathUtils.h"

void Bullet::Update(float dt) {

	nu::Vector2 forward{ 1.0f, 0.0f };
	nu::Vector2 velocity = forward.Rotate(m_transform.rotation * nu::DegToRad) * m_speed;

	SetVelocity(velocity);


	Actor::Update(dt);
}

void Bullet::OnCollision(Actor* other) {
	
	if (GetTag() == "PlayerBullet") {
		if (other->GetName() == "Enemy") {
			other->SetDestroyed();
			SetDestroyed();
		}
	}
	else if (GetTag() == "bullet") {
		if (other->GetName() == "Player") {
			other->SetDestroyed();
			SetDestroyed();
		}
	}
	
	
}