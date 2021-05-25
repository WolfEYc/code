#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

using namespace sf;

unsigned screenx = 600, screeny = 600, fps = 24, level = 3, maxric = 8, curr = 0, wallBuild = 0;
bool rclicking = 0, shot = 0, showMenu = 0, mainMenu = 0, targetPlace = 0;

std::vector<VertexArray> walls;
std::vector<RectangleShape> enemies;
std::vector<bool> whoisHit;
std::vector<VertexArray> shots(maxric); 

CircleShape pivot, gun;
RectangleShape enemy(Vector2f(10.f,20.f));
VertexArray newWall(LinesStrip,2);

Texture buildText, placeText, backText, delWalltext, delTargettext;
Sprite buildwall, placeTarget, goBack, delWall, delTarget;

RenderWindow window(VideoMode(screenx,screeny), "Ricochet", Style::Close);

struct leveld
{
    Vector2f center;
    std::vector<RectangleShape> enemies;
    std::vector<VertexArray> walls;
};

leveld level1, level2, custom;

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


    for(unsigned i = 0; i < level1.walls.size(); i++){
        level1.walls[i][0].color = Color::Red;
        level1.walls[i][1].color = Color::Red;
    }

    custom.walls = level1.walls;
    custom.center = level1.center;

    level1.walls.push_back(leftarrow);
    level1.walls.push_back(rightarrow);

    //enemies

    enemy.setFillColor(Color::Green);
    enemy.setPosition(100.f,100.f);

    level1.enemies.push_back(enemy);

    enemy.setPosition(screenx-100.f,100.f);
    level1.enemies.push_back(enemy);

    enemy.setOrigin(5.f,10.f);
}

float dist(Vector2f v){
    return sqrt(v.x*v.x+v.y*v.y);
}

bool segmentIntersectsRectangle(const sf::FloatRect& rect,
    const sf::Vector2f& a_p1, const sf::Vector2f& a_p2)
{
    // Find min and max X for the segment
    auto minX = std::min(a_p1.x, a_p2.x);
    auto maxX = std::max(a_p1.x, a_p2.x);

    // Find the intersection of the segment's and rectangle's x-projections
    if (maxX > rect.left + rect.width) {
        maxX = rect.left + rect.width;
    }

    if (minX < rect.left) {
        minX = rect.left;
    }

    // If Y-projections do not intersect then there's no intersection
    if (minX > maxX) { return false; }

    // Find corresponding min and max Y for min and max X we found before
    auto minY = a_p1.y;
    auto maxY = a_p2.y;

    auto dx = a_p2.x - a_p1.x;
    if (std::abs(dx) > 0.0000001f) {
        auto k = (a_p2.y - a_p1.y) / dx;
        auto b = a_p1.y - k * a_p1.x;
        minY = k * minX + b;
        maxY = k * maxX + b;
    }

    if (minY > maxY) {
        std::swap(minY, maxY);
    }

    // Find the intersection of the segment's and rectangle's y-projections
    if (maxY > rect.top + rect.height) {
        maxY = rect.top + rect.height;
    }

    if (minY < rect.top) {
        minY = rect.top;
    }

    // If Y-projections do not intersect then there's no intersection
    if (minY > maxY) { return false; }
    return true;
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
    case 3:
        gun.setPosition(custom.center);
        walls = custom.walls;
        enemies = custom.enemies;
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
    pivpos.y-=10.f;
    pivpos.x+=10.f;
    pivot.setPosition(pivpos);

    buildText.loadFromFile("resources/buildwall.png");
    placeText.loadFromFile("resources/placeTarget.png");
    backText.loadFromFile("resources/goback.png");
    delTargettext.loadFromFile("resources/delTarget.png");
    delWalltext.loadFromFile("resources/delWall.png");
    

    buildwall.setTexture(buildText);
    placeTarget.setTexture(placeText);
    goBack.setTexture(backText);
    delTarget.setTexture(delTargettext);
    delWall.setTexture(delWalltext);

    goBack.setPosition(Vector2f(25.f,25.f));
    buildwall.setPosition(Vector2f(75.f,25.f));
    placeTarget.setPosition(Vector2f(125.f,25.f));
    delWall.setPosition(Vector2f(175.f,25.f));
    delTarget.setPosition(Vector2f(225.f,25.f));    


}

