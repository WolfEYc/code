#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
using namespace sf; 
using namespace std;

//g++ conways.cpp -o conways -lsfml-graphics -lsfml-window -lsfml-system && ./conways


float a, b;
CircleShape p;

RenderWindow window(VideoMode::getDesktopMode(), "dots an shid", Style::Close);
View view(window.getDefaultView());

void nextpos (){
    float x = p.getPosition().x;
    float y = p.getPosition().y;
    p.setPosition(sin(x*y/b)*y+cos(a*x-y),x+sin(y)/b);
}

void init(){
    a = -0.65343;
    b =  0.7345345;  
    window.clear();
    view.setCenter(0.f,0.f);  
    p.setRadius(1.f);
    p.setPosition(1.f,1.f);
    p.setFillColor(Color::Red);
    view.zoom(0.1f);
    window.setView(view);
}

void render(){
    window.draw(p);
    window.display();
}

int main(){
    srand(clock());
    init();
    while(window.isOpen()){

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        render();
        nextpos();
    }
    


    


}