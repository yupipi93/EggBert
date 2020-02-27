#include "Level.h"


#define velocidad 0.0002



Level::Level(Player *player)
{
    playerLevel = player;
    pressedA = false;
    pressedD = false;
    pressedW = false;
    pressedS = false;
    pressedSpace = false;
    pressedControl = false;
    levelComplete = false;
    resetLevel = false;
    blockMovement = false;
    godMode = false;
    showKeyboard = true;
    selectedObj = 1;
    currentLVL = 1;
    delay = 0;
    permitir[0] = false; permitir[1] = false; permitir[2] = false; permitir[3] = false;

    txBlack = new sf::Texture;
    sBlack = new sf::Sprite;

    tEnemy = new sf::Texture;
    sEnemy = new sf::Sprite;

    txBlack->loadFromFile("img/black.png");
    sBlack->setTexture(*txBlack);
    sBlack->setPosition(0,640);



    tKeyboard = new sf::Texture;
    sKeyboard = new sf::Sprite;

    tKeyboard->loadFromFile("img/keyboard.png");
    sKeyboard->setTexture(*tKeyboard);


}


void Level::loadLevel(int numLvl){
    currentLVL = numLvl;
    selectedObj=1;
    loadEnemy(currentLVL);
    levelComplete = false;
    haveKeys = 0;



    if(numLvl == 1){
        showKeyboard = true;
        numOfKeys = 5;//5
        numBuidObj = 0;
        numTpObj = 0;
    }else if(numLvl == 2){
        numOfKeys = 4;//4
        numBuidObj = 1;
        numTpObj = 0;
    }else if(numLvl == 3){
        numOfKeys = 4;//4
        numBuidObj = 0;
        numTpObj = 1;
    }else if(numLvl == 4){
        numOfKeys = 4;//4
        numBuidObj = 4;
        numTpObj = 4;
    }else{
        cout << "No implementado el level: " << numLvl << endl;
    }

    loadUI(numLvl);
}



void Level::loadEnemy(int numLvl){
    tEnemy->loadFromFile("img/enemy.png");
    sEnemy->setTexture(*tEnemy);
    if(numLvl == 1){
        sEnemy->setPosition(500,145);
        minWidth = 385;
        maxWidth = 590;
    }else if(numLvl == 2){
        sEnemy->setPosition(457,81);
        minWidth = 64;
        maxWidth = 850;
    }else if(numLvl == 3){
        sEnemy->setPosition(490,273);
        minWidth = 64;
        maxWidth = 915;
    }else if(numLvl == 4){
        sEnemy->setPosition(460,80);
        minWidth = 120;
        maxWidth = 650;

    }else{
        cout << "No implementado el enemido del nuvel: " << numLvl << endl;
    }
    lastXEnemy = nextXEnemy = sEnemy->getPosition().x;
    velEnemyX = velocidad;
}

void Level::updateEnemy(double timeElapsed){
    if(nextXEnemy > maxWidth || nextXEnemy < minWidth){
        velEnemyX *= -1;
    }



    lastXEnemy = nextXEnemy;
    nextXEnemy += velEnemyX * timeElapsed;


}


void Level::eraseLevel(){
        spriteMapDecor.clear();
        spriteMap.clear();
}


