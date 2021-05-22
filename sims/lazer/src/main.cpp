#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

using namespace sf;

#define PI 3.14159265

unsigned screenx = 600, screeny = 600, fps = 30, level = 1, maxric = 18;
bool rclicking = 0;
//std::vector<CircleShape> aimdots;
std::vector<VertexArray> walls;
std::vector<RectangleShape> enemies;
std::vector<std::vector<VertexArray>> shots; 

CircleShape pivot;

CircleShape gun;

RenderWindow window(VideoMode(screenx,screeny), "One Shot", Style::Close);
//i aint movin the camera screw u

struct leveld
{
    Vector2f center;
    std::vector<RectangleShape> enemies;
    std::vector<VertexArray> walls;
};

leveld level1, level2;

void initLevels(){
    level1.center = Vector2f(300.f,500.f);

    VertexArray leftwall(LineStrip,2);
    leftwall[0].position = Vector2f(0.1f,0.1f);
    leftwall[1].position = Vector2f(0.2f,screeny);

    VertexArray topwall(LineStrip,2);
    topwall[0].position = Vector2f(0.1f,0.1f);
    topwall[1].position = Vector2f(screenx,0.2f);

    VertexArray botwall(LineStrip,2);
    botwall[0].position = Vector2f(0.1f,screeny-0.1f);
    botwall[1].position = Vector2f(screenx,screeny-0.2f);

    VertexArray rightwall(LineStrip,2);
    rightwall[0].position = Vector2f(screenx-0.1f,0.1f);
    rightwall[1].position = Vector2f(screenx-0.2f,screeny);

    VertexArray leftarrow(LinesStrip,2);
    leftarrow[0].position = Vector2f (( screenx/2), 100.f );
    leftarrow[1].position = Vector2f (( screenx/2 - 100.f), 200.f );

    VertexArray rightarrow(LinesStrip,2);
    rightarrow[0].position = Vector2f (( screenx/2), 100.f );
    rightarrow[1].position = Vector2f (( screenx/2 + 100.f), 200.f );


    level1.walls.push_back(leftwall);
    level1.walls.push_back(rightwall);
    level1.walls.push_back(topwall);
    level1.walls.push_back(botwall);
    level1.walls.push_back(leftarrow);
    level1.walls.push_back(rightarrow);

    for(unsigned i = 0; i < level1.walls.size(); i++){
        level1.walls[i][0].color = Color::Red;
        level1.walls[i][1].color = Color::Red;
    }
    

}

float dist(Vector2f v){
    return sqrt(v.x*v.x+v.y*v.y);
}

void printVector2f(Vector2f v){
    std::cout << "("<< v.x << "," << v.y << ")" << std::endl;
}

void load(){
    switch (level)
    {
    case 1:
        gun.setPosition(level1.center);
        walls = level1.walls;
        enemies = level1.enemies;
        break;
    
    default:
        break;
    }

}

void init(){ //called once at startup
    initLevels();
    load();
    window.setFramerateLimit(fps);
    gun.setRadius(5.f);
    gun.setOrigin(5.f,5.f);
    gun.setFillColor(Color::Red);
    pivot.setRadius(5.f);
    pivot.setFillColor(Color::Blue);
    pivot.setOrigin(5.f,5.f);
    Vector2f pivpos = gun.getPosition();
    pivpos.y-=1;
    pivpos.x+=1;
    pivot.setPosition(pivpos);
}

void render(){
    window.clear();

    //draw somethin
    for(unsigned i = 0; i < shots.size(); i++){
        for(unsigned line = 0; line < maxric; line++){
            window.draw(shots[i][line]);
        }
    }

    for(unsigned i = 0; i < walls.size(); i++){
        window.draw(walls[i]);
    }

    for(unsigned i = 0; i < enemies.size(); i++){
        window.draw(enemies[i]);
    }

    window.draw(gun);
    window.draw(pivot);

    window.display();
}

Vector2f calcIntersectVector(Vector2f a1, Vector2f a2, Vector2f b1, Vector2f b2){
    float aM = (a2.y-a1.y)/(a2.x-a1.x);
    float aB = a1.y - (aM*a1.x);

    float bM = (b2.y-b1.y)/(b2.x-b1.x);
    float bB = b1.y - (bM*b1.x);

    float left = aM-bM;
    float right = bB-aB;
    float X = right/left;
    float Y = aM*X+aB;

    return Vector2f(X,Y);
}

Vector2f calcPerpIntersect(Vector2f a1, Vector2f b1, Vector2f b2){
    float bM = (b2.y-b1.y)/(b2.x-b1.x);
    
    float pM = -1.f/(bM); //perpendicular slope (sign flipped inverse)
    float pB = a1.y - (pM*a1.x); //y-mx = b

    Vector2f y_int(0.f,pB); //yint of perp line

    return calcIntersectVector(a1,y_int,b1,b2); //return intersection point
}

bool collides (Vector2f a1, Vector2f a2, Vector2f b1, Vector2f b2){
    Vector2f intersection_vector = calcIntersectVector(a1,a2,b1,b2);
    
    float d1 = dist(intersection_vector - b1);
    float d2 = dist(intersection_vector - b2);
    float furthest;

    if(d1 > d2)
        furthest = d1;
    else
        furthest = d2;

    float wall_length = dist(b2-b1);
    
    bool aneg, bneg;
    if((a2 - a1).x > 0)
        aneg = 0;
    else
        aneg = 1;
    
    if((intersection_vector - a1).x > 0)
        bneg = 0;
    else
        bneg = 1;

    

    return bneg == aneg && furthest < wall_length;
   
}

