#include "animate.h"
#include "constants.h"
#include <iostream>
#include <fstream>
using namespace std;
#include "system.h"

animate::animate():sidebar(WORK_PANEL, SIDE_BAR)
{
    cout << "beginning of animate" <<endl;
    _info = new Graph_info();
    cout << "graph info\n";
    system = System(_info);


    // _info->_window_dimensions = sf::Vector2f(SCREEN_WIDTH, WORK_PANEL);        //(x, y) --> (300, 300)
    // _info->_origin = sf::Vector2f(SCREEN_WIDTH/2, WORK_PANEL/2);       //graph's (0,0) in screen coords
    // _info->_domain = sf::Vector2f(-5, 5);
    // _info->_scale = sf::Vector2f(SCREEN_WIDTH/(_info->_domain.y - _info->_domain.x), WORK_PANEL/(_info->_domain.y - _info->_domain.x));
    
    cout<<"animate CTOR: TOP"<<endl;
    window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML window!");
    //VideoMode class has functions to detect screen size etc.
    //RenderWindow constructor has a third argumnet to set style
    //of the window: resize, fullscreen etc.

    //System will be implemented to manage a vector of objects to be animated.
    //  at that point, the constructor of the System class will take a vector
    //  of objects created by the animate object.
    //  animate will
    //system = System();
    window.setFramerateLimit(60);

    mouseIn = true;




    mousePoint = sf::CircleShape();
    mousePoint.setRadius(5.0);
    mousePoint.setFillColor(sf::Color::Red);

    cout<<"Game CTOR. preparing to load the font."<<endl;
    //--- FONT ----------
    //font file must be in the "working directory:
    //      debug folder
    //Make sure working directory is where it should be and not
    //  inside the app file:
    //  Project->RUN->Working Folder
    //
    //font must be a member of the class.
    //  Will not work with a local declaration
    if (!font.loadFromFile("arial.ttf")){
        cout<<"animate() CTOR: Font failed to load"<<endl;
        cin.get();
        exit(-1);
    }

    myTextLabel = sf::Text("f(x) received", font);
    myTextLabel.setCharacterSize(20);
    myTextLabel.setStyle(sf::Text::Bold);
    myTextLabel.setFillColor(sf::Color::Green);
    myTextLabel.setPosition(sf::Vector2f(10, SCREEN_HEIGHT-myTextLabel.getLocalBounds().height-15));

    topLeft = sf::Text("f(x) input", font);
    topLeft.setCharacterSize(20);
    topLeft.setStyle(sf::Text::Bold);
    topLeft.setFillColor(sf::Color::Cyan);
    topLeft.setPosition(sf::Vector2f(10, 5));

    domainP = sf::Text("( domain )", font);
    domainP.setCharacterSize(20);
    domainP.setStyle(sf::Text::Bold);
    domainP.setFillColor(sf::Color(255, 105, 180));
    domainP.setPosition(sf::Vector2f(880, SCREEN_HEIGHT-myTextLabel.getLocalBounds().height-15));

    sidebar[SB_KEY_PRESSED] = "HIT ENTER TO START"; //default when window opens
    
    ifstream if_file("historyfile.txt");
    string someting;
    while(getline(if_file, someting)){
        history.push_back(someting);
        cout << "history pushed back" << endl;
    }
    while(history.size() < 5){
        history.push_back("");
    }

    //probably dont need after clickable lines are working

    // if(!history.empty()){
    //     for(int i = 4; i < history.size() + 4; i++){
    //         sidebar[i] = history[i-4];
    //     }
    // }   
    if_file.close();
    // if(!if_file.fail()){         //if its not open, won't happen
        
    // }


    b0 = sf::Text(history[0], font);        //button 0
    b0.setCharacterSize(20);
    b0.setFillColor(sf::Color(text));
    b0.setPosition(sf::Vector2f(1190, 100));
    
    b1 = sf::Text(history[1], font);        //b1
    b1.setCharacterSize(20);
    b1.setFillColor(sf::Color(text));
    b1.setPosition(sf::Vector2f(1190, 131));
    
    b2 = sf::Text(history[2], font);        //b2
    b2.setCharacterSize(20);
    b2.setFillColor(sf::Color(text));
    b2.setPosition(sf::Vector2f(1190, 161));
    
    b3 = sf::Text(history[3], font);        //b3
    b3.setCharacterSize(20);
    b3.setFillColor(sf::Color(text));
    b3.setPosition(sf::Vector2f(1190, 191));
    
    b4 = sf::Text(history[4], font);        //b4
    b4.setCharacterSize(20);
    b4.setFillColor(sf::Color(text));
    b4.setPosition(sf::Vector2f(1190, 221));

    cout<<"animate instantiated successfully."<<endl;
}

