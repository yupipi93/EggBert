#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include <Level.h>
#include <Map.h>
#include <Player.h>


class Game
{
    public:
        Game(sf::Vector2i resolution, std::string title);

    protected:

    private:
        void loadImages();
        void gameLoop();
        void loadNewLevel();
        //Create Window
        sf::RenderWindow * window;
        sf::Clock * globalClock;
        sf::Clock * updateGlobalClock;


        sf::Time timeElapsed;

        Level *level;
        Player *player;
        //Map *scene;

        float fps;
        int numLvl;

};

#endif // GAME_H
