#pragma once

#include "Random.h"
#include "Vector2.h"
#include "MathUtils.h"
#include "Transform.h"

//systems
#include "Renderer.h"
#include "Input.h"
#include "GameTime.h"
#include "File.h"
#include "Audio.h"
#include "ParticleSystem.h"

#include "Text.h"

//framework
#include "Actor.h"
#include "Mesh.h"
#include "Scene.h"
#include "Game.h"

#include <iostream>
#include <vector>

namespace nu {
	class Engine {
	public:
		static Engine& Get() { static Engine engine; return engine; }

		bool Initialize();
		void Shutdown();

		void Update();

		Input& GetInput() { return m_input; }
		Renderer& GetRenderer() { return m_renderer; }

		Time& GetTime() { return m_time; }
		Audio& GetAudio() { return m_audio; }
		ParticleSystem& GetPS() { return m_particleSystem; }

	private:
		Engine() = default;
	protected:
		Audio m_audio;
		Input m_input;
		Renderer m_renderer;
		Time m_time;
		ParticleSystem m_particleSystem;
	};
	extern Engine engine;
}