void animate::Draw(){
    //Look at the data and based on the data, draw shapes on window object.
    system.Draw(window);
    if (mouseIn){
        window.draw(mousePoint);
    }

    sidebar.draw(window);

    //- - - - - - - - - - - - - - - - - - -
    //getPosition() gives you screen coords, getPosition(window) gives you window coords
    //cout<<"mosue pos: "<<sf::Mouse::getPosition(window).x<<", "<<sf::Mouse::getPosition(window).y<<endl;
    //- - - - - - - - - - - - - - - - - - -

    //drawing Test: . . . . . . . . . . . .
    //This is how you draw text:)
    window.draw(myTextLabel);
    window.draw(topLeft);
    window.draw(domainP);
    window.draw(b0);
    window.draw(b1);
    window.draw(b2);
    window.draw(b3);
    window.draw(b4);
    //. . . . . . . . . . . . . . . . . . .
}

void animate::update(){
    //cause changes to the data for the next frame
    system.Step(command);
    if (command != 0){
        dom = "";
        dom = "( " + to_string(_info->get_domain().x) + ", " + to_string(_info->get_domain().y) + " )";
        domainP.setString(dom);
    }
    command = 0;
    if (mouseIn){
        //mousePoint red dot:
        mousePoint.setPosition(sf::Mouse::getPosition(window).x-5,
                            sf::Mouse::getPosition(window).y-5);

        //mouse location text for sidebar:
        sidebar[SB_MOUSE_POSITION] = mouse_pos_string(window);




    }
}
void animate::render(){
    window.clear();
    Draw();
    window.display();
}



