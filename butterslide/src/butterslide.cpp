#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <random>
//to compile & run
// g++ butterslide.cpp -o butterslide -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio && ./butterslide

//setterings
sf::ContextSettings settings;

//sounds
sf::SoundBuffer newGameSound;
sf::Sound newGamebing;
sf::Music music;

//shapes
sf::RectangleShape grayblock1;
sf::RectangleShape grayblock2;
sf::RectangleShape butter;
sf::RectangleShape newGameButton;
sf::RectangleShape StarTrail;
sf::CircleShape glowCircle;

//colors
sf::Color gray(150, 150, 150);
sf::Color background(0,0,0); 
sf::Color trailcolor(255,255,0);
sf::Color glow(64,64,38,225);
sf::Color BlockRed;
sf::Color PulseGate;

//fonts & text
sf::Font font;
sf::Text newGameText;
sf::Text gameOverText;
sf::Text dist;

//blocks and trails
std::vector<sf::RectangleShape> blocks;
std::vector<sf::RectangleShape> trail;
std::vector<sf::RectangleShape> particles;


//powerups
std::vector<std::pair<int,sf::CircleShape>> powerups;

//variables
bool gameover = false;
int input = 0;
float dx = 0;
float dy = 0;
float next6000 = 0;
float x = 300.f;
float y = 300.f;
const float intitaly = 300.f;
float distance = 0;
int difficulty_scale=150;
int score = 0;
float powerupdist = 0.f;
int currentPower = 0;
int rainbow = 0;
int pulseblock = 0;
int frame60 = 0;
int radius_glow = 0;
bool pulseGate = false;

//window construction
sf::RenderWindow window(sf::VideoMode(600, 800), "ButterSlide",sf::Style::Close);
int defaultXPos = (sf::VideoMode::getDesktopMode().width)/2-300;
int defaultYPos = (sf::VideoMode::getDesktopMode().height)/2-400;

//view construction
sf::View view2(sf::Vector2f(x, y), sf::Vector2f(600.f, 800.f));
sf::Event event;

void init(){
    //variable init
    gameover = false;
    input = 0;
    dx = 0;
    dy = 0;
    next6000 = 0;
    x = 300.f;
    y = 300.f;
    distance = 0;
    score = 0;
    frame60=0;
    powerupdist = 0;
    currentPower = 0;
    rainbow = 0;
    
    //colors
    background.r = 0;
    background.g = 0;
    background.b = 0;

    //antialias
    settings.stencilBits = 8;

    //grayblock
    grayblock1.setSize(sf::Vector2f(15,800));       
    grayblock1.setFillColor(gray);
    grayblock2.setSize(sf::Vector2f(15,800));
    grayblock2.setFillColor(gray);

    //butter construction
    butter.setSize(sf::Vector2f(10,20));
    butter.setFillColor(sf::Color::Yellow);
    butter.setOutlineColor(sf::Color::White);
    butter.setPosition(sf::Vector2f(x,y));
    butter.setOutlineThickness(2);

    //butterglow
    glowCircle.setFillColor(glow);
    glowCircle.setRadius(40.f);

    //new game button
    newGameButton.setSize(sf::Vector2f(200.f,100.f));
    newGameButton.setFillColor(sf::Color::Yellow);
    newGameButton.setOutlineColor(sf::Color::White);
    newGameButton.setOutlineThickness(2);

    //new game text
    newGameText.setFont(font);
    newGameText.setString("Play Again");
    newGameText.setStyle(sf::Text::Bold);
    newGameText.setCharacterSize(24);    
    newGameText.setFillColor(sf::Color::Black);

    //game over text
    gameOverText.setFont(font);
    gameOverText.setStyle(sf::Text::Bold);
    gameOverText.setCharacterSize(36); 
    gameOverText.setString("Game Over");
    gameOverText.setFillColor(sf::Color::Red);

    //distance number text
    dist.setFont(font);
    dist.setCharacterSize(20);
    dist.setFillColor(sf::Color::White);

    //window framerate & keyrepeat disabler
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);
    view2.setSize(sf::Vector2f(600.f, 800.f));
    view2.setCenter(sf::Vector2f(x,y));
    window.setView(view2);
    window.clear(background);    

    //clearing prev vectors
    blocks.clear();
    powerups.clear();
    trail.clear();
    particles.clear();

    //sounds
    newGamebing.setBuffer(newGameSound);

    //Screen Position
    window.setPosition(sf::Vector2i(defaultXPos + rand() % 25, defaultYPos + rand() % 25));
}

