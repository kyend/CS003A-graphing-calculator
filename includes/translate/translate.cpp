#include "translate.h"


Translate::Translate(){

}
Translate::Translate(Graph_info* graph_info){
    _info = graph_info;
}
sf::Vector2f Translate::coord_translation(sf::Vector2f _coord){
    sf::Vector2f translated;
    translated.x = _info->get_scale() * _coord.x + WORK_PANEL/2 + _info->get_offset().x;   //will eventually include scale for zooming in and out
    translated.y = SCREEN_HEIGHT/2 - _info->get_scale() * _coord.y + _info->get_offset().y;
    return translated;
}           //still need offset for both
sf::Vector2f Translate::operator()(sf::Vector2f _coord){
    return coord_translation(_coord);
}