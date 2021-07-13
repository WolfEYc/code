#include "slime.hpp"

slime::slime(){
    coefric = 0.97;
    grav = 0;
    radius = 20;
    hitreg = vector<surface>(5);
    cd = 0;
    bound = 1;
    bouncyness = 25;
    movespeed = 1;
}

slime::slime(Vector2f pos, string texture) : slime(){
    setTexture(texture);
    setPosition(pos);
    setRadius(sprite.getLocalBounds().width/2.f);
}

void slime::setRadius(const float radius){
    this->radius = radius;
}

void slime::setTexture(string texture){
    if(!this->texture.loadFromFile("resources/"+texture)){
        cerr <<"no findy " << texture << " uwu" << endl;
    }
    sprite.setTexture(this->texture);
    sprite.setOrigin(Vector2f(sprite.getLocalBounds().width/2.f, sprite.getLocalBounds().height/2.f));
}

void slime::setPosition(Vector2f pos){
    this->pos = pos;
}

const Vector2f slime::getPosition() const{
    return pos;
}

const Vector2f slime::getNextPosition() const{
    return pos + vel;
}

const float slime::getRadius() const{
    return radius;
}

const FloatRect slime::getBounds() const{
    return sprite.getGlobalBounds();
}

const FloatRect slime::getNextBounds() const{
    Sprite temp = sprite;
    temp.setPosition(pos + vel);
    return temp.getGlobalBounds();
}

void slime::friction(){
    scale(vel, coefric);
}

void slime::collideWith(const int collider){
    if(collider == 0){
        vel.y = -vel.y;
    }
    else if (collider == 1){
        vel.x = -vel.x;
    }
}

//use this to apply outside force like explodyboy
void slime::reactTo(Vector2f expoint){
    float distance = dist(expoint - pos);
    if(distance > 100)
        return;

    float angle = atan2(pos.y - expoint.y, pos.x - expoint.x);

    float X = bouncyness*cos(angle);
    float Y = bouncyness*sin(angle);

    vel += {X, Y};
}

void slime::updateForces(bool* movement){
    vel.y += grav;
    if(movement[0])
        vel.y -= movespeed;
    if(movement[1])
        vel.x -= movespeed;
    if(movement[2])
        vel.y += movespeed;
    if(movement[3])
        vel.x += movespeed;

    friction();
}

void slime::updatePos(){
    
    pos = pos + vel;
}

void slime::cooldown(){
    cd = !cd;
}

void slime::drawSlime(RenderWindow& window){
    sprite.setPosition(pos);
    window.draw(sprite);
}

vector<surface> slime::getHitReg(){
    FloatRect thisframe = getBounds();
    FloatRect nextframe = getNextBounds();

    Vector2f thistl = Vector2f(thisframe.left, thisframe.top);
    Vector2f nexttl = Vector2f(nextframe.left, nextframe.top);

    Vector2f thistr = Vector2f(thisframe.left + thisframe.width, thisframe.top);
    Vector2f nexttr = Vector2f(nextframe.left + nextframe.width, nextframe.top);

    Vector2f thisbr = Vector2f(thisframe.left + thisframe.width, thisframe.top + thisframe.height);
    Vector2f nextbr = Vector2f(nextframe.left + nextframe.width, nextframe.top + nextframe.height);

    Vector2f thisbl = Vector2f(thisframe.left, thisframe.top + thisframe.height);
    Vector2f nextbl = Vector2f(nextframe.left, nextframe.top + nextframe.height);

    
    hitreg[0] = {thistl, nexttl};
    hitreg[1] = {thistr, nexttr};
    hitreg[2] = {thisbr, nextbr};
    hitreg[3] = {thisbl, nextbl};
    hitreg[4] = {pos, pos+vel};

    return hitreg;
    
}

void slime::tipOrigin(){
    
}

void slime::aim(const Vector2f mousepos){
    float angle = atan2(mousepos.y - pos.y, mousepos.x - pos.x);
    sprite.setRotation(rads2degs(angle) + 90);
}

void slime::shoot(const Vector2f mousepos){
    float angle = atan2(mousepos.y - pos.y, mousepos.x - pos.x);
    sprite.setRotation(rads2degs(angle) + 90);
    vel.x = 50*cos(angle);
    vel.y = 50*sin(angle);
}

void slime::reset(const Vector2f pos){
    this->setPosition(pos);
    vel = Vector2f(0.f,0.f);
    bound = 1;
}

bool slime::onCd(){
    return cd;
}

