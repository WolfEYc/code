#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

using namespace sf;

using surface = std::pair<Vector2f,Vector2f>;

void printVector2f(Vector2f v){
    std::cout << "("<< v.x << "," << v.y << ")" << std::endl;
}

CircleShape triangle, triangle2, triangle3;
RenderWindow window(VideoMode(600,600), "test", Style::Close);

std::vector<CircleShape> getPts(CircleShape tri){
    std::vector<CircleShape> pts;
    CircleShape pt;
    pt.setOrigin(2.f,2.f);
    pt.setRadius(2.f);
    pt.setFillColor(Color::Red);

    for(unsigned i = 0; i < tri.getPointCount(); i++){
      pt.setPosition(tri.getTransform().transformPoint(tri.getPoint(i)));
      pts.push_back(pt);  
    }

    return pts;
    
}

Vector2f getPoint(CircleShape shape, unsigned i){
    return shape.getTransform().transformPoint(shape.getPoint(i));
}

std::vector<surface> getWalls(CircleShape shape){
    std::vector<surface> ws;
    unsigned i;
    for(i = 0; i < shape.getPointCount()-1; i++){
        ws.push_back({getPoint(shape,i),getPoint(shape,i+1)});
    }
    ws.push_back({getPoint(shape,0),getPoint(shape,shape.getPointCount()-1)});
    return ws;
}

std::vector<VertexArray> walls (CircleShape shape){
    std::vector<surface> ws = getWalls(shape);
    std::vector<VertexArray> va;
    VertexArray wall(LinesStrip,2);
    for(surface s : ws){     
        wall[0].position = s.first;
        wall[1].position = s.second;
        wall[0].color = Color::Blue;
        wall[0].color = Color::Blue;
        va.push_back(wall);
    }
    return va;
}

void render(){

    window.clear();

    std::vector<CircleShape> tripts = getPts(triangle);
    std::vector<CircleShape> tri2 = getPts(triangle2);
    std::vector<CircleShape> tri3 = getPts(triangle3);

    std::vector<VertexArray> tri2walls = walls(triangle2);

    window.draw(triangle);
    window.draw(triangle2);
    window.draw(triangle3);

    for(unsigned i = 0; i < tripts.size(); i++){
        window.draw(tripts[i]);
    }

    for(unsigned i = 0; i < tri2.size(); i++){
        window.draw(tri2[i]);
    }
    for(unsigned i = 0; i < tri3.size(); i++){
        window.draw(tri3[i]);
    }

    for(unsigned i = 0; i < tri2walls.size(); i++){
        window.draw(tri2walls[i]);
    }
    
    window.display();

}

int main(){
    triangle.setRadius(10.f);
    triangle.setPointCount(3);
    triangle.setFillColor(Color::Green);
    triangle.setOrigin(10.f,10.f);

    triangle2 = triangle;
    triangle3 = triangle;

    triangle.setPosition(100.f,100.f);
    triangle2.setPosition(200.f,200.f);
    triangle3.setPosition(300.f,300.f);

    triangle2.setRotation(15);
    triangle3.setRotation(-30);

    triangle2.setPointCount(4);

    


    

    while(window.isOpen()){

        Event event;
        while(window.pollEvent(event)){
            if (event.type == Event::Closed)
            window.close();
        }

        render();

    }
    /*
    Vector2f midpoint (5.f,5.f), origin (3.f,2.f);

    Vector2f myendpt, otherendpt, weirdpt;

    myendpt.x = midpoint.x + (midpoint.x - origin.x);
    myendpt.y = midpoint.y + (midpoint.y - origin.y);

    otherendpt = midpoint + (midpoint - origin);
    
    weirdpt = (2.f,2.f)*midpoint-origin;

    printVector2f(myendpt);
    printVector2f(otherendpt);
    printVector2f(weirdpt);
    */

   

   return 0;
}
