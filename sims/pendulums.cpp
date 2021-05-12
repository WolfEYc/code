#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
using namespace sf;

//to compile and run
//g++ pendulums.cpp -o pendulums -lsfml-graphics -lsfml-window -lsfml-system && ./pendulums

float gravity = 5.f, acc_reducer = 100.f, radius = 5.f, damper = 30.f, cordLength = 0.f;
unsigned nballs = 3;
int sx = 1920, sy = 1080;
RenderWindow window(sf::VideoMode(sx, sy), "Swingy", sf::Style::Fullscreen);
VertexArray links(LineStrip,nballs);

struct ball{
    Vector2f v, p; //velocity position and radius and the representation
    float r;
    CircleShape rep;
    
    ball(Vector2f pos, Vector2f vel, float rad){
        p = pos;
        v = vel;
        r = rad;
        rep = CircleShape(r);
        rep.setPosition(p);
        rep.setOrigin(r,r);
        rep.setFillColor(Color::Red);
        rep.setPointCount(64);
    }

    void updatePos(){        
        p += v;
        rep.setPosition(p);        
    }
    
    void updatePos(Vector2f newPos){
        p = newPos;
        rep.setPosition(p);     
    }
};

std::vector<ball> balls;

void init(){
    Vector2f mouse_pos(Mouse::getPosition().x,Mouse::getPosition().y);
    Vector2f zero_vector(0.f,0.f);
    for(int i = 0; i < nballs; i++){
        balls.push_back(ball(mouse_pos,zero_vector, radius));
        links[i].color = Color::Green;
    }
}

void update(){
    Vector2f mouse_pos(Mouse::getPosition().x,Mouse::getPosition().y);
    balls[0].updatePos(mouse_pos);
    links[0].position = balls[0].p;

    for(int i = 1; i < nballs; i++){        
        Vector2f dist_vec = balls[i-1].p - balls[i].p;
        float dist = sqrt(dist_vec.x*dist_vec.x+dist_vec.y*dist_vec.y);

        if(dist > cordLength){
            Vector2f accel_vec(dist_vec.x / acc_reducer, (dist_vec.y) / acc_reducer);
            balls[i].v += accel_vec;
        }
        
        balls[i].v.y += gravity;

        if(balls[i].v.y > damper)
            balls[i].v.y = damper;

        if(balls[i].v.y < -damper)
            balls[i].v.y = -damper;

        if(balls[i].v.x > damper)
            balls[i].v.x = damper;

        if(balls[i].v.x < -damper)
            balls[i].v.x = -damper;

        balls[i].updatePos();
        links[i].position = balls[i].p;
    }    
}

void render(){
    window.draw(links);
    
    for(int i = 0; i< nballs; i++){
        window.draw(balls[i].rep);        
    }
    
}

int main()
{
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    init();

    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();            

        }

        update();

        window.clear(Color::Black);
        
        render();
        
        window.display();
    }

    return 0;
}