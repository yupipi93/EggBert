#include "Player.h"
#define FACTOR 0.92

Player::Player()
{
    texturePlayer = new sf::Texture;
    spritePlayer = new sf::Sprite;
    haveKeys = 0;
    dead    = false;
    walking = false;
    left    = true;
    onGrownd = false;
    up = false;
    down = false;
    blockLeft = false;
    blockRight = false;
    step = 0;
    transparente = false;

    texturePlayer->loadFromFile("img/players_64x50.png");

}


void Player::init(int numMap){
    cout << "Creando Jugaor en el level: " << numMap << endl;
    haveKeys = 0;
    dead    = false;
    walking = false;
    left    = true;
    onGrownd = false;
    up = false;
    down = false;
    blockLeft = false;
    blockRight = false;
    step = 0;
    takePlayerSprite(8);//sprite inicial
    if(numMap == 1){
        setToGridPosition(72);//spawn
    }else if(numMap == 2){
        setToGridPosition(58);//spawn
    }else if(numMap == 3){
        setToGridPosition(126);//spawn
    }else if(numMap == 4){
        setToGridPosition(18);//spawn
    }else{
        cout << "Personaje no implementado para el mapa: " << numMap << endl;
    }


}

void Player::setAlive(bool alive){
    dead = !alive;
}
bool Player::getAlive(){
    return !dead;
}

///si la resolucion es 1024x768 y hay un grid de 16*12 cada casilla es de 64.
///dividimos lastX/64 mas 1 porque no empieza en 0 + (lastY/64)*16
int Player::getGridPosition(){
    int posx = nextX/64;
    int posy = nextY/64;
    int gridPos = posx+posy*16;
    return gridPos+1;

}
int Player::getGridPositionCustom(){
    int posx = lastX/64;
    int posy = lastY/64;
    int gridPos = posx+posy*16;
    return gridPos+1;

}


int Player::getGridPositionLast(){
    //Ese - 10 es para parchear el fallo que hay con el origen
    //cuando andas a la izquierda y detectas la siguiente posocion
    int posx = (lastX-10)/64;
    int posy = lastY/64;
    int gridPos = posx+posy*16;
    return gridPos+1;

}

int Player::getGridPositionKey(){
    int posx = (lastX+10)/64;
    int posy = lastY/64;
    int gridPos = posx+posy*16;
    return gridPos;
}

int Player::getMapTileTipe(int pos){
    int ret;
    ret = Map::Instance()->allocation(pos);
    return ret;
}

int Player::getMapTileTipeAction(int pos){
    return Map::Instance()->getModificableMap(pos);
}

void Player::setToGridPosition(int pos){
        int x = 0;
        int y = 0;
    if(pos>=0){//no devolver nada
        x = pos;
        y = 0;

        // de 0 a 16 si es mas de 16 estamos en otra fila
        if(pos >= 17){
            x = pos%16;
            y = pos/16;
        }


        x=64*(x-1);//le sumo la x porque hay una separacion entre tiles de 1 pixel
        y=64*y+3;
    }

    lastX = nextX = x;
    lastY = nextY = y;


}

void Player::returnToLastY(float posY){
    lastY = nextY = (posY-64)+1;
}

void Player::returnToLastXLeft(float posX){
    lastX = nextX = (posX);
    blockLeft = true;
}
void Player::returnToLastXRight(float posX){
    lastX = nextX = (posX);
    //blockRight = true;
}


bool Player::isEmptyTile(){
    int pos= 0;;
    if(left)
        pos = -1;

    bool ret = false;
    int notCollideable[] = {-1};//esto deverias ser variable global o cojerla de mapa

    for(int i = 0; i < sizeof(notCollideable)/sizeof(notCollideable[0]); i++){
        if(pos == 0){
            if((getMapTileTipe(getGridPositionLast()+pos) == notCollideable[i])){
                ret = true;
            }
        }else{
            if((getMapTileTipe(getGridPosition()+pos) == notCollideable[i])){
                ret = true;
            }
        }
    }

    return ret;//soy subnormal y lo envio alreves
}

bool Player::isEmptyDownTile(){
    bool ret = false;
    int pos= 0;
    if(left)
        pos = -2;

        if(( getMapTileTipe((getGridPosition()+pos)+16) == -1)){
            cout << "true" << endl;
            ret = true;
        }

    return ret;//soy subnormal y lo envio alreves
}

bool Player::isEmptyCustomTile(int pos){
    bool ret = false;

        if( getMapTileTipe(getGridPositionCustom()+pos) == -1){
            cout << "true" << endl;
            ret = true;
        }


    return ret;//soy subnormal y lo envio alreves
}

