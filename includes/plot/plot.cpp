#include "plot.h"
#include <iostream>

using namespace std;

Plot::Plot(){

}

Plot::Plot(Graph_info* info){     //will eventually take a Graph_info*
    cout << "top of plot ctor\n";
    _info = info;
    string eq = "x";
    Tokenizer token(eq);
    ShuntingYard post;
    eq_infix = token.tokenize();
    eq_postfix = post.postfix(eq_infix);
}

vector<sf::Vector2f> Plot::plotting(int index){
    double x_value, y_value;
    sf::Vector2f position;
    sf::Vector2f translated;
    vector<sf::Vector2f> _points;
    ShuntingYard post;

    string eq = "";
    eq = _info->get_equa(index);
    Tokenizer token(eq);
    eq_infix = token.tokenize();

    eq_postfix = post.postfix(eq_infix);
    RPN rpn = RPN(eq_postfix);

    double min = _info->get_domain().x;
    double max = _info->get_domain().y;
    double scale = _info->get_scale();        //points per screen relevant incr
    double incr = _info->get_incr();

    // std::cout<< "min " << min << " max " << max << std::endl;

    //for(int i = (min * points); i <= (max * points); i++){ 
    for(double i = min; i < max; i+=incr){
        // cout << i << endl;
        x_value = i;        //will need to call RPN later
        y_value = rpn(i);        //run through shunting yard;
        position.x = x_value;       //must set each separately
        position.y = y_value;
        //translate in here
        Translate translating(_info);       //creating a translate class object
        translated = translating.coord_translation(position);       //performing translation
        //translated = translate(position);
        _points.push_back(translated);    //pushing to vector
    }
    return _points;
}

void Plot::update(Graph_info* info){
    _info = info;
}


// sf::Vector2f Plot::translate(sf::Vector2f position){
//     sf::Vector2f translated;
//     translated.x = position.x * 11.2 + WORK_PANEL/2;
//     translated.y = SCREEN_HEIGHT/2 - position.y * 8;
//     return translated;
// }