bool collide(){    
    for(long unsigned int i = 0;i<blocks.size();i++){
        if(butter.getGlobalBounds().intersects(blocks[i].getGlobalBounds())){                
            if(dy<0)
                dy=5;
            window.setPosition(sf::Vector2i(defaultXPos + rand() % 5, defaultYPos + rand() % 5));
            return true;
        }            
    }
    return false;
}

void setTrailColor(int style){
    //style 0
    if(style == 0){
        trailcolor.r=255;
        trailcolor.g=255;
        trailcolor.b=abs(dy)*12+abs(dx)*6;
    }
    if(style > 0){
        rainbow++;
        if(rainbow>12)
            rainbow=0;
        
        if (rainbow<2){
            trailcolor.r=255;
            trailcolor.g=75;
            trailcolor.b=75;
        }else if (rainbow<4) {       
            trailcolor.r=255;
            trailcolor.g=82+50;
            trailcolor.b=75;
        }              
        else if (rainbow<6){
            trailcolor.r=255;
            trailcolor.b=255;
            trailcolor.g=75;
        }
        else if(rainbow<8){
            trailcolor.r=75;
            trailcolor.b=75;
            trailcolor.g=255;
        }else if(rainbow<10){
            trailcolor.r=75;
            trailcolor.b=255;
            trailcolor.g=75;
        }else if(rainbow<11){
            trailcolor.r=136+50;
            trailcolor.b=255;
            trailcolor.g=75;
        }
        else{        
            trailcolor.r=152+50;
            trailcolor.g=75;
            trailcolor.b=255;            
        }
    }
}

void changeBlockColor(){

    BlockRed.r = 50+score/50;
    BlockRed.g = 50;
    BlockRed.b = 255-score/150;
}

int pulse(int max, int min, int value, int rate)
{
    if(value >=max)
        pulseGate = true;
    if(value <=min)
        pulseGate = false;
    if(!pulseGate)
        value+=rate;
    else
        value-=rate;
        return(value);
}

void endScreen(){
    window.clear(sf::Color::Black);
    gameOverText.setPosition(200.f,view2.getCenter().y-100);
    newGameButton.setPosition(200.f,view2.getCenter().y+100);
    newGameText.setPosition(235.f,view2.getCenter().y+130);
    dist.setPosition(245.f,view2.getCenter().y);
    window.draw(gameOverText);
    window.draw(newGameButton);
    window.draw(newGameText);            
    window.draw(dist);
    gameover = true;  
    window.display();
}

void glowChanger(){
    float blob = (rand() % ((( 2 - (0)) + 1 ) + (0)));
    float pulse_size = pulse(40, 30, radius_glow, blob);
    radius_glow = pulse_size;
    glowCircle.setRadius(pulse_size);
    glowCircle.setPosition(butter.getPosition().x-23-(radius_glow/5),butter.getPosition().y-17-(radius_glow/5));
    
    //colorshift
    if(currentPower!=0){
        glow.r = 4*(radius_glow);
        glow.g = 2*(radius_glow);
        glow.b = 3*(radius_glow);
        
    }else{
        glow.r = 60*(radius_glow/12);        
        glow.g = 60*(radius_glow/12);
        glow.b = 34*(radius_glow/12);
    }
    glowCircle.setFillColor(glow);
}

void particlesadd(){
    for(int i = 0; i < 100;i++){
        sf::RectangleShape particle;
        particle.setFillColor(trailcolor);
        particle.setSize(sf::Vector2f(2.f,2.f));
        particle.setPosition(butter.getPosition().x,butter.getPosition().y-5);   
        particles.push_back(particle);
    }
}

