#ifndef MAP_H
#define MAP_H
#include <SFML/Graphics.hpp>
class Level;
#include <Level.h>

#include <vector>
#include <iostream>
using namespace std;




class Map
{
    public:
        public:
        static Map* Instance();
        void loadMap(Level *level, int nMap);
        int allocation(int num);
        int allocationDecor(int num);
        int getModificableMap(int num);
       void deleteModificableMap(int num);

    protected:

    private:
       void rellenarModificableMap();

        static Map* instance;
        Map();

        sf::Sprite* loadBackGround();
        sf::Sprite* takeMapSprite(int pos);

        sf::Texture *textureMap;
        sf::Texture *backGround;

        int modificableMap[160];

        int numMap;




};

#endif // MAP_H
