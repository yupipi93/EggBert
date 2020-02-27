#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
class Map;
#include <Map.h>
#include <iostream>
using namespace std;


class Player
{
    public:
        Player();
        void init(int numMap);
        int getGridPosition();
        int getGridPositionCustom();
        int getGridPositionLast();
        int getGridPositionKey();
        int getMapTileTipe(int pos);
        int getMapTileTipeAction(int pos);
        void setToGridPosition(int pos);
        void returnToLastY(float posY);
        void returnToLastXLeft(float posX);
        void returnToLastXRight(float posX);
        void update(double velocidad, double timeElapsed);
        sf::Vector2f getLastPosition();
        sf::Vector2f getNextPosition();
        sf::Sprite* getPlayerSprite();

        int updateKeysCollection();
        int whoObjectIsHere();
        void setAlive(bool alive);
        bool getAlive();

        void startWalking(bool left);
        void stopWalking();
        void setOnGrownd(bool on);
        void startUp();
        void stopUp();
        void startDown();
        void stopDown();

        void walkingAnimation();
        void upAnimation();

        bool isEmptyTile();
        bool isEmptyDownTile();
        bool isEmptyCustomTile(int pos);
        bool getLeft();
        bool isStairs(int dir);
        void setTransparente(bool trans);
        bool getTransparente();

    private:


        void takePlayerSprite(int pos);
        sf::Texture *texturePlayer;
        sf::Sprite *spritePlayer;

        float lastX;
        float nextX;

        float lastY;
        float nextY;

        bool dead, walking, left, onGrownd, up, down, blockLeft, blockRight, transparente;
        int gridPos, step,haveKeys;

};

#endif // PLAYER_H