void physics(bool collision){
    //do da physics
    if(input == 0){
        butter.setRotation(0);
        if(dx>0)
            dx-=.1;
        else if (dx<0)
            dx+=.1;
        if(dy<8 ){
            dy+=.4;
        
            //y+=5;
        }
    }else if (input == 1){
        butter.setRotation(-15.f);
        if(dx>-8 && !collision )
            dx-=.8;
        if(dy>-8 && !collision )
            dy-=.4;
        else{
            dy+=.4;
            //y+=5;
        }
    }else{
        butter.setRotation(15.f);
        if(dx<8 && !collision)
            dx+=.8;
        if(dy>-8 && !collision)
            dy-=.4;
        else{
            dy+=.4;
            //y+=5;
        }
    }
    //wall side to side collision
    if(currentPower==3){
        if(x<0)
            x=600;
        if(x>600)
            x=0;
    }else{
        if(x<25)
            x=25;
        if(x>565)
            x=565;
    }
    
    //changing butter position and distance
    butter.setPosition(x+=dx, y+=dy);
    if(collision){
        butter.setPosition(x+=dx, y+=dy+5);
        particlesadd();
        music.openFromFile("/usr/bin/BWAP.wav");
        music.play();
    }
    
    glowChanger();
    
    distance = intitaly-y;

    //update score
    if(distance>score)
        score=distance;

    //shift background color

}

void addRandPowerup(){
    float latest = 900.f;
    for(long unsigned int i = 0;i<powerups.size();i++){
        if(powerups[i].second.getPosition().y<latest)
            latest = powerups[i].second.getPosition().y;
    }
    if(currentPower==0 &&latest > view2.getCenter().y+400 && rand()%1000+1==69){
        int which = rand()%3+1;
        sf::CircleShape powerup;
        powerup.setRadius(7.f);
        powerup.setOutlineColor(sf::Color::White);
        powerup.setOutlineThickness(2);
        powerup.setPosition(rand()%500+20,view2.getCenter().y-400);
        if(which==1){
            powerup.setFillColor(sf::Color::Red);
            std::pair<int,sf::CircleShape> powerpair(which,powerup);             
            powerups.push_back(powerpair);
        }else if (which ==2){
            powerup.setFillColor(sf::Color::Blue);
            std::pair<int,sf::CircleShape> powerpair(which,powerup);
            powerups.push_back(powerpair);
        }else if (which==3){
            powerup.setFillColor(sf::Color::Green);
            std::pair<int,sf::CircleShape> powerpair(which,powerup);   
            powerups.push_back(powerpair);
        }
    }
}

void trailadding(){
    //adds trail to end
    butter.setOutlineThickness(0);    
    butter.setFillColor(trailcolor);
    trail.push_back(butter);
    butter.setFillColor(sf::Color::Yellow);
    butter.setOutlineThickness(2);
}

void updateBlocks(){
    float latest = 900.f;
    for(long unsigned int i = 0;i<blocks.size();i++){
        if(blocks[i].getPosition().y<latest)
            latest = blocks[i].getPosition().y;
    }
    if(((tan(distance/(cos(distance)+difficulty_scale)))>2.5) && latest > view2.getCenter().y-300){
        sf::RectangleShape block;
        block.setSize(sf::Vector2f(200+rand()%50,5));
        block.setFillColor(BlockRed);
        block.setOutlineColor(sf::Color::Blue);
        block.setOutlineThickness(0);
        block.setPosition(rand()%500-50,view2.getCenter().y-400);
        blocks.push_back(block);
    }
    for(long unsigned int i = 0;i<blocks.size();i++){
        blocks[i].setPosition(blocks[i].getPosition().x,blocks[i].getPosition().y+abs(dy)+4);
        blocks[i].setFillColor(BlockRed);
        if(blocks[i].getPosition().y>view2.getCenter().y+500.f)
            blocks.erase(blocks.begin()+i);
    }
    for(long unsigned int i = 0;i<trail.size();i++){
        if(trail[i].getPosition().y>view2.getCenter().y+500.f)
            trail.erase(trail.begin()+i);
    }
    for(long unsigned int i = 0;i<powerups.size();i++){
        powerups[i].second.setPosition(powerups[i].second.getPosition().x,powerups[i].second.getPosition().y+1.5);
        if(butter.getGlobalBounds().intersects(powerups[i].second.getGlobalBounds())){
            currentPower = powerups[i].first;
            powerups.erase(powerups.begin()+i);
        }
        if(powerups[i].second.getPosition().y>view2.getCenter().y+500.f)
            powerups.erase(powerups.begin()+i);
    }
    for(long unsigned int i = 0;i<particles.size()/2;i++){
        particles[i].setPosition(particles[i].getPosition().x-(particles.size()/2-i)/3,particles[i].getPosition().y+i);
    }
    for(long unsigned int i = particles.size()/2;i<particles.size();i++){
        particles[i].setPosition(particles[i].getPosition().x+i,particles[i].getPosition().y+(particles.size()/2-i));
    }
    for(long unsigned int i = 0;i<particles.size();i++){
        if(particles[i].getPosition().x>x+50 || particles[i].getPosition().x<x-50
            || particles[i].getPosition().y>y+50 || particles[i].getPosition().y<y-50)
            particles.erase(particles.begin()+i);
    }

}

