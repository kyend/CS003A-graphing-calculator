#ifndef SYSTEM_H
#define SYSTEM_H
#include <vector>
#include <SFML/Graphics.hpp>
#include "../graph/graph.h"
#include "../plot/plot.h"
#include "../graph_info/graph_info.h"

using namespace std;
class System
{
public:
    System();
    System(Graph_info* info);
    void Step(int command, Graph_info* info);
    void Step(int command);
    void set_info(Graph_info* info);
    int Size();
    void Draw(sf::RenderWindow& window);


private:
    // vector<Particle> system;
    sf::CircleShape shape;
    sf::Vector2f vel;
    sf::RectangleShape not_shape;
    Graph_info* _info;
    Graph graph; 

};

#endif // SYSTEM_H
