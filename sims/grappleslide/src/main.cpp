#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
using namespace sf;

unsigned sw = 600, sh = 400, it = 0, pastFlip = 0, collision = 0; // 0 none, 1 below, 2 above, 3 mouse

bool grav = 1, prev = 0; //0 = up, 1 = down

RectangleShape colliding;

Vector2f zero(0.f,0.f);
Vector2f velocity(0.f,0.f);
Vector2f forwards(15.f,0.f);
Vector2f gravity(0.f,10.f);


Vector2f acceleration = gravity;

IntRect animation[12];

RenderWindow window(VideoMode(sw,sh), "Swingy", Style::Close);
View view(window.getDefaultView());
Vector2f initpos(view.getCenter().x -200.f, view.getCenter().y -100.f);

Texture balltexture;
Sprite ball;
RectangleShape aboveCollider;
RectangleShape belowCollider;
std::vector<RectangleShape> platforms;

void init(){
    srand(time(NULL));

    window.setFramerateLimit(24);
    balltexture.loadFromFile("images/spritesheet.png");
    ball.setOrigin(16.f,32.f);
    ball.setTexture(balltexture);
    ball.setPosition(initpos);
    for(int i = 0; i < 12; i++){
        animation[i] = IntRect(i*32,0,32,32);
    }

    aboveCollider.setFillColor(Color::Red);
    aboveCollider.setPosition(Vector2f(ball.getPosition().x,ball.getPosition().y-80.f));
    aboveCollider.setSize(Vector2f(1.f,64.f));

    belowCollider.setFillColor(Color::Blue);
    belowCollider.setPosition(Vector2f(ball.getPosition().x,ball.getPosition().y-16.f));
    belowCollider.setSize(Vector2f(1.f,64.f));
    
    //for testing

    
    RectangleShape r;
    r.setSize(Vector2f(sw,5.f));
    r.setPosition(Vector2f(view.getCenter().x-(sw/2),view.getCenter().y+(sh/2)-5));
    r.setFillColor(Color::Red);
    platforms.push_back(r);
    

}

float dist(Vector2f v){
    return sqrt(v.x*v.x + v.y*v.y);
}

Vector2f normalize(Vector2f v){
    float d = dist(v);
    return Vector2f(v.x/d, v.y/d);
}

void updateBall(){
    if(it == 12)
        it = 0;

    ball.setTextureRect(animation[it]);

    

    if(collision == 0){
        if(grav)
            acceleration = acceleration + gravity;
        else
            acceleration = acceleration - gravity;
    }
    else if (collision == 1){
        if(grav){            
            acceleration = zero;
            ball.setPosition(ball.getPosition().x,colliding.getPosition().y);
        }
        else
            acceleration = acceleration - gravity;
    }else if (collision == 2){
        if(grav)
            acceleration = acceleration + gravity;
        else{
            acceleration = zero;
            ball.setPosition(ball.getPosition().x,colliding.getPosition().y+5+32);
        }
    }

    velocity = acceleration + forwards;

    ball.setPosition(ball.getPosition() + velocity);    

    //for testing
    if(collision == 3){
        ball.setPosition(view.getCenter());
    }

    aboveCollider.setPosition(Vector2f(ball.getPosition().x,ball.getPosition().y-80.f));   

    
    belowCollider.setPosition(Vector2f(ball.getPosition().x,ball.getPosition().y-16.f));

    view.setCenter(ball.getPosition().x + 200.f, view.getCenter().y);

}

void collisionDetection(){
    for(RectangleShape platform : platforms){
        if(belowCollider.getGlobalBounds().intersects(platform.getGlobalBounds())){
            collision = 1;
            colliding = platform;
            return;
        }else
        if(aboveCollider.getGlobalBounds().intersects(platform.getGlobalBounds())){
            collision = 2;
            colliding = platform;
            return;
        }
        
    }
    collision = 0;
}

void updatePlatforms(){

    float last = 0.f;

    if(!platforms.empty())
        last = (view.getCenter().x + (sw/2)) - (platforms.back().getPosition().x+platforms.back().getSize().x);

    if (last >= 0.f ){

        RectangleShape newR;

        if(prev){
            newR.setPosition(Vector2f(view.getCenter().x+(sw/2), view.getCenter().y+(sh/2)-5));
            prev = 0;
        }
        else{
            newR.setPosition(Vector2f(view.getCenter().x+(sw/2), view.getCenter().y-(sh/2)));
            prev = 1;
        }

        newR.setFillColor(Color::Red);
        
        newR.setSize(Vector2f(200+ (rand() % 100), 5.f));
        platforms.push_back(newR);

    } 

}

void render(){
    window.clear();

    for(unsigned i = 0; i < platforms.size(); i++){
        window.draw(platforms[i]);
    }

    window.draw(ball);

    //for testing
    //window.draw(aboveCollider);
    //window.draw(belowCollider);

    window.display();
}

int main(){

    init();
    //collision = 3;
    
    while(window.isOpen()){

        Event e;
        while(window.pollEvent(e)){

            if (e.type == Event::Closed)
                window.close();

            if(e.type == Event::KeyPressed){
                if((e.key.code == Keyboard::Space) && pastFlip > 10){
                    pastFlip = 0;
                    if(grav)
                        grav = 0;
                    else
                        grav = 1;
                }
                

            }



        }


        window.setView(view);

        render();

        
        updateBall();
        collisionDetection();
        updatePlatforms();
        it++;
        pastFlip++;
        forwards.x+=.01f;
    }



    return 0;
}