#include "../Engine/Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "Assets.h"
#include "SpaceGame.h"

#include <SDL3/SDL.h>

#include <fmod.hpp>

#include <iostream>
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

int main(int argc, char* argv[])

{
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

    std::shared_ptr<Texture> texture = std::make_shared<Texture>();
    texture->Load("Textures/IAmPibble.jpg", Engine::Get().GetRenderer());
 
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
		Engine::Get().GetRenderer().DrawTexture(texture.get(), 0.0f, 0.0f);

        Engine::Get().GetPS().Draw(Engine::Get().GetRenderer());
        Engine::Get().GetRenderer().Present();
       
    }
    //SHUTDOWN

    Engine::Get().Shutdown();

    return 0;
}