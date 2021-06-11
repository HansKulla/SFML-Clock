#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <SFML/System.hpp>
#include <ctime>

int main()
{
    const int width = 500, height = 500;
    sf::Event event;
    sf::RenderWindow window( sf::VideoMode(width,height), "SFML works!" );

    //sets view on origin
    sf::View view2(sf::Vector2f(0.f, 0.f), sf::Vector2f(500.f, 500.f));
    window.setView(view2);

    //creates background
    sf::Texture backgroundClock;
    backgroundClock.loadFromFile("CLOCK.png");
    sf::RectangleShape background(sf::Vector2f(300, 300));
    background.setTexture(&backgroundClock);  
    //centers the background on the origin
    background.setOrigin(background.getSize().x / 2.0f, background.getSize().y / 2.0f);


    //creates a texture object
    sf::Texture clockHandTexture;
    //loads a picture of an arrow for a clockhand
    clockHandTexture.loadFromFile("clockHand.png");
    sf::RectangleShape clockHandMinute(sf::Vector2f(8, 150));
    clockHandMinute.setTexture(&clockHandTexture);
    clockHandMinute.setScale(sf::Vector2f(1, 0.9));
    //centers the clock hand in x dimension and shifts it just above the origin in y direction
    clockHandMinute.setOrigin(clockHandMinute.getSize().x/2.0f,clockHandMinute.getSize().y);
    //printf("x:%f y:%f", clockHand.getOrigin().x, clockHand.getOrigin().y);

    sf::RectangleShape clockHandHour(sf::Vector2f(8, 150));
    clockHandHour.setTexture(&clockHandTexture);
    clockHandHour.setScale(sf::Vector2f(1, 0.6));
    clockHandHour.setOrigin(clockHandHour.getSize().x / 2.0f, clockHandHour.getSize().y);

    sf::RectangleShape clockHandSecond(sf::Vector2f(8, 150));
    clockHandSecond.setTexture(&clockHandTexture);
    clockHandSecond.setFillColor(sf::Color::Red);
    clockHandSecond.setScale(sf::Vector2f(1, 0.9));
    clockHandSecond.setOrigin(clockHandSecond.getSize().x / 2.0f, clockHandSecond.getSize().y);

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

        //rotation for minutes and seconds is 360/60 = 6 degrees/minute
        clockHandMinute.setRotation(gmtm.tm_min * 6);
        clockHandSecond.setRotation(gmtm.tm_sec * 6);
        //function takes hours from midnight so need to compensate with +1
        //rotation for hours is 360/12 = 30 degrees/hour if goes over 12 hours still works since 13*30 (13:00) = 390 is the same -
        //rotation as 1*30
        clockHandHour.setRotation((gmtm.tm_hour + 1) * 30);
        //sets rotation for inbetween hours, math is (current_minute/60) * 30 which simplifies to current_minute/2
        clockHandHour.rotate(gmtm.tm_min / 2);
        window.clear(sf::Color::White);
        window.draw(background); 
        window.draw(clockHandMinute);
        window.draw(clockHandHour);
        window.draw(clockHandSecond);
        window.display();
    }

    return 0;
}