void animate::processEvents()
{
    bool debug = true;
    sf::Event event;
    string back = "";
    float mouseX, mouseY;

        //for the button number 0-4

    vector<string>::iterator it;
    vector<string>::iterator it_his = history.begin();

    bool button0 = sf::Mouse::getPosition(window).x >= 1120      //first function
                    && sf::Mouse::getPosition(window).x <= 1400
                    && sf::Mouse::getPosition(window).y >= 100
                    && sf::Mouse::getPosition(window).y <= 130;

    bool button1 = sf::Mouse::getPosition(window).x >= 1120      //second function
                    && sf::Mouse::getPosition(window).x <= 1400
                    && sf::Mouse::getPosition(window).y >= 131
                    && sf::Mouse::getPosition(window).y <= 160;

    bool button2 = sf::Mouse::getPosition(window).x >= 1120      //third function
                    && sf::Mouse::getPosition(window).x <= 1400
                    && sf::Mouse::getPosition(window).y >= 161
                    && sf::Mouse::getPosition(window).y <= 190;

    bool button3 = sf::Mouse::getPosition(window).x >= 1120      //fourth function
                    && sf::Mouse::getPosition(window).x <= 1400
                    && sf::Mouse::getPosition(window).y >= 191
                    && sf::Mouse::getPosition(window).y <= 220;

    bool button4 = sf::Mouse::getPosition(window).x >= 1120      //fifth function
                    && sf::Mouse::getPosition(window).x <= 1400
                    && sf::Mouse::getPosition(window).y >= 221
                    && sf::Mouse::getPosition(window).y <= 250;

    // equa_func.push_back(button0);
    // equa_func.push_back(button1);
    // equa_func.push_back(button2);
    // equa_func.push_back(button3);
    // equa_func.push_back(button4);




    while (window.pollEvent(event))//or waitEvent
        {
        // check the type of the event...
            switch (event.type)
            {
            // window closed
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::TextEntered:        //do this all outside somewhere else; graph class? system?     
                    // if(event.text.unicode == 133 || event.text.unicode == 133){
                    //     input = "";
                    // }
                    // if(on_off == false && event.text.unicode < 128 && event.text.unicode > 31){
                    if(toggle && event.text.unicode < 128 && event.text.unicode > 31 && event.text.unicode != 91 && event.text.unicode != 93){
                        input +=event.text.unicode; //need external bool/toggle 
                        switch(num){
                        case 0:
                            b0.setString(input);
                            myTextLabel.setString(input);
                        break;
                        case 1:
                            b1.setString(input);
                            myTextLabel.setString(input);
                        break;
                        case 2:
                            b2.setString(input);
                            myTextLabel.setString(input);
                        break;
                        case 3:
                            b3.setString(input);
                            myTextLabel.setString(input);
                        break;
                        case 4:
                            b4.setString(input);
                            myTextLabel.setString(input);
                        break;
                        default:
                        break;
                        }


                        // input +=event.text.unicode; //need external bool/toggle 
                        // topLeft.setString(input);
                        // _info->set_eq(input);
                        // system = System(_info);
                        // command = 3;

                    }
                break;
            // key pressed
            case sf::Event::KeyPressed:
                switch(event.key.code){
                    case sf::Keyboard::BackSpace:{
                        back = input.substr(0, input.size()-1);
                        // cout << "string is: " << back << endl;
                        input = back;
                        topLeft.setString(input);
                    }break;
                    case sf::Keyboard::Enter:{
                        if(toggle){          //if button is selected, then will erase current text and replace
                            if (input != ""){ 
                                it = history.erase(it_his + num); 
                                it = history.insert(it_his + num, input);
                                sidebar.box_color(num);
                                _info->edit_equa(input, num);   //if input is not empty, it can change

                                cout << "equation sent:" << _info->get_equa(num) << endl;
                                
                                command = 99;
                                input = "";
                                toggle = false;
                            }
                            else{
                                sidebar.box_color(num);
                                toggle = false;
                            }   
                        }

                        // if (on_off == true){
                        //     topLeft.setString("");
                        //     // cout << "if open, now setting to closed\n";
                        //     sidebar[SB_KEY_PRESSED] = "ENTER: PLEASE TYPE EQUATION";
                        // }
                        // else if (on_off == false){
                        //     // cout << "if off, now open n submitted\n";
                        //     sidebar[SB_KEY_PRESSED] = "ENTER: EQUATION SUBMITTED";
                        //     myTextLabel.setString(input);
                        //     history.push_back(input);       //push back input into history aka vector of string
                        //     // cout << "history size: " << history.size() << endl;
                        //     if(!history.empty()){
                        //         for(int i = 4; i < history.size() + 4; i++){
                        //             sidebar[i] = history[i-4];
                        //         }
                        //     }
                        //     _info->set_eq(input);                               //send to info
                        //     command = 99;
                        //     input = "";
                        // }
                        // on_off = !on_off;       //toggles true/false
                    }break;
                    case sf::Keyboard::Left:{
                        if(!toggle)
                        sidebar[SB_KEY_PRESSED] = "LEFT ARROW: PAN LEFT";
                        command = 4;
                    }break;
                    case sf::Keyboard::Right:{
                        if(!toggle)
                        sidebar[SB_KEY_PRESSED] = "RIGHT ARROW: PAN RIGHT";
                        command = 5;
                    }break;
                    case sf::Keyboard::Up:{
                        sidebar[SB_KEY_PRESSED] = "UP ARROW: PAN UP";
                        command = 7;
                    }break;
                    case sf::Keyboard::Down:{
                        sidebar[SB_KEY_PRESSED] = "DOWN ARROW: PAN DOWN";
                        command = 6;
                    }break;
                    case sf::Keyboard::LBracket:{
                            sidebar[SB_KEY_PRESSED] = "LEFT BRACKET: ZOOM OUT";
                            //changes scale and domain
                            command = 10;
                    }break;
                    case sf::Keyboard::RBracket:{
                        sidebar[SB_KEY_PRESSED] = "RIGHT BRACKET: ZOOM IN";
                        //changes scale and domain 
                        command = 11;
                    }break;
                    case sf::Keyboard::S:{
                        if(on_off){
                            cout << "dou we get heree??" << endl;
                            sidebar[SB_KEY_PRESSED] = "S: SAVED HISTORY";
                            ofstream file("historyfile.txt");
                            cout << "file created" << endl;
                            if(!history.empty()){
                                for(int i = 0; i < history.size(); i++){
                                    string hi_push = history[i];
                                    file << hi_push << endl;
                                }
                            }
                            file.close();       //prevents other things from altering your file
                            command = 42;
                        }
                    }break;
                    case sf::Keyboard::Escape:{
                        sidebar[SB_KEY_PRESSED] = "ESC: RESET";
                        command = 99;
                    }break;
                }
            case sf::Event::MouseEntered:{
                    mouseIn = true;
                    break;
            case sf::Event::MouseLeft:
                    mouseIn = false;
                    break;

            case sf::Event::MouseMoved:
                    mouseX = event.mouseMove.x;
                    mouseY = event.mouseMove.y;
                    //Do something with it if you need to...
                    break;
            case sf::Event::MouseButtonReleased:
                    if (event.mouseButton.button == sf::Mouse::Right)
                    {
                        sidebar[SB_MOUSE_CLICKED] = "RIGHT CLICK " +
                                mouse_pos_string(window);

                    }
                    else{
                        sidebar[SB_MOUSE_CLICKED] = "LEFT CLICK " +
                                mouse_pos_string(window);
                        if(!toggle){
                            sidebar[SB_KEY_PRESSED] = "HIT ENTER TO SUBMIT";
                            if(button0){
                                if(debug) cout << "button0\n";
                                toggle = true;      //toggled on, can receive text input now
                                num = 0;            //num of the button
                                myTextLabel.setString(input);       //shows eq in two places
                                b0.setString(input);
                                sidebar.box_color(num);             //changes to selected color
                                command = 30;
                            }
                            else if(button1){
                                if(debug) cout << "button1\n";
                                toggle = true;      //toggled on, can receive text input now
                                num = 1;
                                myTextLabel.setString(input);
                                b1.setString(input);
                                sidebar.box_color(num);
                                command = 31;
                            }
                            else if(button2){
                                if(debug) cout << "button2\n";
                                toggle = true;      //toggled on, can receive text input now
                                num = 2;
                                myTextLabel.setString(input);
                                b2.setString(input);
                                sidebar.box_color(num);
                                command = 32;
                            }
                            else if(button3){
                                if(debug) cout << "button0\n";
                                toggle = true;      //toggled on, can receive text input now
                                num = 3;
                                myTextLabel.setString(input);
                                b3.setString(input);
                                sidebar.box_color(num);
                                command = 33;
                            }
                            else if(button4){
                                if(debug) cout << "button0\n";
                                toggle = true;      //toggled on, can receive text input now
                                num = 4;
                                history.erase(it_his + num);
                                myTextLabel.setString(input);
                                b4.setString(input);
                                sidebar.box_color(num);
                                command = 34;
                            }            
                        }
                    }

                    break;

                default:
                    break;
            }
        }
    }
}

void animate::run(){
while (window.isOpen())
{
    processEvents();
    update();
    render(); //clear/draw/display
}
cout<<endl<<"-------ANIMATE MAIN LOOP EXITING ------------"<<endl;
}

// void animate::textInput(bool on_off){
//     if(on_off == false){
//         myTextLabel.setString(input);
//         //send to info
//         cout << "================= animate: input " << input << endl;
//         _info->set_eq(input);       //NOT WORKIGN 
//         cout << "equation gotten in animate: " << _info->get_eq() << endl;
//         command = 3;
//         // system.Step(command, _info);
//         input = "";
//         // on_off = !on_off;
//     }
// }

string mouse_pos_string(sf::RenderWindow& window){
    return "(" +
            to_string(sf::Mouse::getPosition(window).x) +
            ", " +
            to_string(sf::Mouse::getPosition(window).y) +
            ")";
}
