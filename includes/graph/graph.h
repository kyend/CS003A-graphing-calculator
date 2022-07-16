#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <SFML/Graphics.hpp>
#include "../animate/constants.h"
#include "../plot/plot.h"
#include "../graph_info/graph_info.h"
#include "../graph_info/equation.h"

using namespace std;

class Graph
{
public:
    Graph();
    Graph(Graph_info* info); 
    void Draw(sf::RenderWindow& window);
    void set_info();
    void update(Graph_info* info);

private:
    Graph_info* _info;

    vector<sf::Vector2f> _points;
    vector<sf::CircleShape> circle_points; //screen points
    vector<vector<sf::CircleShape>> points_prime;       //for functions 0-4

    sf::RectangleShape y_axis;
    sf::RectangleShape x_axis;
    // sf::CircleShape circle;
    // Plot points; 

    vector<sf::RectangleShape> grid_x;
    vector<sf::RectangleShape> grid_xn; 
    vector<sf::RectangleShape> grid_y; 
    vector<sf::RectangleShape> grid_yn;
    Plot _plot;


    //make two rectangleshapes for X and Y axes
    //font stuff??? 

};

#endif //GRAPH_H