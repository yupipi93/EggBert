#include "Game.h"
#include <iostream>


#include<stdio.h>
using namespace std;

#define UPDATE_TICK_TIME (1000/15)


Game::Game(sf::Vector2i resolution, std::string title)
{
    numLvl = 1;

    fps = 60.f;
    globalClock = new sf::Clock;
    updateGlobalClock = new sf::Clock;
    timeElapsed = sf::Time();


    player = new Player();
    level = new Level(player);


    window = new sf::RenderWindow(sf::VideoMode(resolution.x, resolution.y),title);
    window->setFramerateLimit(fps);


    // Load a sprite an init
    player->init(numLvl);
    level->loadLevel(numLvl);
    Map::Instance()->loadMap(level,numLvl);



    // Start the game loop
    gameLoop();



}



void Game::gameLoop(){

  bool firstTime = true;
    while (window->isOpen())
    {
        window->setVerticalSyncEnabled(true);

// Process events
        sf::Event event;
        while (window->pollEvent(event))
        {
// Close window : exit
            if (event.type == sf::Event::Closed)
                window->close();

        }

        if (updateGlobalClock->getElapsedTime().asMilliseconds() >= UPDATE_TICK_TIME)
        {
            //UPDATE
            timeElapsed = updateGlobalClock->restart();
            if(!level->getResetLevel()){
                level->updateLevel((double)timeElapsed.asMicroseconds());
                if( level->isLevelComplete() ){
                    numLvl++;
                    if(numLvl >=5){
                        numLvl = 1;
                    }
                    loadNewLevel();
                }
            }else{
                level->eraseLevel();
                player->init(numLvl);
                level->loadLevel(numLvl);
                Map::Instance()->loadMap(level,numLvl);
                level->setResetLevel(false);
            }

             if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
                window->close();
            }



        }


        // Draw the sprite
        float percentTick = min(1.0, updateGlobalClock->getElapsedTime().asMilliseconds()/(double)UPDATE_TICK_TIME);
        level->drawLevel(window, percentTick);


    }


}

    void Game::loadNewLevel(){
        level->eraseLevel();
        player->init(numLvl);
        level->loadLevel(numLvl);
        Map::Instance()->loadMap(level,numLvl);
    }









