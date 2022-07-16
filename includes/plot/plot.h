#ifndef PLOT_H
#define PLOT_H
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../queue/MyQueue.h"
#include "../token/token.h"
#include "../rpn/rpn.h"
#include "../shunting_yard/shunting_yard.h"
#include "../animate/constants.h"
#include "../graph_info/graph_info.h"
#include "../translate/translate.h"
#include "../tokenizer/tokenizer.h"

class Plot{
    public:
        Plot();
        Plot(Graph_info* info);   //calls set info
        vector<sf::Vector2f> plotting(int index);  //returns vector of screen coords; calls the translate class, not a specific function
        // sf::Vector2f translate(sf::Vector2f position);
        void update(Graph_info* info);
        void set_info(Graph_info*);

        
    private:
        Queue<Token*> eq_infix;
        Queue<Token*> eq_postfix;
        Graph_info* _info;  
};


#endif //PLOT_H