void Level::loadUI(int numLvl){
    spritesUI.clear();
    string rutas[3];

    if(numLvl == 1){
        rutas[0]="img/x.png";rutas[1]="img/x.png";rutas[2]="img/x.png";
    }else if(numLvl == 2){
        rutas[0]="img/contruir.png";rutas[1]="img/x.png";rutas[2]="img/x.png";
    }else if(numLvl == 3){
       rutas[0]="img/x.png";rutas[1]="img/tp.png";rutas[2]="img/x.png";
    }else if(numLvl == 4){
        rutas[0]="img/contruir.png";rutas[1]="img/tp.png";rutas[2]="img/x.png";
    }else{
        rutas[0]="img/x.png";rutas[1]="img/x.png";rutas[2]="img/x.png";
    }


    int posicionesX[] = {200,300,400};
    int posicionesY[] = {680,680,680};

    for(int i = 0; i < sizeof(rutas)/sizeof(rutas[0]); i++){

        textures.push_back(new sf::Texture);
        textures.at(i)->loadFromFile(rutas[i]);
        spritesUI.push_back(new sf::Sprite);
        spritesUI.at(i)->setTexture(*textures.at(i));
        spritesUI.at(i)->setOrigin(spritesUI.at(i)->getGlobalBounds().width/2, spritesUI.at(i)->getGlobalBounds().height/2);
        spritesUI.at(i)->setPosition(posicionesX[i],posicionesY[i]);
    }

    //Fondo negro
    tSelected = new sf::Texture;
    sSelected = new sf::Sprite;
    tSelected->loadFromFile("img/selected.png");
    sSelected->setTexture(*tSelected);
    sSelected->setOrigin(sSelected->getGlobalBounds().width/2,sSelected->getGlobalBounds().height/2);
    sSelected->setPosition(200,680);
    spritesUI.push_back(sSelected);//pos3

    //Caja Contruida
    tContruida = new sf::Texture;
    tContruida->loadFromFile("img/cajaMagica.png");

    tPosTPup = new sf::Texture;
    tPosTPup->loadFromFile("img/posTPup.png");

    tPosTPdown = new sf::Texture;
    tPosTPdown->loadFromFile("img/posTPdown.png");

    tPosTPright = new sf::Texture;
    tPosTPright->loadFromFile("img/posTPright.png");

    tPosTPleft = new sf::Texture;
    tPosTPleft->loadFromFile("img/posTPleft.png");

    tTransparente = new sf::Texture;
    tTransparente->loadFromFile("img/transparente.png");

    font = new sf::Font;
    font->loadFromFile("img/PressStart2P.ttf");

    keys = new sf::Text;
    keys->setFont(*font);
    keys->setCharacterSize(25);
    keys->setString("Keys left: ");
    keys->setPosition(490,660);


    numOfKeysLeft = new sf::Text;
    numOfKeysLeft->setFont(*font);
    numOfKeysLeft->setCharacterSize(25);
    numOfKeysLeft->setString(toString(numOfKeys-haveKeys));
    numOfKeysLeft->setPosition(780,660);


    numBuid = new sf::Text;
    numBuid->setFont(*font);
    numBuid->setCharacterSize(25);
    numBuid->setString(toString(numBuidObj));
    numBuid->setPosition(190,720);

    numTp = new sf::Text;
    numTp->setFont(*font);
    numTp->setCharacterSize(25);
    numTp->setString(toString(numTpObj));
    numTp->setPosition(290,720);

    numNothing = new sf::Text;
    numNothing->setFont(*font);
    numNothing->setCharacterSize(25);
    numNothing->setString("0");
    numNothing->setPosition(390,720);

    godModeText = new sf::Text;
    godModeText->setFont(*font);
    godModeText->setCharacterSize(25);
    godModeText->setString("");
    godModeText->setPosition(490,700);

    pressSpaceText = new sf::Text;
    pressSpaceText->setFont(*font);
    pressSpaceText->setCharacterSize(35);
    pressSpaceText->setString("");
    pressSpaceText->setPosition(150,300);



}

void Level::updateUI(){
    numOfKeysLeft->setString(toString(numOfKeys-haveKeys));
    numBuid->setString(toString(numBuidObj));
    numTp->setString(toString(numTpObj));
    if(godMode){
        godModeText->setString("!!! GodMode !!!");
    }else{
        godModeText->setString("");
    }

    if(!playerLevel->getAlive()){
        pressSpaceText->setString("Press SPACE to restart");
    }else{
        pressSpaceText->setString("");
    }
}

int Level::addSpriteMap(sf::Sprite *sprite){
    int ret = spriteMap.size();
    spriteMap.push_back(sprite);
    return ret;
}
int Level::addSpriteNotCollitionable(sf::Sprite *sprite){
    int ret = spriteMapDecor.size();
    spriteMapDecor.push_back(sprite);
    return ret;
}

