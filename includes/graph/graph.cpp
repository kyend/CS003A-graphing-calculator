#include "graph.h"

Graph::Graph(){
    // y_axis = sf::RectangleShape(sf::Vector2f(3, SCREEN_HEIGHT));    //make the y axis
    // y_axis.setPosition(sf::Vector2f(WORK_PANEL/2, 0));
    // y_axis.setFillColor(sf::Color::White);


    // x_axis = sf::RectangleShape(sf::Vector2f(WORK_PANEL, 3));
    // x_axis.setPosition(sf::Vector2f(0, SCREEN_HEIGHT/2));
    // x_axis.setFillColor(sf::Color::White);

    // //translates the vector of vector2fs into a vector of circles

    // Plot plotter = Plot();
    // _points = plotter();

    // for(int i = 0; i <= _info->_points; i++){   //number of points; must determine myself;  
    //     circles_points.push_back(sf::CircleShape(2));

    //     circles_points[i].setPosition(sf::Vector2f(_points[i].x, _points[i].y));
    //     circles_points[i].setFillColor(sf::Color::Green);
    //     //points = 
    // }

}

Graph::Graph(Graph_info* info){
    cout << "top of graph ctor\n";

    _info = info;
    _plot = Plot(_info);
    double domain_size = _info->get_domain().y - _info->get_domain().x;
    double scale_size = _info->get_scale();

    cout << "domain size: " << domain_size << endl;
    cout << "scale: " << _info->get_scale() << endl;

    y_axis = sf::RectangleShape(sf::Vector2f(3, SCREEN_HEIGHT));    //make the y axis
    y_axis.setPosition(sf::Vector2f(WORK_PANEL/2 + _info->get_offset().x, 0));
    y_axis.setFillColor(sf::Color::White);


    x_axis = sf::RectangleShape(sf::Vector2f(WORK_PANEL, 3));   //make x axis
    x_axis.setPosition(sf::Vector2f(0, SCREEN_HEIGHT/2 + _info->get_offset().y));
    x_axis.setFillColor(sf::Color::White);



    for(int index = 0; index < 5; index++){
        if(_info->get_show(index)){
            _points.clear();        //clear points from vector of vector2f 
            _points = _plot.plotting(index);

            circle_points.clear();      //clearing old circle points

            for(int i = 0; i < _points.size(); i++){
                circle_points.push_back(sf::CircleShape(2));                //pushing shapes
                circle_points[i].setPosition(sf::Vector2f(_points[i].x, _points[i].y));     //points for circles from previous function
                circle_points[i].setFillColor(sf::Color(_info->get_color(index)));          //setting color per function
            }
            points_prime.push_back(circle_points);
        }
        else{
            points_prime.push_back(vector<sf::CircleShape>());      //make empty vector to pop in place
        }
    }


    //for the initial set for multi-plots, we need ALL 5 graphs
    // for(int index = 0; index < 5; index++){

    //     cout << "graph: f(x) " << index << endl;
    //     _info->set_num(index);      //function 0-4
    //     points_prime[index].clear();        //clearing out old points
        // _points = _plot();              //getting new points of function i
    //     cout << "calc points\n";

    //     for(int i = 0; i < _points.size(); i++){
    //         points_prime[index].push_back(sf::CircleShape(2));
    //         points_prime[index][i].setPosition(sf::Vector2f(_points[i].x, _points[i].y));
    //         points_prime[index][i].setFillColor(sf::Color(_info->get_color(index)));
    //     }
    //     cout << "pushed back points\n";
    // }




    // //translates the vector of vector2fs into a vector of circles
    // circles_points.clear();
    // _points = _plot();

    // for(int i = 0; i < _points.size(); i++){   //number of points; must determine myself;  
    //     circles_points.push_back(sf::CircleShape(2));
    //     circles_points[i].setPosition(sf::Vector2f(_points[i].x, _points[i].y));
    //     circles_points[i].setFillColor(sf::Color::Green);
    // }



    //gridlines drawn from x and y axes respectively

    for(double i = 0; i < _info->get_domain().y; i++){
        // cout << "testing grid x in graph" << endl;
        grid_x.push_back(sf::RectangleShape(sf::Vector2f(1, SCREEN_HEIGHT)));
        grid_x[i].setPosition(sf::Vector2f((scale_size*i) + WORK_PANEL/2 + _info->get_offset().x, 0)); //_info->get_scale() * i, 0
        grid_x[i].setFillColor(sf::Color(64, 64, 64));
    }

    int j = 0;      //for incrementing the negative grid lines
    int k = 0;

    for(double i = 0; i > _info->get_domain().x; i--){
        // cout << "testing grid x in graph" << endl;
        grid_xn.push_back(sf::RectangleShape(sf::Vector2f(1, SCREEN_HEIGHT)));
        grid_xn[j].setPosition(sf::Vector2f(WORK_PANEL/2 + _info->get_offset().x + (scale_size*i), 0)); //_info->get_scale() * i, 0
        grid_xn[j].setFillColor(sf::Color(64, 64, 64));
        j++;
    }

    for(double i = 0; i < _info->get_domain().y + _info->get_pan_y(); i++){
        grid_y.push_back(sf::RectangleShape(sf::Vector2f(WORK_PANEL, 1)));
        grid_y[i].setPosition(sf::Vector2f(0, SCREEN_HEIGHT/2 + _info->get_offset().y + (scale_size*i))); //_info->get_scale() * i, 0
        grid_y[i].setFillColor(sf::Color(64, 64, 64));
    }

    for(double i = 0; i > _info->get_domain().x - _info->get_pan_y(); i--){
        grid_yn.push_back(sf::RectangleShape(sf::Vector2f(WORK_PANEL, 1)));
        grid_yn[k].setPosition(sf::Vector2f(0, SCREEN_HEIGHT/2 + _info->get_offset().y + (scale_size*i))); //_info->get_scale() * i, 0
        grid_yn[k].setFillColor(sf::Color(64, 64, 64));
        k++;
    }



}

