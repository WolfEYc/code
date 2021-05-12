#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <bits/stdc++.h>
using namespace sf;

/*
Isaac Wolf
To compile and run
g++ conways.cpp -o conways -lsfml-graphics -lsfml-window -lsfml-system && ./conways
*/

unsigned sw = VideoMode::getDesktopMode().width, sy = VideoMode::getDesktopMode().height;
unsigned cores = std::thread::hardware_concurrency();
RenderWindow window(VideoMode::getDesktopMode(), "Conways", Style::Default);
View view;

//int zoom = 10;
int scale = 10;
bool pause = 1, move = 0, placing = 0, removing = 0;
Vector2i windowOffset(window.getPosition());
Vector2f prevOffset(0.f,0.f);
const Color gray(100,100,100);

std::vector<Vector2i> points;
std::unordered_set<std::string> mergedPts;
std::vector<std::vector<Vector2i>> punmerged(2);
std::vector<std::vector<Vector2i>> bunmerged(cores);
std::unordered_map<std::string, unsigned> bPoints;


void place(Vector2i p){
    std::vector<Vector2i>::iterator it = std::find(points.begin(),points.end(),p);
    if(it == points.end())
        points.push_back(p);
}

void remove(Vector2i p){
    std::vector<Vector2i>::iterator it = std::find(points.begin(),points.end(),p);
    if(it != points.end())
        points.erase(it);    
          
}

std::string V2S(Vector2i v){    
    return std::to_string(v.x) + "," + std::to_string(v.y);    
}

Vector2i S2V(std::string s){
    std::stringstream ss(s);
    int x, y;
    char comma;
    ss >> x >> comma >> y;
    return Vector2i(x,y);
}

void broadcast(unsigned section){
    unsigned zone = points.size()/cores;
    unsigned extra = 0;

    if(section == cores){
        extra = points.size()-(cores*zone);
    }
    
    for(unsigned i = (section-1)*zone; i < section*zone+extra; i++){
        for(int y = points[i].y-1; y <= points[i].y+1; y+=1){
            for(int x = points[i].x-1; x <= points[i].x+1; x+=1){                
                //bPoints[V2S(Vector2i(x,y))]++;
                bunmerged[section-1].push_back(Vector2i(x,y));
            }
        }
    }    
}

void mergebp(){
    for(unsigned i = 0; i < cores; i++){
        for(unsigned j = 0; j < bunmerged[i].size(); j++){
            bPoints[V2S(bunmerged[i][j])]++;
        }
        bunmerged[i].clear();
    }       
}

void mergepts(){
    for(unsigned i = 0; i != 2; i++){
        for(unsigned j = 0; j != punmerged[i].size(); j++){
            mergedPts.insert(V2S(punmerged[i][j]));
        }
        punmerged[i].clear();
    }
    points.clear();
    for(auto i : mergedPts)
        points.push_back(S2V(i));

    mergedPts.clear();
}

/*
    Any live cell with two or three live neighbours survives.
    Any dead cell with three live neighbours becomes a live cell.
    All other live cells die in the next generation. Similarly, all other dead cells stay dead.
*/

void updateDead(){
    for(auto itr : bPoints){
        Vector2i p = S2V(itr.first);
        if(itr.second==3)
            punmerged[1].push_back(p);
    }  
}

void updateLive(){    
    unsigned size = points.size();
    for(unsigned i = 0; i < size; i++){         
        int n = bPoints[V2S(points[i])] - 1;
        if(n == 2 || n == 3)
            punmerged[0].push_back(points[i]);               
    }        
}

void render(){
    for(Vector2i point : points){
        RectangleShape rect(Vector2f(scale,scale));
        rect.setPosition(Vector2f(point*scale-windowOffset));        
        rect.setFillColor(Color::Red);
        window.draw(rect);
    }
    if(pause){
        Vector2f origin = window.mapPixelToCoords(Vector2i(0,0),view);

        origin.x=(int(origin.x)/scale)*scale;
        origin.y=(int(origin.y)/scale)*scale;
        //int zoomscale = (zoom*zoom*zoom);
        
        //std::cout << origin.x << ", " << origin.y << std::endl;  
        for(int y = origin.y+windowOffset.y; y < window.getSize().y+origin.y+windowOffset.y; y+=scale){
            VertexArray va(LineStrip,2);
            va[0] = Vector2f(origin.x,y-windowOffset.y);
            va[1] = Vector2f(window.getSize().x+origin.x,y-windowOffset.y);
            va[0].color = gray;
            window.draw(va);
        }
        for(int x = origin.x+windowOffset.x; x < window.getSize().x+origin.x+windowOffset.x; x+=scale){
            VertexArray va(LineStrip,2);
            va[0] = Vector2f(x-windowOffset.x,origin.y);
            va[1] = Vector2f(x-windowOffset.x,window.getSize().y+origin.y);
            va[0].color = gray;
            window.draw(va);
        }

    }
}
//b

