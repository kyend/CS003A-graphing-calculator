#ifndef TRANSLATE_H
#define TRANSLATE_H
#include <vector>
#include <SFML/Graphics.hpp>
#include "../queue/MyQueue.h"
#include "../token/token.h"
#include "../rpn/rpn.h"
#include "../shunting_yard/shunting_yard.h"
#include "../animate/constants.h"
#include "../graph_info/graph_info.h"

class Translate{
    public:
        Translate();
        Translate(Graph_info* graph_info);
        sf::Vector2f coord_translation(sf::Vector2f _coord);
        sf::Vector2f operator()(sf::Vector2f _coord);   //should just call the above

        void set_info(Graph_info* new_info);        //new graph info to change things with    

    private:
        Graph_info* _info;
};

#endif      //COORD_TRANSLATIONS_H