sf::Sprite* Level::getSpriteMap(int numSprite){
    return spriteMap.at(numSprite);
}


void Level::updateLevel(double timeElapsed){


    handleEvents();
    if(playerLevel->getAlive()){
        handleCottition();
        handleCottitionActions();

        playerLevel->update(velocidad,timeElapsed);
        //Enemigo update
        updatePlayerAlive();
        updatePlayerKeys();
        actionObject();
        changeObjectSelected();
        updateEnemy(timeElapsed);
        updateUI();
        delay++;
    }else if(pressedSpace){
        resetLevel = true;

    }else{
        cout << "Press SPACE to reset Level" << endl;
    }



}
void Level::changeObjectSelected(){

    if(pressedControl && delay >= 4){
        if(selectedObj <= 2){
            selectedObj++;
            sSelected->setPosition(sSelected->getPosition().x+100,sSelected->getPosition().y);
        }else{
            selectedObj=1;
            sSelected->setPosition(200,sSelected->getPosition().y);
        }
        delay = 0;
    }

}

void Level::actionObject(){

    int dir = 1;
    if(playerLevel->getLeft()){
        dir = -1;
    }

    if(pressedSpace && delay >= 10){
        if(selectedObj == 1 && (currentLVL==2 || currentLVL==4) && numBuidObj>0){
            cout << "usando contruir" << endl;
            if( playerLevel->isEmptyDownTile() ){
                //añadir textura a la casilla vacia de delante + 1 fila(16)
                spriteMap.at((playerLevel->getGridPositionCustom()+dir)+16)->setTexture(*tContruida);
                numBuidObj--;
            }
        }else if(selectedObj == 2 && currentLVL>=3 && numTpObj>0){
            cout << "usando tp" << endl;

            if(playerLevel->isEmptyCustomTile(-33) && (playerLevel->getGridPositionCustom()-32)>= 0){
                 spriteMap.at(playerLevel->getGridPositionCustom()-32)->setTexture(*tPosTPup);
                 cout << "llega" << endl;
                 permitir[0] = true;
            }
              if(playerLevel->isEmptyCustomTile(33) && (playerLevel->getGridPositionCustom()+32)< spriteMap.size()){
                 spriteMap.at(playerLevel->getGridPositionCustom()+32)->setTexture(*tPosTPdown);
                 permitir[1] = true;
            }
             if(playerLevel->isEmptyCustomTile(1) && (playerLevel->getGridPositionCustom()+2)< spriteMap.size()){
                 spriteMap.at(playerLevel->getGridPositionCustom()+2)->setTexture(*tPosTPright);
                 permitir[2] = true;
            }
             if(playerLevel->isEmptyCustomTile(-3) && (playerLevel->getGridPositionCustom()-2)>= 0){
                 spriteMap.at(playerLevel->getGridPositionCustom()-2)->setTexture(*tPosTPleft);
                 permitir[3] = true;
            }

            if(permitir[0] || permitir[1] || permitir[2] || permitir[3]){
                cout << "desbanecer" << endl;
                blockMovement = true;
                playerLevel->setTransparente(true);
                godMode = true;
                playerLevel->getPlayerSprite()->setTexture(*tTransparente);

            }
            numTpObj--;


        }else if(selectedObj == 3){
            cout << "usando nada" << endl;
        }
        delay = 0;
    }

    if(playerLevel->getTransparente()){
        if(pressedW && permitir[0]){
            godMode = false;
            playerLevel->setTransparente(false);
            desmarcar();
            playerLevel->setToGridPosition(playerLevel->getGridPositionCustom()-32);
            playerLevel->getPlayerSprite();
        }else if(pressedS && permitir[1]){
            godMode = false;
            playerLevel->setTransparente(false);
            desmarcar();
            playerLevel->setToGridPosition(playerLevel->getGridPositionCustom()+32);
            playerLevel->getPlayerSprite();
        }else if(pressedD && permitir[2]){
            godMode = false;
            desmarcar();
            playerLevel->setToGridPosition(playerLevel->getGridPositionCustom()+2);
            playerLevel->setTransparente(false);
        }else if(pressedA && permitir[3]){
            godMode = false;
            playerLevel->setTransparente(false);
            desmarcar();
            playerLevel->setToGridPosition(playerLevel->getGridPositionCustom()-2);
            playerLevel->getPlayerSprite();
        }

    }


}

