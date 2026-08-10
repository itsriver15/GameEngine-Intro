#include "../Engine/Engine.h"
#include "../Engine/ResourceManager.h"
#include "SpaceGame.h"
#include "Bullet.h"
#include "Assets.h"
#include "Player.h"


#include <memory>

using namespace assets;
using namespace nu;

void Player::Update(float dt){
    float thrust = 0.0f;
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_W)) thrust = m_speed;
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_S)) thrust = -m_speed;

    float rotate = 0.0f;
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_A)) rotate = -180.0f;
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_D)) rotate = +180.0f;

    SetRotation(m_transform.rotation + rotate * dt);

    nu::Vector2 forward{ 1.0f,0.0f };
    nu::Vector2 velocity = forward.Rotate((DegToRad * m_transform.rotation)) * thrust;

    AddVelocity(velocity * dt);
 
        //particle system
    if (Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_W)) {
        nu::Particle particle;
        particle.position = m_transform.position;
        particle.color = { 1.0f, 1.0f, 1.0f };
        particle.lifespan = RandomFloat(0.5f, 1.5f);
        particle.velocity = { RandomFloat(-200.0f, 200.0f), RandomFloat(-200.0f, 200.0f) };

   
        Engine::Get().GetPS().AddParticle(particle);
    }

    //fire
    if (nu::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE)) {
        Engine::Get().GetAudio().PlaySound("laser");
        BulletDesc desc;
        desc.name = "PlayerBullet";
        desc.tag = "PlayerBullet";
        //desc.model = bulletModel;
        desc.texture = Resources().Get<Texture>("textures/bullet.png", Engine::Get().GetRenderer());
        desc.transform = Transform{ m_transform.position, m_transform.rotation, 1.0f };
        desc.speed = 1000.0f;
        desc.lifespan = 3.0f;

        unique_ptr<Bullet> bullet = make_unique<Bullet>(desc);
        m_scene->AddActor(move(bullet));
    };

    Actor::Update(dt);
}



void Player::OnCollision(Actor* other) {

    Color color1 = { 1.0f, 1.0f, 1.0f };
    Color color2 = { 0.0f, 1.0f, 1.0f };
    Color color3 = { 1.0f, 0.0f, 1.0f };


    if (other->GetName() == "Enemy") {
        SetDestroyed();
        ((SpaceGame*)m_scene->GetGame())->OnPlayerDead();

        for (int i = 0; i < 100; i++)
        {
            nu::Particle particle;
            particle.position = m_transform.position;
            int randomInt = RandomInt(0, 3);
            switch (randomInt) {
            case 0:
                particle.color = color1;
                break;
            case 1:
                particle.color = color2;
                break;
            case 2:
                particle.color = color3;
                break;
            default:
                particle.color = color1;
                break;
            }
            particle.lifespan = nu::RandomFloat(0.5f, 2.0f);
            particle.velocity = { nu::RandomFloat(-600.0f, 600.0f), nu::RandomFloat(-600.0f, 600.0f) };

            nu::Engine::Get().GetPS().AddParticle(particle);
        }
    }
    
}
