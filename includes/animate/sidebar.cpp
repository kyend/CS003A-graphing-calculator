#include "sidebar.h"
#include "constants.h"
Sidebar::Sidebar(){

}

Sidebar::Sidebar(float left, float width):_left(left), _width(width){
    cout<<"Sidebar CTOR: TOP"<<endl;
    items.reserve(50);

    //set up the sidebar rectangle:
    rect.setFillColor(sf::Color(105,105,105)); //(192,192,192)); //silver
    rect.setPosition(sf::Vector2f(left, 0));
    rect.setSize(sf::Vector2f(width, SCREEN_HEIGHT));
    cout<<"Sidebar CTOR: about to load font."<<endl;

    box.setFillColor(sf::Color(64, 64, 64));
    box.setSize(sf::Vector2f(180, 25));

    for(int i = 0; i < 5; i++){
        bars.push_back(box);
        bars[i].setPosition(sf::Vector2f(1170, 100 + (i*30)));
    }

    ////- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    //the font file must be in the "working directory"
    // check projects->run->working directory
    //      [Make sure it's not pointing to the app file]

    if (!font.loadFromFile("Roboto-Thin.ttf")){
        cout<<"Sidebar() CTOR: Font failed to load"<<endl;
        cin.get();
        exit(-1);
    }
    ////- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    cout<<"Sidebar CTOR: loaded font."<<endl;

    //. . . . . text / font problems: . . . . . . . .
    //initializing text object in this way caused problems
    // (hangs!)
    //only when sb_text was a private member and worked fine
    //when it was a public member. Probably not releavant,
    //but still strange!
    //
    //sb_text = sf::Text("Initial String for myTextLabel", font);
    //
    //. . . . . . . . . . . . . . . . . . . . . . . . .
    cout<<"Sidebar CTOR: Text object initialized."<<endl;
    sb_text.setFont(font);
    sb_text.setCharacterSize(20);
    sb_text.setStyle(sf::Text::Bold);
    sb_text.setFillColor(sf::Color::Yellow);

    ////this is how you would position text on screen:
    //sb_text.setPosition(sf::Vector2f(10, SCREEN_HEIGHT-sb_text.getLocalBounds().height-5));

    items.push_back("sidebar sample text");
    //Fill the items vector with empty strings so that we can use [] to read them:
    for (int i=0 ; i<30; i++){
        items.push_back("");
    }
    cout<<"Sidebar: CTOR: Exit."<<endl;
}

void Sidebar::draw(sf::RenderWindow& window){
    const double VERTICAL_LINE_SPACING = 5.0;
    const double LEFT_MARGIN = 10.0;

    window.draw(rect);
    for (int i = 0; i < bars.size(); i++){
        window.draw(bars[i]);
    }
    float height = 10;

    int t = 0;      //counter for sb_text

    for (vector<string>::iterator it = items.begin();
                                it!= items.end(); it++){
        bool blank = false;
        if (it->length() == 0){
            //empty rows must be taken into account (getLocalBounds())
            //    but not drawn
            blank = true;
            sb_text.setString("BLANK");
        }
        else{
            sb_text.setString(it->c_str());
        }
        if (t < 4){
        sb_text.setPosition(sf::Vector2f(_left+LEFT_MARGIN, height));   //sets the pos of line of text  
        height += sb_text.getLocalBounds().height+VERTICAL_LINE_SPACING;
        }
        // else if(t >= 4){
        //     sb_text.setPosition(sf::Vector2f(bars[t-4].getPosition().x + 20, bars[t-4].getPosition().y));
        // }
        if (!blank)
            window.draw(sb_text);
        t++;
    }
}

string& Sidebar::operator [](int index){
    return items[index];
}

void Sidebar::box_color(int line){
    if(bars[line].getFillColor() != sf::Color::Magenta){            //if not magenta, turn on
        bars[line].setFillColor(sf::Color::Magenta);

    }
    else if(bars[line].getFillColor() == sf::Color::Magenta){       //if magenta, turn off
        bars[line].setFillColor(sf::Color(64, 64, 64));
    }
}

Graph_info* Sidebar::update(int f_comm){
    if(f_comm != 0){
        return _info;
    }
}


//text.setPosition(rect.getPosition())

//     for (vector<string>::iterator it = items.begin();
//                                 it!= items.end(); it++){
//         bool blank = false;
//         if (it->length() == 0){
//             //empty rows must be taken into account (getLocalBounds())
//             //    but not drawn
//             blank = true;
//             sb_text.setString("BLANK");
//         }
//         else{
//             sb_text.setString(it->c_str());
//         }
//         sb_text.setPosition(sf::Vector2f(_left+LEFT_MARGIN, height));   //sets the pos of line of text  
//         height += sb_text.getLocalBounds().height+VERTICAL_LINE_SPACING;
//         if (!blank)
//             window.draw(sb_text);
//     }
// }