void Level::desmarcar(){
    sf::Sprite *s1 = new sf::Sprite;
    sf::Sprite *s2 = new sf::Sprite;
    sf::Sprite *s3 = new sf::Sprite;
    sf::Sprite *s4 = new sf::Sprite;
    if(permitir[0]){
        s1->setPosition(spriteMap.at(playerLevel->getGridPositionCustom()-32)->getPosition());
        spriteMap.at(playerLevel->getGridPositionCustom()-32) = s1;
    }
    if(permitir[1]){
        s2->setPosition(spriteMap.at(playerLevel->getGridPositionCustom()+32)->getPosition());
        spriteMap.at(playerLevel->getGridPositionCustom()+32) = s2;
    }
    if(permitir[2]){
        s3->setPosition(spriteMap.at(playerLevel->getGridPositionCustom()+2)->getPosition());
        spriteMap.at(playerLevel->getGridPositionCustom()+2) = s3;
    }
    if(permitir[3]){
        s4->setPosition(spriteMap.at(playerLevel->getGridPositionCustom()-2)->getPosition());
        spriteMap.at(playerLevel->getGridPositionCustom()-2) = s4;
    }
   permitir[0] = false; permitir[1] = false; permitir[2] = false; permitir[3] = false;
   blockMovement = false;

}


bool Level::getResetLevel(){
    return resetLevel;
}
void Level::setResetLevel(bool reset){
    resetLevel = reset;
}

void Level::updatePlayerAlive(){
int obj = playerLevel->whoObjectIsHere();
    if(obj==60||obj==68){
        playerLevel->setAlive(false);
    }
}

void Level::updatePlayerKeys(){
    if(haveKeys >= numOfKeys){
        cout << "Level Complete" << endl;
        levelComplete = true;
    }
    else if(playerLevel->updateKeysCollection()==29){//es una llave?
        haveKeys++;
        //borrar de registro
        Map::Instance()->deleteModificableMap(playerLevel->getGridPositionKey());
        //borrar de mundo
        sf::Sprite *s= new sf::Sprite;
        spriteMapDecor.at(playerLevel->getGridPositionKey())= s;//seguramente le falte un mas 1 a la pos
    }
}

bool Level::isLevelComplete(){
    return levelComplete;
}

void Level::handleEvents(){


    //KEYBOARD EVENT
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        if(!blockMovement){
            playerLevel->startWalking(false);
        }
        pressedD = true;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        playerLevel->startWalking(true);
        pressedA = true;
    }
    else{
        if(!blockMovement){
            playerLevel->stopWalking();
        }
        pressedA = false;
        pressedD = false;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        if(!blockMovement){
            playerLevel->startUp();
        }
        pressedW = true;
    }
    else{
        playerLevel->stopUp();
        pressedW = false;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        if(!blockMovement){
            playerLevel->startDown();
        }
        pressedS = true;
    }
    else{
        playerLevel->stopDown();
        pressedS = false;
    }

     if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        pressedSpace = true;
        showKeyboard = false;
    }
    else{
        pressedSpace = false;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::K)){
        playerLevel->setAlive(false);
    }

    if( (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::RControl)) ) {
        pressedControl = true;
    }else{
        pressedControl = false;
    }

    if( (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) && delay >= 10) {
        godMode = !godMode;
        delay = 0;
    }


}

