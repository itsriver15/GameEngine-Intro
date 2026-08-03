#include "Enemy.h"
#include "Player.h"
#include "SpaceGame.h"
#include "../Engine/Engine.h" 

void Enemy::Update(float dt) {
	Player* player = m_scene->GetActorByName<Player>("Player");
	if (player) {
		Vector2 direction = player->GetTransform().position - m_transform.position;
		float rotation = direction.Angle();

		m_transform.rotation = rotation * RadToDeg;

		Vector2 forward{ 1,0 };
		forward = forward.Rotate(m_transform.rotation * DegToRad);
		AddVelocity(forward * m_speed * dt);

		float thrust = 0.0f;
		float rotate = 0.0f;

		forward = { 1.0f, 0.0f };
		Vector2 velocitiy = forward.Rotate(m_transform.rotation * DegToRad) * thrust;
		AddVelocity(velocitiy * dt);

		Actor::Update(dt);


	}
}

void Enemy::OnCollision(Actor* other) {

	if (other->GetTag() == "PlayerBullet") {
		SetDestroyed();
		other->SetDestroyed();
		cout << "Destroyed" << endl;
		if (m_scene && m_scene->GetGame())
		{
			((SpaceGame*)m_scene->GetGame())->AddPoints(100);
		}

		Engine::Get().GetAudio().PlaySound("explosion");

		// create particle explosion
		for (int i = 0; i < 100; i++)
		{
			nu::Particle particle;
			particle.position = m_transform.position;
			particle.color = { 1.0f, 0.0f, 0.0f };
			particle.lifespan = nu::RandomFloat(0.5f, 2.0f);
			particle.velocity = { nu::RandomFloat(-600.0f, 600.0f), nu::RandomFloat(-600.0f, 600.0f) };

			nu::Engine::Get().GetPS().AddParticle(particle);
		}
	}
}
