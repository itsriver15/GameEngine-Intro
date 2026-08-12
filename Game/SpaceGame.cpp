#include "SpaceGame.h"
#include "..\Engine\Engine.h"
#include "..\Engine\ResourceManager.h"
#include "Player.h"
#include "Assets.h"
#include "Enemy.h"
#include <memory>


bool SpaceGame::Initialize()
{
	Game::Initialize();
	m_scene = new Scene();
	m_scene->SetGame(this);

	m_titleText = new Text(Resources().GetWithID<Font>("title_font", "8-bit-limit/8bitlim.ttf", 100.0f));
	m_titleText->Create(Engine::Get().GetRenderer(), "Shoot Em Space", Color{ 1.0f, 1.0f, 1.0f });

	m_gameOverText = new Text(Resources().GetWithID<Font>("title_font", "8-bit-limit/8bitlim.ttf", 100.0f));
	m_gameOverText->Create(Engine::Get().GetRenderer(), "Game Over", Color{ 1.0f, 0.0f, 0.0f });

	m_scoreText = new Text(Resources().GetWithID<Font>("game_font","8-bit-limit/8bitlim.ttf", 50.0f));
	m_livesText = new Text(Resources().GetWithID<Font>("game_font", "8-bit-limit/8bitlim.ttf", 50.0f));


	

	Engine::Get().GetAudio().AddSound("laser", "Audio/laser.wav");
	Engine::Get().GetAudio().AddSound("explosion", "Audio/explosion.wav");

	return false;
}

void SpaceGame::Update(float dt)
{
	switch (m_gameState) {
	case GameState::Title:
		if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE)) {
			m_gameState = GameState::StartGame;
		}
			break;
	case GameState::StartGame:
		m_score = 0;
		m_lives = 3;
		m_spawnTime = 3.0f;
		m_gameState = GameState::StartLevel;
		break;
	case GameState::StartLevel:
		m_scene->RemoveAllActors();
		SpawnPlayer();
	m_gameState = GameState::Game;
		break;
	case GameState::Game:
		m_spawnTimer -= dt;
		if (m_spawnTimer <= 0.0f) {
			m_spawnTimer = m_spawnTime;
			SpawnEnemy();
			
		}
		break;
	case GameState::GameOver:
		m_scene->RemoveAllActors();
		if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_RETURN)) {
			m_gameState = GameState::Title;
		}
		break;
	default:
		break;
	}
	Game::Update(dt);

}

void SpaceGame::Draw(Renderer& renderer)
{
	renderer.DrawTexture(*Resources().Get<Texture>("textures/background.jpg", Engine::Get().GetRenderer()), 600.0f, 500.0f, 0.0f, 1.0f);

	switch (m_gameState) {
	case GameState::Title:
		//draw title
		m_titleText->Draw(renderer, 325.0f, 400.0f);
		break;
	case GameState::StartGame:
		break;
	case GameState::StartLevel:
		break;
	case GameState::Game:
		//draw score / lives
		m_scoreText->Create(renderer, "Score - " + to_string(m_score), { 1.0f, 1.0f, 1.0f });
		m_livesText->Create(renderer, "Lives - " + to_string(m_lives), { 1.0f, 1.0f, 1.0f });
		m_scoreText->Draw(renderer, 30.0f, 30.0f);
		m_livesText->Draw(renderer, 30.0f, 80.0f);
		break;
	case GameState::GameOver:
		m_gameOverText->Draw(renderer, 450.0f, 400.0f);
		m_scoreText->Draw(renderer, 550.0f, 500.0f);
		//draw game over
		break;
	default:
		break;
	}
	Game::Draw(renderer);
}

void SpaceGame::OnPlayerDead()
{
	Engine::Get().GetAudio().PlaySound("explosion");
	m_lives--;
	if (m_lives == 0) m_gameState = GameState::GameOver;
	else m_gameState = GameState::StartLevel;

}

void SpaceGame::SpawnPlayer()
{
	PlayerDesc playerDesc;
	playerDesc.name = "Player";
	//playerDesc.model = assets::playerModel;
	playerDesc.texture = Resources().Get<Texture>("textures/ship.png", Engine::Get().GetRenderer());
	playerDesc.transform = Transform{ Vector2 {640.0f, 512.0f}, 0.0f, 1.0f };
	playerDesc.damping = 3.0f;
	playerDesc.speed = 2000.0f;

	unique_ptr<Player> player = make_unique<Player>(playerDesc);
	m_scene->AddActor(move(player));

}

void SpaceGame::SpawnEnemy()
{
	EnemyDesc enemyDesc;
	enemyDesc.name = "Enemy";
	//enemyDesc.model = assets::enemyModel;
	enemyDesc.texture = Resources().Get<Texture>("textures/enemy.png", Engine::Get().GetRenderer());
	enemyDesc.transform = Transform{ Vector2{ nu::RandomFloat((float)Engine::Get().GetRenderer().GetWidth()), RandomFloat((float)Engine::Get().GetRenderer().GetHeight())}, 90.0f, 2.0f };
	enemyDesc.damping = 3.0f;
	enemyDesc.speed = 2000.0f;

	unique_ptr<Enemy> enemy = make_unique<Enemy>(enemyDesc);
	m_scene->AddActor(move(enemy));
}