void render(){
    window.clear();

    Vector2i windowoffset = window.getPosition();
    windowoffset.y+=30;
    Vector2f mousepos = Vector2f(Mouse::getPosition()-windowoffset);

    //draw somethin
    if(!shot){        
        for(unsigned line = 0; line < maxric; line++){
            window.draw(shots[line]);
        }        
    }else{        
        for(unsigned line = 0; line < curr; line++){
            window.draw(shots[line]);
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

    if(showMenu){
        window.draw(goBack);
        if(level == 3){
            window.draw(buildwall);
            window.draw(placeTarget);
            window.draw(delWall);
            window.draw(delTarget);            
        }
    }

    if(wallBuild == 2){
        newWall[1].position = mousepos;
        window.draw(newWall);
    }

    if(targetPlace){
        enemy.setPosition(mousepos);
        window.draw(enemy);
    }
    

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

    float bM = (wallb.y-walla.y)/(wallb.x-walla.x);
    
    float pM = -1.f/(bM); //perpendicular slope (sign flipped inverse)
    float pB = ipoint.y - (pM*ipoint.x); //y-mx = b

    Vector2f y_int(0.f,pB); //yint of perp line
    
    Vector2f midpoint = calcPerpIntersect(a1, y_int, ipoint);

    return (2.f,2.f) * midpoint - a1;
}

void calcShot(){

    Vector2f a1 = gun.getPosition();
    Vector2f a2 = pivot.getPosition();

    std::vector<VertexArray> thisshots;
    whoisHit = std::vector<bool> (enemies.size(), 0);

    for(unsigned i = 0; i < enemies.size(); i++){
        enemies[i].setFillColor(Color::Green);
    }

    unsigned wallhit;
    for(unsigned i = 0; i < maxric; i++){

        wallhit = firstCollision(a1,a2,wallhit);

        if(wallhit == 69)
            break;

        Vector2f b1 = walls[wallhit][0].position;
        Vector2f b2 = walls[wallhit][1].position;

        Vector2f collision_v = calcIntersectVector(a1,a2,b1,b2);

        for(unsigned i = 0; i < enemies.size(); i++){
            if(segmentIntersectsRectangle(enemies[i].getGlobalBounds(),a1,collision_v)){
                whoisHit[i] = 1;
                enemies[i].setFillColor(Color::Yellow);        
            }
        }

        VertexArray shot(LineStrip,2);
        shot[0].position = a1;
        shot[0].color = Color(155,135,12);
        shot[1].position = collision_v;
        shot[1].color = Color(155,135,12);

        shots[i] = shot;

        a2 = newPivot(a1,collision_v,b1,b2);
        a1 = collision_v;
    }
}

int main(){

    init();
    
    while(window.isOpen()){

        Event e;
        while(window.pollEvent(e)){

            if (e.type == Event::Closed)
                window.close();

            if(e.type == Event::MouseButtonPressed){ // do shooty stuff
                if(Mouse::isButtonPressed(Mouse::Left)){
                    Vector2i windowoffset = window.getPosition();
                    windowoffset.y+=30;
                    Vector2f newpos = Vector2f(Mouse::getPosition()-windowoffset);

                    if(targetPlace){
                        enemy.setPosition(newpos);
                        enemies.push_back(enemy);
                        targetPlace = 0;
                        showMenu = 1;
                    }else
                    if(wallBuild){
                        wallBuild++;
                        if(wallBuild==2){
                            newWall[0].position = newpos;                                                     
                        }else if(wallBuild == 3){
                            newWall[1].position = newpos;
                            walls.push_back(newWall);
                            showMenu = 1;
                            wallBuild = 0;
                        }else{
                            showMenu = 1;
                            wallBuild = 0;
                        }
                    }else
                    if(showMenu){
                        
                        if(goBack.getGlobalBounds().contains(newpos)){
                            //mainMenu = 1;
                            std::cout << "going back" << std::endl;
                        }

                        if(level==3){
                            if(buildwall.getGlobalBounds().contains(newpos)){
                                showMenu = 0;
                                std::cout << "building wall" << std::endl;
                                wallBuild = 1;
                            }
                            if(placeTarget.getGlobalBounds().contains(newpos)){
                                showMenu = 0;                                
                                std::cout << "placing target" << std::endl;
                                targetPlace = 1;
                            }
                            if(delWall.getGlobalBounds().contains(newpos)){                                                             
                                std::cout << "deleting wall" << std::endl;
                                if(walls.size()>4)
                                    walls.pop_back();
                            }
                            if(delTarget.getGlobalBounds().contains(newpos)){                                                             
                                std::cout << "deleting Target" << std::endl;
                                if(!enemies.empty())
                                    enemies.pop_back();
                            }


                        }

                    }else //cant change pivot if menu is open
                    if(abs(newpos.x-gun.getPosition().x) > 0.12f && abs(newpos.y-gun.getPosition().y) > 0.12f
                        && dist(newpos-gun.getPosition()) > 10.f )
                        pivot.setPosition(Vector2f(Mouse::getPosition()-windowoffset));

                    
                }
                if(Mouse::isButtonPressed(Mouse::Right)){
                    rclicking = 1;
                }

            }
            if(e.type == Event::KeyPressed){
                switch(e.key.code){
                    case Keyboard::Space:
                        if(shot == 0){
                            shot = 1;
                            calcShot();
                        }
                        break;
                    case Keyboard::Tab:
                        if(!mainMenu && !wallBuild && !targetPlace)                        
                            showMenu = !showMenu;
                        
                        break;                

                }
               
            }
            if(e.type == Event::MouseButtonReleased){
                if(!Mouse::isButtonPressed(Mouse::Right)){
                    rclicking = 0;
                }
            }

        }
        if(shot){       
            //std::cout << "Frame: " << frame << std::endl;           
            //std::cout << "Curr: " << curr << std::endl;
  
            curr++;
            if(curr == maxric){
                shot = 0;
                curr = 0;
            }  
        }
 

        


        render();

    }



}
