#include "../Engine/Engine.h"
#include "Assets.h"

namespace assets {
	Mesh playerMesh1{ {{ 0, -1 }, { 1, 0 }, { 0, 1 }, { 3, 0 }, { 0, -1 } }, { 0.694f, 0.0f, 1.0f } };
	Mesh playerMesh2{ {{ 0, -1 }, { -1, -2 }, { -3, 0 }, { -1, 2 }, { 0, 1 }}, {1.0f, 0.902f, 0.38f} };
	Mesh playerMesh3{ {{ -1, -1 }, { 0, 0 }, { -1, 1 }, { -2, 0 }, { -1, -1 }}, {0.53f, 1.0f, 0.7f} };
	Model playerModel = vector<Mesh>{ playerMesh1, playerMesh2, playerMesh3 };

	Mesh enemyMesh{ {{ 0, -1 }, { 1, 0 }, { 0, 1 }, { 3, 0 }, { 0, -1 } }, { 1.0f, 0.0f, 0.0f } };

	Model enemyModel = vector<Mesh>{ enemyMesh };


	Mesh bulletMesh{
		{
		  Vector2{ -1, -1 },
		  Vector2{ 1, 0 },
		  Vector2{ -1, 1 },
		  Vector2{ -1, -1 },
		},
		Color{ 0.0f, 1.0f, 1.0f }
	};

	Model bulletModel(vector<Mesh>{bulletMesh});
}