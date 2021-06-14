#include "cell.hpp"
#include <iostream>
using namespace std;
using namespace sf;

unsigned screenx = 800, screeny = 800, fps = 60, cellsize = 25;

static RenderWindow window(VideoMode(screenx,screeny), "Ricochet", Style::Close);

vector<cell> cells;

void init(){
    window.setFramerateLimit(fps);    
}

void events(){
    Event e;
    while(window.pollEvent(e)){
        switch (e.type)
        {
        case Event::Closed:
            window.close();
            break;

        
        
        default:
            break;
        }
    }
}

void render(){
    window.clear();

    
    
    window.display();
}


int main(){

    init();

    while(window.isOpen()){

        events();

        render();

    }


    return 0;
}
