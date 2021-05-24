#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <bits/stdc++.h>
using namespace sf;

/*
Isaac Wolf
To compile and run
g++ oldparticles.cpp -o oldparticles -lsfml-graphics -lsfml-window -lsfml-system && ./oldparticles
*/

float gravity = 0.f, acc_reducer = 1.f, radius = 1.f, damper = 15.f, cordLength = 0.f;
unsigned nballs = 8000, sx = 1920, sy = 1080, trailL = 50, count = 0, cores = std::thread::hardware_concurrency();
bool pull = false;

RenderWindow window(VideoMode::getDesktopMode(), "Swingy", Style::Fullscreen);
VertexArray links(LineStrip,nballs);
Vector2f zero_vector(0.f,0.f);

float Q_rsqrt(float number){
    long i;
    float x2, y;
    
    x2 = number * 0.5f;
    y = number;
    i = * (long *) &y;
    i = 0x5f3759df - (i >> 1);
    y = * (float *) &i;
    y = y * (1.5f - (x2 * y * y));
    y = y * (1.5f - (x2 * y * y));
    
    return y;
}

float rdist(Vector2f dif){
	return sqrt((dif.x * dif.x) + (dif.y * dif.y));
}

Vector2f normalize(Vector2f v,float d){    
    return Vector2f(v.x/d, v.y/d);
}

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
    }

    void updatePos(){
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
    for(unsigned i = 0; i < nballs; i++){    
        window.draw(balls[i].rep);
    }    
}

void update(unsigned int section){
    
    unsigned int zone = nballs/cores;

    for(unsigned int i = (section-1)*zone; i < section*zone; i++){

        if(i==0)
            continue;
        
        Vector2f dist_vec(balls[0].p - balls[i].p);
        float dis = rdist(dist_vec);
        Vector2f normalized_v = normalize(dist_vec,dis);
        
        if(pull)            
            balls[i].v = balls[i].v + normalized_v;
        
        if(balls[i].v.y > damper)
            balls[i].v.y = damper;

        if(balls[i].v.y < -damper)
            balls[i].v.y = -damper;

        if(balls[i].v.x > damper)
            balls[i].v.x = damper;

        if(balls[i].v.x < -damper)
            balls[i].v.x = -damper;     
        
        balls[i].updatePos();
        
        float cbrtdist = cbrt(dis);

        balls[i].rep.setFillColor(Color (220/cbrtdist,80/cbrtdist,30));

    }      
}

void init(){
    window.setMouseCursorVisible(false);
    Vector2f mouse_pos(Mouse::getPosition().x,Mouse::getPosition().y);    
    balls.push_back(ball(mouse_pos ,zero_vector, radius, Color::Green ));
    for(int i = 1; i < nballs; i++){
        Vector2f rand_pos(mouse_pos.x + rand() % 1000 - 500, mouse_pos.y + rand() % 1000 - 500);
        balls.push_back(ball(rand_pos ,zero_vector, radius, Color(255,0,10)));
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
        if(count > 600)
            count = 0;

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if(event.type == Event::MouseButtonPressed)
                pull = true;            

            if(event.type == Event::MouseButtonReleased)
                pull = false;
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
        //count++;
    }
    return 0;
}