void handlePlace(Vector2i clickpos){
    //Vector2i worldpos = clickpos-windowOffset;
    Vector2i worldpos = Vector2i(window.mapPixelToCoords(clickpos,view));
    
    /*if(zoom < 10){
        worldpos.y+=10;
        if(zoom < 5){
            worldpos.y+=10;
        }
    }else if (zoom > 10){
        worldpos.y-=10;
    }*/

    if(scale > 10){
        worldpos.y+=scale;
        if(scale > 25){
            worldpos.y+=scale;
        }
    }

    //std::cout << clickpos.x << "," << clickpos.y << std::endl;
    //std::cout << worldpos.x << "," << worldpos.y << std::endl;
    place(Vector2i((worldpos.x/scale),(worldpos.y/scale)));
}

void handleRemove(Vector2i clickpos){
    
    //Vector2i worldpos = clickpos-windowOffset;
    Vector2i worldpos = Vector2i(window.mapPixelToCoords(clickpos,view));
    /*if(zoom < 10){
        worldpos.y+=scale;
        if(zoom < 7){
            worldpos.y+=scale;
        }
    }else if (zoom > 10){
        worldpos.y-=scale;
    }*/
    if(scale > 10){
        worldpos.y+=scale;
        if(scale > 25){
            worldpos.y+=scale;
        }
    }

    //std::cout << worldpos.x << "," << worldpos.y << std::endl;
    remove(Vector2i((worldpos.x/scale),(worldpos.y/scale)));
}

void handleMove(Vector2i clickpos){
    if((prevOffset.x!=0.f || prevOffset.y!=0.f))
        view.move(prevOffset - Vector2f(clickpos));        
    
    prevOffset = Vector2f(clickpos);
}

int main(){
    window.setFramerateLimit(15);
    view = window.getDefaultView();
    window.setView(view);

    std::vector<Thread*> broadcasts;
    for(unsigned i = 0; i < cores; i++)
        broadcasts.push_back(new Thread(&broadcast, i+1));

    Thread uLive(&updateLive);
    Thread uDead(&updateDead);
    
    while (window.isOpen())
    {

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if(event.type == Event::Resized){
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                view = View(visibleArea);
                //window.setView(view);
                //windowOffset = window.getPosition();
            }

            if(event.type == Event::MouseWheelScrolled){
                if(event.mouseWheelScroll.delta == 1){
                   if(scale < 30)//zoomout
                        scale++; 
                    //if( > 2)

                        //view.zoom(0.9f);
                        //zoom--;
                    //}      
                }else{
                    if(scale > 5)//zoomout
                        scale--;
                    //if(zoom < 15){
                        //view.zoom(1.1f);
                        //zoom++;
                    //}                    
                }
            }

            if(event.type == Event::MouseButtonPressed){
                if(sf::Mouse::isButtonPressed(Mouse::Left))
                    placing = 1;
                if(sf::Mouse::isButtonPressed(Mouse::Right))
                    move = 1;
            }            

            if(event.type == Event::MouseButtonReleased){                
                prevOffset = Vector2f(0.f,0.f);
                move = 0;
                placing = 0;                
            }

            if(event.type == Event::KeyPressed){
                if(event.key.code == Keyboard::P){                    
                    if(pause)
                        pause = 0;
                    else
                        pause = 1;
                }
                if(event.key.code == Keyboard::R){
                    if(removing)
                        removing = 0;
                    else
                        removing = 1;
                }
                /*
                if(event.key.code == Keyboard::A)
                    view.move(Vector2f(-1,0));
                if(event.key.code == Keyboard::D)
                    view.move(Vector2f(1,0));                 
                if(event.key.code == Keyboard::W)
                    view.move(Vector2f(0,1));
                if(event.key.code == Keyboard::S)
                    view.move(Vector2f(0,-1));
                */ 
            }            
        }

        window.setView(view);
        windowOffset = window.getPosition();        
        windowOffset.x = (windowOffset.x/scale)*scale;
        windowOffset.y = (windowOffset.y/scale)*scale;
        windowOffset.y+=scale*3;

        if(move){
            handleMove(Mouse::getPosition());                     
        }

        if(placing){
            //windowOffset = window.getPosition();
            if(removing)
                handleRemove(Mouse::getPosition());
            else
                handlePlace(Mouse::getPosition());
        }

        if(!pause){        

            for(auto broadcast : broadcasts){
                broadcast->launch();
            }

            for(auto broadcast : broadcasts){
                broadcast->wait();
            }            

            mergebp();

            uDead.launch();
            uLive.launch();

            uDead.wait();
            uLive.wait();

            mergepts();

            bPoints.clear();                       
        }

        
        window.clear(Color::Black);       
        render();
        window.display();
    }
}
