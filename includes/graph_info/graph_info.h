#ifndef GRAPH_INFO_H
#define GRAPH_INFO_H
#include <vector>
#include <SFML/Graphics.hpp>
#include "../queue/MyQueue.h"
#include "../token/token.h"
#include "../rpn/rpn.h"
#include "../shunting_yard/shunting_yard.h"
#include "../animate/constants.h"
#include "equation.h"

class Graph_info
{
public:
    Graph_info();
    void pan_x(double arg);     //arg can be positive or negative, depending on directing
    void pan_y(double arg);
    void zoom_in();      //will change scale AND domain
    void zoom_out();

    double get_scale(){return _scale;}
    sf::Vector2f get_offset(){return _offset;}
    sf::Vector2f get_domain(){return _domain;}
    double get_points(){return _points;}
    double get_incr(){return _incr;}
    double get_pan_y(){return _pan_y;}
    // string get_eq(){return _equation;}
    int get_num(){return _num;}

    void set_num(int i){_num = i;}

    string get_equa(int index);
    sf::Color get_color(int index);

    void edit_equa(string eq, int index);        //changes the equation at index
    vector<Equation> get_equa();
    bool get_show(int index);

    void reset();

    //need get vectors

private:
    double _points = 1000;        //number of points; doesn't change at all
    vector<Equation> _equa; 
    
    // string _equation;
    // string _eq1;
    // string _eq2;
    // string _eq3;
    // string _eq4;

    int _num;

    sf::Vector2f _window_dimensions;        //(x, y) --> (300, 300)
    sf::Vector2f _origin;       //graph's (0,0) in screen coords
    sf::Vector2f _domain;
    double _scale;
    double _incr;
    sf::Vector2f _offset;
    double _pan_y;  
    /*should be based on domain; has to do with zoom; 
    *what do you multiply your points by to make sure 
    *they are in the right place re:screen coords*/

//    vector<sf::Color> eq_color; 
};


#endif      //GRAPH_INFO_H