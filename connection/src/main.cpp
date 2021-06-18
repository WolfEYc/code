#include "cells.hpp"

unsigned screenx = 1280, screeny = 720, fps = 30, cellsize = 20;

RenderWindow window(VideoMode(screenx,screeny), "Connection", Style::Close);
Vector2i windowoffset;
Vector2u mousepos;
Vector2u cellpos;

Cells cells(screenx,screeny,cellsize);

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

            case Event::MouseButtonPressed:
                windowoffset = window.getPosition();
                windowoffset.y+=30;
                mousepos = Vector2u(window.mapPixelToCoords((Mouse::getPosition()-windowoffset)));
                cellpos = cells.convertCoord(mousepos);

                if(Mouse::isButtonPressed(Mouse::Left)){
                    cout << cellpos.x << " " << cellpos.y << endl;
                    cells.modify(cellpos);
                    cout << "Cell ID: " << cells.getValue(cellpos) << " Charge: " << cells.getCharge(cellpos) << endl;
                    break;
                }
                if(Mouse::isButtonPressed(Mouse::Right)){                
                    cells.toggleSwitch(cellpos);
                    cout << "Cell ID: " << cells.getValue(cellpos) << " Charge: " << cells.getCharge(cellpos) << endl;
                    break;
                }
            
            default:
                break;
        }
    }
}

void render(){
    window.clear();

    cells.draw(window);
    
    window.display();
}


int main(){

    init();

    while(window.isOpen()){
        events();
        cells.iterate();
        render();
    }

    return 0;
}
