#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <SFML/System.hpp>
#include <ctime>

int main()
{
    const int width = 500, height = 500;
    sf::Event event;
    sf::RenderWindow window( sf::VideoMode(width,height), "SFML works!" );

    //sets view
    sf::View view2(sf::Vector2f(0.f, 0.f), sf::Vector2f(500.f, 500.f));
    window.setView(view2);

    //creates background
    sf::Texture backgroundClock;
    backgroundClock.loadFromFile("CLOCK.png");
    sf::RectangleShape background(sf::Vector2f(300, 300));
    background.setTexture(&backgroundClock);  

    //
    sf::Texture clockHandTexture;
    clockHandTexture.loadFromFile("clockHand.png");
    sf::RectangleShape clockHand(sf::Vector2f(8, 150));
    clockHand.setTexture(&clockHandTexture);
    //clockHand.setPosition(sf::Vector2f(154,280));
    clockHand.setScale(sf::Vector2f(1, 0.9));
    //clockHand.rotate(180);
    clockHand.setOrigin(clockHand.getSize().x/2.0f,clockHand.getSize().y);
    //clockHand.rotate(45);
    //printf("x:%f y:%f", clockHand.getOrigin().x, clockHand.getOrigin().y);

    sf::RectangleShape clockHand2(sf::Vector2f(8, 150));
    clockHand2.setTexture(&clockHandTexture);
    clockHand2.setScale(sf::Vector2f(1, 0.6));
    clockHand2.setOrigin(clockHand2.getSize().x / 2.0f, clockHand2.getSize().y);

    sf::RectangleShape clockHand3(sf::Vector2f(8, 150));
    clockHand3.setTexture(&clockHandTexture);
    clockHand3.setFillColor(sf::Color::Red);
    clockHand3.setScale(sf::Vector2f(1, 0.9));
    clockHand3.setOrigin(clockHand3.getSize().x / 2.0f, clockHand3.getSize().y);

    background.setOrigin(background.getSize().x/2.0f, background.getSize().y / 2.0f);

    while (window.isOpen())
    {
        while(window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();   
            }
        }
        time_t now = time(0);
        tm gmtm;
        gmtime_s(&gmtm, &now);

        clockHand.setRotation(gmtm.tm_min * 6);
        clockHand3.setRotation(gmtm.tm_sec * 6);
        //-30 is to compensate for it being 1 hour ahead for some reason
        clockHand2.setRotation(gmtm.tm_hour * 15-30);
        window.clear(sf::Color::White);
        window.draw(background); 
        window.draw(clockHand);
        window.draw(clockHand2);
        window.draw(clockHand3);
        window.display();
    }

    return 0;
}