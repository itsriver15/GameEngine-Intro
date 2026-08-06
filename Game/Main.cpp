#include "../Engine/Engine.h"
#include "../Engine/ResourceManager.h"
#include "Player.h"
#include "Enemy.h"
#include "Assets.h"
#include "SpaceGame.h"

#include <SDL3/SDL.h>

#include <fmod.hpp>

#include <iostream>
#include <random>
#include <vector>
#include <map>

using namespace nu;
using namespace std;

class Object {
public:
    Object() { cout << "constructor" << endl; }
	~Object() { cout << "destructor" << endl; }
    Object(const Object& other) { cout << "copy constructor" << endl; }
	Object& operator = (const Object& object) { cout << "assignment" << endl; return *this; }
};
uint32_t seed = 1234;
uint32_t RNG() {
    seed = (seed * 1103515245) + 12345;
    return seed;
}

int main(int argc, char* argv[]) {
    for (size_t i = 0; i < 10; i++) { cout << RNG() << " "; }
    cout << endl;

    seed = 1234;
    for (size_t i = 0; i < 10; i++) { cout << RNG() << " "; }
    cout << endl;

    //srand((unsigned int)time(NULL));
    SeedRandom((unsigned int)time(NULL));
    for (size_t i = 0; i < 10; i++) { cout << rand() << " "; }
    cout << endl;

    //<random>
    random_device randomDevice;
    cout << randomDevice.min() << endl;
    cout << randomDevice.max() << endl;
    cout << randomDevice.entropy() << endl;

    mt19937 generator(randomDevice());
    
    uniform_int_distribution<> dist(0, 20);

    for (size_t i = 0; i < 10; i++) { cout << dist(generator) << " "; }
    cout << endl;

    uniform_real_distribution<float> distReal(-10.0f, 20.0f);
    for (size_t i = 0; i < 10; i++) { cout << distReal(generator) << " "; }
    cout << endl;


    return 0;


	cout << "+++++++++Object+++++++++" << endl;
    {
        Object objectA;
        Object objectB(objectA);
        Object objectC;
        objectC = objectA;
    }
	cout << "+++++++++Shared Pointers+++++++++" << endl;
    shared_ptr<Object> objectC;
    {
        auto objectA = make_shared<Object>();
        cout << objectA.get() << endl;
		cout << objectA.use_count() << endl;
		auto objectB = objectA;
        cout << objectB.get() << endl;
        cout << objectB.use_count() << endl;
        objectC = objectA;
        cout << objectC.get() << endl;
        cout << objectC.use_count() << endl;
    }
    cout << objectC.use_count() << endl;

    SetWorkingDirectory("Assets");

    //INITALIZE
    Engine::Get().Initialize();

    SpaceGame game;
    game.Initialize();

    //std::shared_ptr<Texture> texture = std::make_shared<Texture>();
    //texture->Load("Textures/ship.png", Engine::Get().GetRenderer());
 
    //MAIN LOOP
    bool quit = false;
    while (!quit)
    {
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
                quit = true;

            if (event.type == SDL_EVENT_KEY_DOWN &&
                event.key.scancode == SDL_SCANCODE_ESCAPE)
                quit = true;
        }
        //UPDATE
        //ENGINE
        Engine::Get().Update();

        float dt = Engine::Get().GetTime().GetDeltaTime();

        //GAME
        game.Update(dt);
        Engine::Get().GetPS().Update(Engine::Get().GetTime().GetDeltaTime());


        //RENDER
        Engine::Get().GetRenderer().SetColor(0.0f, 0.0f, 0.0f);
        Engine::Get().GetRenderer().Clear();

        game.Draw(Engine::Get().GetRenderer());
		Engine::Get().GetRenderer().DrawTexture(*Resources().Get<Texture>("Textures/ship.png", Engine::Get().GetRenderer()), 0.0f, 0.0f);

        Engine::Get().GetPS().Draw(Engine::Get().GetRenderer());
        Engine::Get().GetRenderer().Present();
       
    }
    //SHUTDOWN

    Engine::Get().Shutdown();

    return 0;
}