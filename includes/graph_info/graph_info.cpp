#include "graph_info.h"

using namespace std;

Graph_info::Graph_info(){

    cout << "top of g_info ctor";

    for (int i = 0; i < 5; i++){
        _equa.push_back(Equation());
        _equa[i]._eq = "x";
        _equa[i]._show = false;
        _equa[i]._color = sf::Color(255, 255, 0);
    }

    cout << "graph info eq done \n";

    // eq_color[0] = sf::Color::Red;
    // eq_color[1] = sf::Color::Green;
    // eq_color[2] = sf::Color::Blue;
    // eq_color[3] = sf::Color::Magenta;
    // eq_color[4] = sf::Color::Yellow;    
    // cout << "eq colors done\n";

    _window_dimensions = sf::Vector2f(WORK_PANEL, SCREEN_HEIGHT);        //(x, y) --> (300, 300)
    // _origin = sf::Vector2f(WORK_PANEL/2, SCREEN_HEIGHT/2);       //graph's (0,0) in screen coords
    _domain = sf::Vector2f(-5, 5);
    // _scale = _points/(_domain.y - _domain.x);
    _scale = WORK_PANEL/(_domain.y - _domain.x);
    _incr = (_domain.y - _domain.x)/_points; 
    _offset = sf::Vector2f(0, 0);
    _pan_y = 0;
}

void Graph_info::pan_x(double arg){     //arg takes in -1 or +1 to know which direction 
    _domain.x += arg;     //increases min dom by offset
    _domain.y += arg;     //increases max dom by offset
    _scale = WORK_PANEL/(_domain.y - _domain.x);
    _incr = (_domain.y - _domain.x)/_points; 

    //_scale = sf::Vector2f(SCREEN_WIDTH/(_domain.y - _domain.x), WORK_PANEL/(_domain.y - _domain.x));
    _offset.x -= (arg * _scale);     //offset x is for x axis
    //offset here 
    //domain does change
} 

void Graph_info::pan_y(double arg){
    _scale = WORK_PANEL/(_domain.y - _domain.x);
    _incr = (_domain.y - _domain.x)/_points; 
    _offset.y += (arg * _scale);
    _pan_y += _scale;
    //_scale = sf::Vector2f(SCREEN_WIDTH/(_domain.y - _domain.x), WORK_PANEL/(_domain.y - _domain.x));
    //up and down no domain change 
}

void Graph_info::zoom_in(){
    //zooming in by a percent
    _domain.x = _domain.x * .8;
    _domain.y = _domain.y * .8;
    // cout << "ginfo _incr before zin: " << get_incr() << endl;
    _scale = WORK_PANEL/(_domain.y - _domain.x);
    _incr = (_domain.y - _domain.x)/_points; 
    // cout << "ginfo _incr after zin: " << get_incr() << endl;

}//will change scale AND domain

void Graph_info::zoom_out(){
    _domain.x = _domain.x * 1.25;
    _domain.y = _domain.y * 1.25;
    // cout << "ginfo _incr after zin: " << get_incr() << endl;
    _scale = WORK_PANEL/(_domain.y - _domain.x);
    _incr = (_domain.y - _domain.x)/_points; 
    // cout << "ginfo _incr after zout: " << get_incr() << endl;


}

void Graph_info::reset(){
    //_window_dimensions = sf::Vector2f(SCREEN_WIDTH, WORK_PANEL);        //(x, y) --> (300, 300)
    _origin = sf::Vector2f(WORK_PANEL/2, SCREEN_HEIGHT/2);       //graph's (0,0) in screen coords
    _domain = sf::Vector2f(-5, 5);
    _scale = WORK_PANEL/(_domain.y - _domain.x);
    _incr = (_domain.y - _domain.x)/_points; 
    _offset = sf::Vector2f(0, 0);
    // _offset.x = 0;
    // _offset.y = 0;
}

// void Graph_info::set_eq(string eq){
//     _equation = eq;
//     _id = 0;
// }

// void Graph_info::set_eq1(string eq){        //for button 1
//     _eq1 = eq;
//     _id = 1;
// }

// void Graph_info::set_eq2(string eq){        //for button 2
//     _eq2 = eq;
//     _id = 2;
// }

// void Graph_info::set_eq3(string eq){        //for button 3
//     _eq3 = eq;
//     _id = 3;
// }

// void Graph_info::set_eq4(string eq){        //for button 4
//     _eq4 = eq;
// }

void Graph_info::edit_equa(string eq, int index){
    _equa[index]._eq = "x";
    _equa[index]._show = true;
}

bool Graph_info::get_show(int index){
    return _equa[index]._show;
}

sf::Color Graph_info::get_color(int index){
    return _equa[index]._color;
}

string Graph_info::get_equa(int index){
    return _equa[index]._eq;
}
