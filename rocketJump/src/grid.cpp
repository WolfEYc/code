#include "grid.hpp"

void grid::convertToBlock(int &pos){
    pos = (pos / cellsize) * cellsize;
}

bool grid::collides(const Vector2f p1, const Vector2f p2){
     
    for(auto it : blocks){
        lastBounds = it.second.getGlobalBounds();
        if(segmentIntersectsRectangle(lastBounds, p1, p2)){
            lastblock = it.first;
            return true;
        }
    }
    
    return false;
}


void grid::getWalls(const Vector2i block){
    Vector2f topleft ,topright, botright, botleft; 
    topleft = topright = botright = botleft = Vector2f(block);
    topright.x+=cellsize;
    botright.x+=cellsize;
    botright.y+=cellsize;
    botleft.y+=cellsize;

    surface top = make_pair(topleft, topright);
    surface right = make_pair(topright, botright);
    surface bot = make_pair(botleft, botright);
    surface left = make_pair(topleft, botleft);

    lastCollider = {top, right, bot, left};
}

grid::grid(const unsigned cellsize){
    this->cellsize = cellsize;
    this->color = Color::Red;
    this->closest = -1;
    this->lastCollider = vector<surface>(4);
}

void grid::add(Vector2i block){
    convertToBlock(block.x);
    convertToBlock(block.y);

    for(auto it : blocks)
        if(it.first == block)
            return;

    RectangleShape rect(Vector2f(cellsize,cellsize));
    rect.setFillColor(color);
    rect.setPosition(Vector2f(block));
    

    blocks.push_back({block,rect});
}

int grid::collisionSurface(vector<surface> hitreg, Vector2f pos, Vector2f nextpos, const float radius, bool gay){
    for(surface hit : hitreg){
        Vector2f p1s = hit.first;
        Vector2f p2s = hit.second;
        if(collides(p1s, p2s)){
            getWalls(lastblock);
            float closestdist = 9999.f;
            for(int i = 0; i < lastCollider.size(); i++){

                if(segIntersectSeg({p1s, p2s}, lastCollider[i])){
                    Vector2f ipoint = calcIntersectVector(pos, nextpos, lastCollider[i].first, lastCollider[i].second);
                    
                    float length = dist(ipoint - pos);
                    if(length < closestdist){
                        closestdist = length;
                        closest = i % 2;                       
                        if(gay){
                            gaypoint = ipoint;
                        }
                    }
                }
            }
            return closest;
        }
    }
    return -1;
}

Vector2f grid::getGaypoint(){
    return Vector2f(gaypoint);
}

void grid::draw(RenderWindow& window){
    for(auto r : blocks){
        window.draw(r.second);
    }
}
