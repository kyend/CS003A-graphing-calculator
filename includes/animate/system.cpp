#include "system.h"
#include "random.h"

#include <iostream>

#include "constants.h"
System::System(){
    // Random r;
    // int xpos = 100;
    // int ypos = 100;
    // //the shape of the object, along with its velocity, acceleration,
    // //position, etc. should be part of the individual object.
    // shape = sf::CircleShape(10);
    // shape.setPosition(sf::Vector2f(xpos, ypos));
    // vel = sf::Vector2f(r.Next(-5,5), r.Next(-5,5)); //random velocity
    // int r_ = r.Next(0,255);
    // int g_ = r.Next(0,255);
    // int b_ = r.Next(0,255);
    // shape.setFillColor(sf::Color(r_, g_, b_));

    // not_shape = sf::RectangleShape(sf::Vector2f(420, 420));
    // not_shape.setPosition(sf::Vector2f(xpos,ypos));
    // vel = sf::Vector2f(r.Next(-10, 10), r.Next(-10, 10));
    // int _r = r.Next(0, 255);
    // int _g = r.Next(0, 255);
    // int _b = r.Next(0, 255);
    // not_shape.setFillColor(sf::Color::Yellow);


}

System::System(Graph_info* info){
    _info = info;
    graph = Graph(_info);

}


//------------------------------------------------------------------
//------------------------------------------------------------------

void System::Step(int command){
    switch(command){
        case 2:
            break;
        case 3:
            // cout << "equation in system is: " << _info->get_eq() << endl;
            break;
        case 4:     //left arrow pan left
            _info->pan_x(-1);
            break;
        case 5:     //pan right
            _info->pan_x(1);
            break;
        case 6:     //pan up
            _info->pan_y(-1);
            break;
        case 7:     //pan down
            _info->pan_y(1);
            break;
        case 10:    //zoom in
            _info->zoom_out();
            break;
        case 11:    //zoom out
            _info->zoom_in();
            break;
        case 99:
            _info->reset();
            break;
        default:
            break;
    }
    if(command != 0){
        // cout << _info << endl;
        graph.update(_info);
    }   //calls graph to redo stuff

        //all this is the responsibility of the
        // individual object:
        // shape.move(vel);
        // sf::Vector2f pos = shape.getPosition();
        // if ((pos.x)>=WORK_PANEL-20)
        //     vel = sf::Vector2f(-1*vel.x,1*vel.y);
        // if (pos.x<=0)
        // if ((pos.y)>=SCREEN_HEIGHT-20)
        //     vel = sf::Vector2f(1*vel.x,-1*vel.y);
        // if (pos.y<=0)
        //     vel = sf::Vector2f(1*vel.x,-1*vel.y);
    //    for (int i=0; i<particle_vector.size(); i++){
    //        particle_vector[i].step();
    //    }

    //reads user command, acts accordingly (arrow keys, etc)
}

// void System::Step(int command, Graph_info* info){
//     if(command != 0){
//         graph.update(_info);
//     }
// }


void System::Draw(sf::RenderWindow& window){
    graph.Draw(window);

}
