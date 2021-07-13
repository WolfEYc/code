#include "ParticleSystem.cpp"

unsigned screenx = 1280, screeny = 720, cellsize = 20, fps = 30, frame = 0, counter = 0, parton = 0;
bool editmode = 1;
bool movement[4];

RenderWindow window(VideoMode(screenx, screeny), "Rocketslime", Style::Close);
View view(window.getDefaultView());
static Clock c;
ParticleSystem particles(1000);

grid blocks(cellsize);
slime player(view.getCenter(),"Green_Slime.png");
slime rocket(player.getPosition(), "pew.png");

Vector2i mousepos;

void getMousepos(){
    mousepos = Vector2i(window.mapPixelToCoords(Mouse::getPosition(), view));
    Vector2i windowoffset = window.getPosition();
    windowoffset.y+=30;
    mousepos = Vector2i(mousepos - windowoffset);
}

void update(){

    if(editmode)
        return;

    player.updateForces(movement);

    int phit = blocks.collisionSurface(player.getHitReg(), player.getPosition(), player.getNextPosition(), player.getRadius(), false);

    if(phit != -1){
        player.collideWith(phit);
    }else
        player.updatePos();
    


    if(rocket.bound){
        rocket.aim(Vector2f(mousepos));
        rocket.setPosition(player.getPosition());
    }else {
        int rhit = blocks.collisionSurface({{rocket.getPosition(), rocket.getNextPosition()}} ,rocket.getPosition(), rocket.getNextPosition(), rocket.getRadius(), true);

        if(rhit != -1){
            particles.setEmitter(blocks.getGaypoint());
            player.reactTo(blocks.getGaypoint());
            rocket.bound = 1;
            rocket.reset(player.getPosition());
            parton = 1;
            c.restart();
            particles.reset();
        }else
            rocket.updatePos();
            
    }

}

void render(){
    view.setCenter(player.getPosition());
    window.clear();
    blocks.draw(window);
    if(!rocket.onCd() || !rocket.bound)
        rocket.drawSlime(window);
    if(parton)
        window.draw(particles);
    player.drawSlime(window);
    window.display();
}

void events(){
    Event e;
    while(window.pollEvent(e)){
        if (e.type == Event::Closed)
            window.close();

        if (e.type == Event::KeyPressed){
            switch(e.key.code){
                case Keyboard::E:
                    editmode = !editmode;
                    break;

                case Keyboard::W:
                    movement[0] = 1;
                    break;
                case Keyboard::A:
                    movement[1] = 1;
                    break;
                case Keyboard::S:
                    movement[2] = 1;
                    break;
                case Keyboard::D:
                    movement[3] = 1;
                    break;

                default:
                    break;
            }
        }

        if(e.type == Event::KeyReleased){
            switch(e.key.code){
                case Keyboard::W:
                    movement[0] = 0;
                    break;
                case Keyboard::A:
                    movement[1] = 0;
                    break;
                case Keyboard::S:
                    movement[2] = 0;
                    break;
                case Keyboard::D:
                    movement[3] = 0;
                    break;

                default:
                    break;
            }
        }
            

        if(e.type == Event::MouseButtonPressed){
            
            if(editmode){           
                blocks.add(mousepos);
            }else{
                if(!rocket.onCd() && rocket.bound){
                    rocket.bound = 0;
                    rocket.shoot(Vector2f(mousepos));
                    counter = 1;
                    rocket.cooldown();
                }
            }
        }
    }

    if(parton && editmode){
        c.restart();
    }

    if(counter && !editmode)
        counter++;

    if(parton && !editmode){
        parton++;
        particles.update(c.restart());
    }


    if(counter == fps){
        if(!rocket.bound){
            rocket.bound = 1;
            rocket.reset(player.getPosition());
        }
        rocket.cooldown();
        counter = 0;
    }

    if(parton == fps){
        parton = 0;
    }
    
    if(++frame == fps){
        frame = 0;     
    }

}

void init(){
    window.setFramerateLimit(fps);
    window.setVerticalSyncEnabled(true);
    window.setView(view);
}

int main(){

    init();

    while(window.isOpen()){
        getMousepos();
        events();
        update();
        render();
    }

    return 0;
}