void Level::handleCottition(){
    //Calculo las 5 posiciones con las que tengo que comprobar colisiones
    collideables.push_back(16);//Suelo
    collideables.push_back(17);//Suelo
    collideables.push_back(15);//Suelo


    bool onGround[] = {false,false,false};

    int initialPos = playerLevel->getGridPosition();//OK independiente del lvl


    for(int i = 0; i< 3; i++){
        if(playerLevel->getPlayerSprite()->getGlobalBounds().intersects( spriteMap.at(playerLevel->getGridPosition()+collideables.at(i))->getGlobalBounds()  )){
            onGround[i] = true;
        }else{
            onGround[i] = false;
        }

    }

    if(onGround[0]||onGround[1]||onGround[2]){
        //return to last position
        playerLevel->returnToLastY( spriteMap.at(initialPos+16)->getPosition().y );
        playerLevel->setOnGrownd(true);
    }else{

        playerLevel->setOnGrownd(false);
    }
     if(playerLevel->isStairs(0) || playerLevel->isStairs(16)){
         playerLevel->setOnGrownd(true);
    }





    if(pressedA){
         if(playerLevel->getPlayerSprite()->getGlobalBounds().intersects( spriteMap.at(playerLevel->getGridPosition()+0)->getGlobalBounds()  )){
            //playerLevel->stopWalking();
            playerLevel->returnToLastXLeft( spriteMap.at(initialPos+1)->getPosition().x );
        }
    }
    if(pressedD){
         if(playerLevel->getPlayerSprite()->getGlobalBounds().intersects( spriteMap.at(playerLevel->getGridPosition()+0)->getGlobalBounds()  )){
            //playerLevel->stopWalking();
            //playerLevel->returnToLastXRight( spriteMap.at(initialPos-1)->getPosition().x );
        }
    }


        if(playerLevel->getPlayerSprite()->getGlobalBounds().intersects( sEnemy->getGlobalBounds()) && !godMode){
            playerLevel->setAlive(false);
        }



}

void Level::handleCottitionActions(){
    if(playerLevel->getPlayerSprite()->getGlobalBounds().intersects( spriteMapDecor.at(playerLevel->getGridPosition()+15)->getGlobalBounds()  )){

    }else{

    }

}


void Level::drawLevel(sf::RenderWindow *window, float tick){

    //INTERPOLACION -->> pos = (lastX*Tick + newX*Tick),(lastY*Tick + newY*Tick)
    sf::Vector2f last = playerLevel->getLastPosition();
    sf::Vector2f next = playerLevel->getNextPosition();
    sf::Vector2f inter (last.x*(1-tick) + next.x*tick,  last.y*(1-tick) + next.y*tick);


    window->clear();



    //Dibujar Mapa
    for(int i = 0; i < spriteMap.size(); i++){
        window->draw(*spriteMap.at(i));
    }
    //Dibujar decoracion
     for(int i = 0; i < spriteMapDecor.size(); i++){
        window->draw(*spriteMapDecor.at(i));
    }





    //Black
    window->draw(*sBlack);


    //Dibujar UI
    for(int i = 0; i < spritesUI.size(); i++){
       window->draw(*spritesUI.at(i));
    }




    //Dibujar player
    sf::Sprite *spritePlayer = playerLevel->getPlayerSprite();
    if(playerLevel->getAlive()){
        spritePlayer->setPosition(inter);
    }
    window->draw(*spritePlayer);


    //Enemy
    int interXEnemy = lastXEnemy*(1-tick) + nextXEnemy*tick;
    if(playerLevel->getAlive()){
        sEnemy->setPosition(interXEnemy,sEnemy->getPosition().y);
    }
    window->draw(*sEnemy);



    window->draw(*keys);
    window->draw(*numOfKeysLeft);
    window->draw(*numBuid);
    window->draw(*numTp);
    window->draw(*numNothing);
    window->draw(*godModeText);
    window->draw(*pressSpaceText);



    if(showKeyboard){


        window->draw(*sKeyboard);

    }


    window->display();

}


	// Converts an int into a string
string Level::toString(int integer)
{
    ostringstream os;
    os << integer;
    return os.str();
}


