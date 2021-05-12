#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <bits/stdc++.h>
using namespace sf;

/*
Isaac Wolf
To compile and run
g++ particles.cpp -o particles -lsfml-graphics -lsfml-window -lsfml-system && ./particles
*/

float gravity = 0.f, acc_reducer = 1.f, radius = 1.f, damper = 10.f, cordLength = 0.f;
unsigned nballs = 1000, sx = 1920, sy = 1080, trailL = 50, count = 0, cores = 8;


RenderWindow window(VideoMode::getDesktopMode(), "Swingy", Style::Fullscreen);
VertexArray links(LineStrip,nballs);
Vector2f zero_vector(0.f,0.f);


struct ball{
    Vector2f v, p; //velocity position and radius and the representation
    float r;
    CircleShape rep;
    VertexArray trail;    
    
    ball(Vector2f pos, Vector2f vel, float rad, Color c){
        p = pos;
        v = vel;
        r = rad;
        rep = CircleShape(r);
        rep.setPosition(p);
        rep.setOrigin(r,r);
        rep.setFillColor(c);
        rep.setPointCount(64);
        /*
        trail = VertexArray(LineStrip, trailL);
        for(unsigned i = 0; i < trailL; i++){
            trail[i].position = p;
            trail[i].color = Color::Green;
            trail[i].color.g =  Color::Green.g -Color::Green.g*((i+1)/(float)trailL);
        }*/
    }

    void updatePos(){
        /*for(unsigned i = trailL-1; i > 0; i--){
            trail[i].position = trail[i-1].position;            
        }
        trail[0].position = p;
        trail[0].color = Color::Green;*/     
        p = p + v;
        rep.setPosition(p);        
    }
    
    void updatePos(Vector2f newPos){
        p = newPos;
        rep.setPosition(p);     
    }
};

std::vector<ball> balls;

void render(){
    //window.draw(links); 
    //window.draw(balls[i].trail);
    for(unsigned i = 0; i < nballs; i++)    
        window.draw(balls[i].rep);        
    
}

void update(unsigned int section){    
    
    //links[0].position = balls[0].p;
    unsigned int zone = nballs/cores;

    for(unsigned int i = (section-1)*zone; i < section*zone; i++){

        if(i==0)
            continue;

        //Vector2f dist_vec((balls[0].p.x - balls[i].p.x),((balls[0].p.y - balls[i].p.y)) );
        Vector2f dist_vec = zero_vector;
        
        for(int j = 0; j < nballs; j++){
            if(j!=i){
                Vector2f reducer(acc_reducer/(balls[j].p.x - balls[i].p.x), acc_reducer/(balls[j].p.y - balls[i].p.y));
                dist_vec = dist_vec + reducer;
            }
        }

        float dist = sqrt(dist_vec.x*dist_vec.x+dist_vec.y*dist_vec.y);

        if(dist > cordLength){
            Vector2f accel_vec((dist_vec.x) , (dist_vec.y) );
            balls[i].v = balls[i].v + accel_vec;
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
        
        //links[i].position = balls[i].p;
    }
      
}


void init(){
    window.setMouseCursorVisible(false);
    Vector2f mouse_pos(Mouse::getPosition().x,Mouse::getPosition().y);    
    balls.push_back(ball(mouse_pos ,zero_vector, radius, Color::Green ));
    for(int i = 1; i < nballs; i++){
        Vector2f rand_pos(mouse_pos.x + rand() % 1000 - 500, mouse_pos.y + rand() % 1000 - 500);
        balls.push_back(ball(rand_pos ,zero_vector, radius, Color::Red));
        //links[i].color = Color::Green;
    }
}




int main()
{
    srand(clock());
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    init();

    std::vector<Thread*> threads;
    for(unsigned i = 0; i < cores; i++)
        threads.push_back(new Thread(&update, i+1));   


    while (window.isOpen())
    {

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();            

        }        

        for(auto th : threads)
            th->launch();

        for(auto th : threads)
            th->wait();

        Vector2f mouse_pos(Mouse::getPosition().x,Mouse::getPosition().y);
        balls[0].updatePos(mouse_pos);
        
        

        window.clear(Color::Black);        
        
        render();
        
        window.display();
    }

    return 0;
}