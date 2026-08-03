#pragma once
#include "..\Engine\Game.h"
#include "..\Engine\Text.h"
using namespace nu;


class SpaceGame : public nu::Game {
public:
	enum class GameState {
		Title,
		StartGame,
		StartLevel,
		Game,
		GameOver
	};
public:
		SpaceGame() = default;
		SpaceGame(nu::Scene* scene) : nu::Game{ scene } {};
		bool Initialize() override;

		void Update(float dt) override;
		void Draw(Renderer& renderer) override;

		void OnPlayerDead();

		void AddPoints(int points) {
			m_score += points;
		};

	private:
		void SpawnPlayer();
		void SpawnEnemy();

	private:
		int m_score{ 0 };
		int m_lives{ 0 };

		float m_stateTimer = 0.0f;

		float m_spawnTimer = 0.0f;
		float m_spawnTime = 3.0f;

		GameState m_gameState = GameState::Title;

		Font* m_titleFont{ nullptr };
		Text* m_titleText{ nullptr };

		Font* m_gameOverFont{ nullptr };
		Text* m_gameOverText{ nullptr };

		Font* m_gameFont{ nullptr };

		Text* m_scoreText{ nullptr };
		Text* m_livesText{ nullptr };
};