void Graph::update(Graph_info* info){
    //need to update the axes and circlepoints
    // cout << "address of graph gi" << _info << endl;
    // cout << "x offset: " << _info->get_offset().x << endl;
    // cout << "y offset: " << _info->get_offset().y << endl;

    // cout << "equation in graph class: " << _info->get_eq() << endl;

    _info = info;
    double domain_size = _info->get_domain().y - _info->get_domain().x;
    double scale_size = _info->get_scale();
    // cout << _info->get_domain().x << ", " << _info->get_domain().y << endl;
    
    _plot.update(_info);

    y_axis = sf::RectangleShape(sf::Vector2f(3, SCREEN_HEIGHT));    //make the y axis
    y_axis.setPosition(sf::Vector2f(WORK_PANEL/2 + _info->get_offset().x, 0));
    y_axis.setFillColor(sf::Color::White);


    x_axis = sf::RectangleShape(sf::Vector2f(WORK_PANEL, 3));   //make x axis
    x_axis.setPosition(sf::Vector2f(0, SCREEN_HEIGHT/2 + _info->get_offset().y));
    x_axis.setFillColor(sf::Color::White);

    for(int index = 0; index < 5; index++){
        if(_info->get_show(index)){
            _points.clear();        //clear points from vector of vector2f 
            _points = _plot.plotting(index);

            circle_points.clear();      //clearing old circle points

            for(int i = 0; i < _points.size(); i++){
                circle_points.push_back(sf::CircleShape(2));                //pushing shapes
                circle_points[i].setPosition(sf::Vector2f(_points[i].x, _points[i].y));     //points for circles from previous function
                circle_points[i].setFillColor(sf::Color(_info->get_color(index)));          //setting color per function
            }
            points_prime.push_back(circle_points);
        }
        else{
            points_prime.push_back(vector<sf::CircleShape>());      //make empty vector to pop in place
        }
    }

    grid_x.clear();
    grid_xn.clear();
    grid_y.clear();
    grid_yn.clear();
    
    for(double i = 0; i < _info->get_domain().y; i++){
        // cout << "testing grid x in graph" << endl;
        grid_x.push_back(sf::RectangleShape(sf::Vector2f(1, SCREEN_HEIGHT)));
        grid_x[i].setPosition(sf::Vector2f((scale_size*i) + WORK_PANEL/2 + _info->get_offset().x, 0)); //_info->get_scale() * i, 0
        grid_x[i].setFillColor(sf::Color(64, 64, 64));
    }

    int j = 0;      //for incrementing the negative grid lines
    int k = 0;

    for(double i = 0; i > _info->get_domain().x; i--){
        // cout << "testing grid x in graph" << endl;
        grid_xn.push_back(sf::RectangleShape(sf::Vector2f(1, SCREEN_HEIGHT)));
        grid_xn[j].setPosition(sf::Vector2f(WORK_PANEL/2 + _info->get_offset().x + (scale_size*i), 0)); //_info->get_scale() * i, 0
        grid_xn[j].setFillColor(sf::Color(64, 64, 64));
        j++;
    }

    for(double i = 0; i < _info->get_domain().y + _info->get_pan_y(); i++){
        grid_y.push_back(sf::RectangleShape(sf::Vector2f(WORK_PANEL, 1)));
        grid_y[i].setPosition(sf::Vector2f(0, SCREEN_HEIGHT/2 + _info->get_offset().y + (scale_size*i))); //_info->get_scale() * i, 0
        grid_y[i].setFillColor(sf::Color(64, 64, 64));
    }

    for(double i = 0; i > _info->get_domain().x - _info->get_pan_y(); i--){
        grid_yn.push_back(sf::RectangleShape(sf::Vector2f(WORK_PANEL, 1)));
        grid_yn[k].setPosition(sf::Vector2f(0, SCREEN_HEIGHT/2 + _info->get_offset().y + (scale_size*i))); //_info->get_scale() * i, 0
        grid_yn[k].setFillColor(sf::Color(64, 64, 64));
        k++;
    }



}


void Graph::Draw(sf::RenderWindow& window){
    window.draw(y_axis);
    window.draw(x_axis);

    for(int index = 0; index < 5; index++){
        for(int i = 0; i < points_prime[index].size(); i++){
            window.draw(points_prime[index][i]);
        }
    }

    for(int i = 0; i < grid_x.size(); i++){
        // cout << "drawing grid x" << endl;
        window.draw(grid_x[i]);
    }
    for(int i = 0; i < grid_xn.size(); i++){
        // cout << "drawing grid x" << endl;
        window.draw(grid_xn[i]);
    }
    for(int i = 0; i < grid_y.size(); i++){
        // cout << "drawing grid x" << endl;
        window.draw(grid_y[i]);
    }
    for(int i = 0; i < grid_yn.size(); i++){
        // cout << "drawing grid x" << endl;
        window.draw(grid_yn[i]);
    }
}