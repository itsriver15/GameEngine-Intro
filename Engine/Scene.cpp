#include "pch.h"
#include "Scene.h"
#include "Actor.h"
#include "Renderer.h"

namespace nu {
	void Scene::AddActor(unique_ptr<Actor> actor){
		actor->m_scene = this;
		m_pendingActors.push_back(move(actor));

	}

	void Scene::RemoveAllActors()
	{
		m_actors.clear();
	}

	void Scene::Update(float dt) {
		//update actors
		for (auto& actor : m_actors) {
			actor->Update(dt);
		}
		//update collisions
		UpdateCollisions();

		//remove destroyed actors
		erase_if(m_actors, [](auto& actor) {return actor->m_destroyed; });


		//add pending actors
		for (auto& actor : m_pendingActors) {
			m_actors.push_back(std::move(actor));
		}

		m_pendingActors.clear();
	}

	void Scene::Draw(const class Renderer& renderer) {
		for (auto& actor : m_actors) {
			if (actor) actor->Draw(renderer);
		}
	}

	void Scene::UpdateCollisions(){
		for (auto& actorA : m_actors) {
			for (auto& actorB : m_actors) {
				if (actorA == actorB || actorA->m_destroyed || actorB->m_destroyed) {
					continue;
				}
				float distance = (actorA->m_transform.position - actorB->m_transform.position).Length();

				if (distance <= (actorA->GetRadius() + actorB->GetRadius())) {
					actorA->OnCollision(actorB.get());
					actorB->OnCollision(actorA.get());
				}
			}
		}
	}
};