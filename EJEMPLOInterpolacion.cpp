#include <SFML/Graphics.hpp>
#include <iostream>

#define UPDATE_TICK_TIME (1000/15) // ~67
#define WIDTH 900
#define HEIGHT 600

using namespace std;

int main()
{
// Create the main window
    sf::RenderWindow app(sf::VideoMode(WIDTH, HEIGHT), "EggBert");
    app.setFramerateLimit(60);

    sf::Clock clock;
    sf::Clock updateClock;
    sf::Time timeElapsed;
    double newX = 0, lastX = 0, posY = 250;
    double velX = 0.001;


    loadImage();

// Load a sprite to display
    sf::Texture texture;
    if (!texture.loadFromFile("cb.bmp"))
        return EXIT_FAILURE;
    sf::Sprite sprite(texture);

    sprite.setOrigin(texture.getSize().x/2, texture.getSize().y/2);


    bool firstTime = true;

// Start the game loop
    while (app.isOpen())
    {
// Process events
        sf::Event event;
        while (app.pollEvent(event))
        {
// Close window : exit
            if (event.type == sf::Event::Closed)
                app.close();

        }

        if (updateClock.getElapsedTime().asMilliseconds() >= UPDATE_TICK_TIME)
        {
            lastX = newX;
            timeElapsed = updateClock.restart();
            cout << "UPDATE - " << timeElapsed.asMilliseconds() << endl;
            newX += velX * (double)timeElapsed.asMicroseconds();
            if (newX > WIDTH - sprite.getOrigin().x/2 || newX < 0)
                velX *= -1;
        }

        float percentTick = min(1.0, updateClock.getElapsedTime().asMilliseconds()/(double)UPDATE_TICK_TIME);

        //cout <<

        cout << "DRAW - " << updateClock.getElapsedTime().asMilliseconds() << " - " << (double)percentTick<< endl;

        int interX = lastX * (1-percentTick) + newX * percentTick;

        sprite.setPosition(interX, posY);
// Clear screen
        app.clear();
// Draw the sprite
        app.draw(sprite);
// Update the window
        app.display();
    }

    return EXIT_SUCCESS;
}