bool Player::getLeft(){
    return left;
}


bool Player::isStairs(int dir){
    dir--;
    bool ret = false;
    int notCollideable[] = {23};//esto deverias ser variable global o cojerla de mapa

    for(int i = 0; i < sizeof(notCollideable)/sizeof(notCollideable[0]); i++){
        if((getMapTileTipeAction(getGridPosition()+dir) == notCollideable[i])){
            ret = true;
        }
    }

    int pene = getMapTileTipe(getGridPosition()+dir);
    return ret;
}



void Player::update(double velocidad, double timeElapsed){
    lastX = nextX;
    lastY = nextY;


    if(walking && onGrownd){
        if(left && isEmptyTile() && !blockLeft){
            nextX -= velocidad * timeElapsed;
            blockRight = false;

        }
        if(!left && isEmptyTile() && onGrownd){
            nextX += velocidad * timeElapsed;
            blockLeft = false;
        }

    }

    if(!onGrownd){
            nextY += (velocidad * timeElapsed);
            blockLeft = blockRight = false;
    }

     if(up && (isStairs(0) || isStairs(16)) ){
            nextY -= (velocidad * timeElapsed);
            blockLeft = blockRight = false;
    }
      if(down && isStairs(16)){
            nextY += (velocidad * timeElapsed);
            blockLeft = blockRight = false;
    }






}

int Player::updateKeysCollection(){

    //esto me decuelve el objeto decorativo en el que estoy encima
    return whoObjectIsHere();
}

int Player::whoObjectIsHere(){
    return getMapTileTipeAction(getGridPositionKey());
}


void Player::startWalking(bool isLeft)
{
    if (!dead)
    {
        walking = true;
        left = isLeft;
    }
}

void Player::stopWalking()
{
    walking = false;
}



void Player::startUp()
{
    if (!dead)
        up = true;
}

void Player::stopUp()
{
    up = false;
}

void Player::startDown()
{
    if (!dead)
        down = true;
}

void Player::stopDown()
{
    down = false;
}



void Player::setOnGrownd(bool on){
    onGrownd = on;
}



sf::Vector2f Player::getLastPosition(){
    sf::Vector2f ret (lastX,lastY);
    return ret;
}

sf::Vector2f Player::getNextPosition(){
    sf::Vector2f ret (nextX,nextY);
    return ret;
}
void Player::setTransparente(bool trans){
    transparente = trans;
}

bool Player::getTransparente(){
    return transparente;
}


 sf::Sprite* Player::getPlayerSprite(){
     if(!transparente){

         if(dead){
            takePlayerSprite(2);//Muerto
         }else{
            takePlayerSprite(8);
            if(!up && !down && !walking)
                step = 0;
            if( (up && (isStairs(0) || isStairs(16))) || (down && isStairs(16)) ){
                upAnimation();
            }
            else if(walking){
                walkingAnimation();
                if(left){
                    spritePlayer->setOrigin(50/2,64/2);
                    spritePlayer->setScale(-1.f, 1.f);
                    spritePlayer->setOrigin(50,0);
                }else{
                    spritePlayer->setOrigin(50/2,64/2);
                    spritePlayer->setScale(1.f, 1.f);
                    spritePlayer->setOrigin(0,0);

                }

            }
        }
     }

    return spritePlayer;
 }

 void Player::upAnimation(){
    int rect= 10;
        if(step<=10){
            rect = 6;
        }


        if(step > 20)//dos pasos
            step=0;

        step++;

    takePlayerSprite(rect);
 }

 void Player::walkingAnimation(){
    int rect= 8;
        if(step<=10){
            rect = 5;
        }else
         if(step<=20){
            rect = 3;
        }else
         if(step<=30){
            rect = 9;
        }else
         if(step<=40){
            rect = 1;
        }

        if(step > 50)//dos pasos
            step=0;
        step++;

    takePlayerSprite(rect);


 }



void Player::takePlayerSprite(int pos){
    sf::IntRect rect;
    //sf::Sprite *sprite = new sf::Sprite;

    if(pos!=-1){//no devolver nada
        int x = pos;
        int y = 0;

        // de 0 a 11 si es mas de 11 estamos en otra fila
        if(pos >= 4){
            x = pos%4;
            y = pos/4;
        }


        x=50*x+x;//le sumo la x porque hay una separacion entre tiles de 1 pixel
        y=64*y+y;


        rect = sf::IntRect(x,y,50,64);
        spritePlayer->setTexture(*texturePlayer);
        spritePlayer->setTextureRect(rect);


    }


}