unsigned firstCollision (Vector2f a1, Vector2f a2, unsigned prevwall){
    float closest_intersection = 9999.f;
    unsigned closest_wall = 69;

    for(unsigned w = 0; w < walls.size(); w++){

        if(w == prevwall)
            continue;

        VertexArray wall = walls[w];

        Vector2f b1 = wall[0].position;
        Vector2f b2 = wall[1].position;

        if(collides(a1,a2,b1,b2)){        
            Vector2f ipoint = calcIntersectVector(a1,a2,b1,b2);
            
            float dist_to_intersection = dist(ipoint - a1);
            if(dist_to_intersection < closest_intersection){
                closest_intersection = dist_to_intersection;
                closest_wall = w;
            }        
        }
    }
    return closest_wall;
}

Vector2f newPivot(Vector2f a1, Vector2f ipoint, Vector2f walla, Vector2f wallb){

    //Vector2f perp_for_theta = calcPerpIntersect(a1,walla,wallb);
    float bM = (wallb.y-walla.y)/(wallb.x-walla.x);
    
    float pM = -1.f/(bM); //perpendicular slope (sign flipped inverse)
    float pB = ipoint.y - (pM*ipoint.x); //y-mx = b

    Vector2f y_int(0.f,pB); //yint of perp line
    
    Vector2f midpoint = calcPerpIntersect(a1, y_int, ipoint);

    std::cout << "Midpoint: ";
    printVector2f(midpoint);

    /*
    float adj = dist(midpoint - ipoint);
    float hyp = dist(ipoint - a1);

    //std::cout << adj << " " << hyp << std::endl;

    float theta = acos(adj/hyp);

    //std::cout << theta << std::endl;

    //float shit = (PI-2*theta)/2;

    float X = a1.x*cos(theta);
    float Y = a1.y*sin(theta);
    */
    float X = midpoint.x + (midpoint.x-a1.x);
    float Y = midpoint.y + (midpoint.y-a1.y);

    return Vector2f(X,Y);

}

void calcShot(){
    Vector2f a1 = gun.getPosition();
    Vector2f a2 = pivot.getPosition();

    std::vector<VertexArray> thisshots;

    unsigned wallhit;

    for(unsigned i = 0; i < maxric; i++){

        wallhit = firstCollision(a1,a2,wallhit);

        std::cout << wallhit << " at ";

        Vector2f b1 = walls[wallhit][0].position;
        Vector2f b2 = walls[wallhit][1].position;

        Vector2f collision_v = calcIntersectVector(a1,a2,b1,b2);

        
        printVector2f(collision_v);

        VertexArray shot(LineStrip,2);
        shot[0].position = a1;
        shot[0].color = Color::Yellow;
        shot[1].position = collision_v;
        shot[1].color = Color::Yellow;

        thisshots.push_back(shot);

        a2 = newPivot(a1,collision_v,b1,b2);
        a1 = collision_v;
    }

    shots.push_back(thisshots);

}

void test(){

    Vector2f origin (40.f,20.f);
    Vector2f pivot (20.f,30.f);

    Vector2f walla(1.f,1.f);
    Vector2f wallb(10.f,100.f);

    VertexArray projectile(LineStrip,2);
    VertexArray wall(LinesStrip,2);
    VertexArray newPivo(LinesStrip,2);

    projectile[0].position = origin;
    projectile[0].color = Color::Green;
    
    projectile[1].color = Color::Green;

    wall[0].position = walla;
    wall[0].color = Color::Blue;
    wall[1].position = wallb;
    wall[1].color = Color::Blue;

    Vector2f intersect = calcIntersectVector(origin,pivot, walla,wallb);
    Vector2f newPiv = newPivot(origin,intersect,walla,wallb);

    projectile[1].position = intersect;

    newPivo[0].position = intersect;
    newPivo[0].color = Color::Red;
    newPivo[1].position = newPiv;
    newPivo[1].color = Color::Red;

    std::cout << "Intersect: ";
    printVector2f(intersect);

    std::cout << "New pivot: ";
    printVector2f(newPiv);

    window.draw(projectile);
    window.draw(wall);
    window.draw(newPivo);

    window.display();


}

int main(){

    init();
    //test();
    
    while(window.isOpen()){

        Event e;
        while(window.pollEvent(e)){

            if (e.type == Event::Closed)
                window.close();

            if(e.type == Event::MouseButtonPressed){ // do shooty stuff
                if(Mouse::isButtonPressed(Mouse::Left)){
                    Vector2i windowoffset = window.getPosition();
                    windowoffset.y+=30;

                    pivot.setPosition(Vector2f(Mouse::getPosition()-windowoffset));
                }
                if(Mouse::isButtonPressed(Mouse::Right)){
                    rclicking = 1;
                }

            }
            if(e.type == Event::KeyPressed){
                if(e.key.code == Keyboard::Space){
                    calcShot();

                }
            }
            if(e.type == Event::MouseButtonReleased){
                if(!Mouse::isButtonPressed(Mouse::Right)){
                    rclicking = 0;
                }
            }

        }

        render();

    }



}
