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
#include <fstream>



using namespace nu;
using namespace std;

int main() {

    SetWorkingDirectory("Assets");

    Factory::Instance().Register<Actor>("Actor");
    Factory::Instance().Register<Object>("Object");
    Factory::Instance().Register<Player>("Player");

    auto actor = Factory::Instance().Create<Actor>("Actor");
    cout << actor->IsActive() << endl;

    auto object = Factory::Instance().Create("Object");
    cout << object->IsActive() << endl;

    auto player = Factory::Instance().Create<Player>("Player");
    cout << player->IsActive() << endl;


    json::document_t document;
    if (json::Load("Data/scene.json", document)) {
        player->Read(document);
        cout << player->GetName() << endl;
        cout << player->GetTag() << endl;
        cout << player->GetTransform().rotation << endl;
        cout << player->GetSpeed() << endl;
        cout << player->IsActive() << endl;

    }

    return 0;

    //INITALIZE
    Engine::Get().Initialize();

    SpaceGame game;
    game.Initialize();
    // load the json data from a file
    string buffer;
    if (ReadTextFile("data/data.json", buffer))
    {
        // show the contents of the json file (debug)
        cout << buffer << endl;

        // create json document from the json file contents
        rapidjson::Document document;

        if (json::Load("data/data.json", document))
        {
            // read/show the data from the json file
            string name;
            int age;
            float speed;
            bool isAwake;
            Vector2 position;
            Vector3 color;

            // read the json data
            JSON_READ(document, name);
            JSON_READ(document, age);
            JSON_READ(document, speed);
            JSON_READ(document, isAwake);
            JSON_READ(document, position);
            JSON_READ(document, color);

            // show the data
            cout << "Name: " << name << endl;
            cout << "Age: " << age << endl;
            cout << "Speed: " << speed << endl;
            cout << "Awake? " << isAwake << endl;
            cout << "Position: " << position.x << ", " << position.y << endl;
            cout << "Color: (" << color.r << ", " << color.g << ", " << color.b << ")" << endl;
        }
    }

 
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
        Engine::Get().GetPS().Draw(Engine::Get().GetRenderer());
		

        Engine::Get().GetRenderer().Present();
       
    }
    //SHUTDOWN

    Engine::Get().Shutdown();

    return 0;
}