void powerupdate(){
    if(currentPower!=0)
        powerupdist+=2;
    if(currentPower==1)
        window.setFramerateLimit(30);
    if(currentPower==2)
        window.setFramerateLimit(80);
    if(powerupdist>1000){
        powerupdist=0;
        currentPower=0;
        window.setFramerateLimit(60);
    }
}

void backgroundShift(){
    next6000+=score/1000;
    if(next6000>6000)
        next6000=0;
    if(next6000>4000){
        background.b = 200;
        background.g = 200;
        background.r = (next6000-4000)/10.0;
    }else if (next6000>2000){
        background.b=200;
        background.g = (next6000-2000)/10.0;
    }else{
        background.b=next6000/10.0;
    }        
}

void drawAll(){
    window.draw(glowCircle);
    for(long unsigned int i = 0;i<trail.size();i++)
        window.draw(trail[i]);
    for(long unsigned int i = 0;i<powerups.size();i++)
        window.draw(powerups[i].second);
    for(long unsigned int i = 0;i<blocks.size();i++)
        window.draw(blocks[i]);
    for(long unsigned int i = 0;i<particles.size();i++)
        window.draw(particles[i]);    
    window.draw(butter); 
    window.draw(dist);
    if(currentPower!=3){
        window.draw(grayblock1);
        window.draw(grayblock2);
    }
}

int main()
{
    //font     
    if (!font.loadFromFile("/usr/bin/arial.ttf"))
        std::cout << "arial file no likey" <<std::endl;   
        
    //fixes random
    srand(time(NULL));

    //initializes variables
    init();
    
    while (window.isOpen()){

        // check all the window's events that were triggered since the last iteration of the loop        
        while (window.pollEvent(event)){            
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
            if(event.type == sf::Event::KeyReleased){
                if((event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D) && input == 2)
                    input = 0;
                if((event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A) && input == 1)                    
                    input = 0;
            }           
            if(event.type == sf::Event::KeyPressed){
                if((event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D))
                    input = 2;            
                if((event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A))
                    input = 1;
            }                       
            if(gameover && sf::Mouse::isButtonPressed(sf::Mouse::Left)        
            && sf::Mouse::getPosition(window).x>200.f && sf::Mouse::getPosition(window).x<400.f
            && sf::Mouse::getPosition(window).y>500.f && sf::Mouse::getPosition(window).y<600.f){               
                newGamebing.play();
                init();              
            }                         
        }
        //game over  
        if(gameover || butter.getPosition().y>view2.getCenter().y+400.f){
            endScreen();
            continue;
        }

        frame60++;
        if(frame60>=60)
            frame60=0;

        addRandPowerup();    
        
        physics(collide());
        //adds and erases the red blocks        

        updateBlocks();

        setTrailColor(currentPower);

        changeBlockColor();

        trailadding();

        //backgroundShift();

        powerupdate();

        //updates view       
        window.clear(background);
        if(y<view2.getCenter().y-50 && !collide())
            view2.setCenter(300.f,view2.getCenter().y+dy);        
        
        //sets siderails 
        grayblock1.setPosition(0,view2.getCenter().y-400);
        grayblock2.setPosition(585,view2.getCenter().y-400);
        dist.setPosition(400.f,view2.getCenter().y+350.f);
        
        //displays score
        dist.setString("Score: "+std::to_string(int(score)));

        //updates the view
        window.setView(view2);

        //draws all objects
        drawAll();

        //displays the current frame
        window.display();
    }
    return 0;
}
