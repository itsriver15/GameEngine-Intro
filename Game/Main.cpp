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

int main(int argc, char* argv[]) {


    SetWorkingDirectory("Assets");

    {
        //read file - input file
        ifstream file("Data/text.txt");
        if (file.is_open()) {
            string str;

            while (std::getline(file, str)){
                cout << str << endl;
            }
        }
        else {
            cout << "Could not load file" << endl;
        }
        file.close();
    }
  

    {
        //write file -  output file
        ofstream file("Data/text.txt", std::ios::app);
        if (file.is_open()) {
            file << "Now he has a scratch! \n";

        }
    }

    {
        // read / write (input / output)
        fstream file("Data/text.txt", ios::in | ios::out | std::ios::app);
        if (file.is_open()) {
            //input
            file << "An added line across his cheek...\n";
            //output
            file.seekg(0);
            std::string str;
            while (std::getline(file, str)) {
                cout << str << endl;
            }

        }

    }

    {
        string name;
        int score;
        bool isAlive;

        bool save = true;

        if (save) {
            name = "River A. Cantrell";
            score = 1234;
            isAlive = true;
        }
        //save game data
        ofstream file("Data/game.txt", ios::trunc);
        if (file.is_open()) {
            file << name << "\n";
            file << score << "\n";
            file << std::boolalpha << isAlive << "\n";

        }
        //load game data
        bool load = true;
        if (load) {
            ifstream file("Data/game.txt");
            if (file.is_open()) {
                file >> name;
                file >> score;
                file >> std::boolalpha >> isAlive;

            }
        }
        //display game data
        cout << name << endl;
        cout << score << endl;
        cout << boolalpha << isAlive << endl;
    }


    return 0;

    //INITALIZE
    Engine::Get().Initialize();

    SpaceGame game;
    game.Initialize();
 
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