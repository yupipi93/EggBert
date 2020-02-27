#ifndef LEVEL_H
#define LEVEL_H
#include <SFML/Graphics.hpp>


#include <vector>
class Player;
#include <Player.h>
#include <sstream>

#include <iostream>
using namespace std;




class Level
{
    public:
        Level(Player *player);
        void loadLevel(int numLvl);

        void loadUI(int numLvl);

        void updateLevel( double timeElapsed);
        void drawLevel( sf::RenderWindow *window, float percentTick);

        int addSpriteMap(sf::Sprite *sprite);
        int addSpriteNotCollitionable(sf::Sprite *sprite);
        sf::Sprite* getSpriteMap(int numSprite);

        bool isLevelComplete();
        void eraseLevel();
        void updatePlayerAlive();
        bool getResetLevel();
        void setResetLevel(bool reset);
        string toString(int integer);


    protected:

    private:
        void handleEvents();
        void handleCottition();
        void handleCottitionActions();
        void updatePlayerKeys();
        void changeObjectSelected();
        void actionObject();
        void desmarcar();
        void loadEnemy(int numLvl);
        void updateEnemy(double timeElapsed);
        void updateUI();

        vector<sf::Sprite*> spritesUI;
        vector<sf::Sprite*> spriteMap;
        vector<sf::Sprite*> spriteMapDecor;
        vector<sf::Texture*> textures;

        vector<int> collideables;

        sf::Texture *tKeyboard;
        sf::Sprite *sKeyboard;


        sf::Font *font;
        sf::Text *keys;
        sf::Text *numOfKeysLeft;
        sf::Text *numBuid;
        sf::Text *numTp;
        sf::Text *numNothing;
        sf::Text *godModeText;
        sf::Text *pressSpaceText;

        sf::Texture *txBlack;
        sf::Sprite *sBlack;

        sf::Texture *tSelected;
        sf::Sprite * sSelected;


        sf::Texture *tEnemy;
        sf::Sprite * sEnemy;

        sf::Texture *tContruida;
        sf::Texture *tPosTPup;
        sf::Texture *tPosTPdown;
        sf::Texture *tPosTPright;
        sf::Texture *tPosTPleft;
        sf::Texture *tTransparente;

        Player *playerLevel;

        sf::Time timeElapsed;
        double newX,lastX,posY, velX, velocidad, lastXEnemy, nextXEnemy,velEnemyX;
        int numLevel,haveKeys,numOfKeys,selectedObj,currentLVL, delay,numBuidObj,numTpObj,minWidth,maxWidth;
        bool pressedA,pressedD,pressedW,pressedS, levelComplete,pressedSpace,resetLevel,pressedControl,blockMovement,godMode,showKeyboard;
        bool permitir[4];


    //sf::RenderWindow window = nullptr;
};

#endif // LEVEL_H
