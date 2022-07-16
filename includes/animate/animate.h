#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include <string.h>
#include "system.h"
#include "sidebar.h"
#include "../graph_info/graph_info.h"

class animate{
public:
    animate();
    animate(Graph_info* info);
    void run();
    void processEvents();
    void update();
    void render();
    void Draw();
    // void textInput(bool on_off);       //char input, bool on_off
private:
    sf::RenderWindow window;
    System system;                      //container for all the animated objects
    Sidebar sidebar;                    //rectangular message sidebar


    sf::CircleShape mousePoint;         //The little red dot
    int command;                        //command to send to system
    int f_comm;                         //command to send to sidebar; only for multi graphs
    int num = 0;                        //button number 0-4

    sf::Font font;                      //font to draw on main screen
    sf::Text myTextLabel;               //text to draw on main screen
    sf::Text topLeft;                  //text for while entering
    sf::Text domainP;

    sf::Text b0;
    sf::Text b1;
    sf::Text b2;
    sf::Text b3;
    sf::Text b4;

    sf::Color text = sf::Color(255, 255, 0);        //yellow for the time being 



    bool mouseIn;                       //mouse is in the screen
    string input;
    string dom;
    Graph_info* _info;
    bool on_off = true;

    bool toggle = false;

    vector<string> history;

    vector<bool> equa_func;


    //font stuff
    //input function stuff
};

string mouse_pos_string(sf::RenderWindow& window);

#endif // GAME_H
