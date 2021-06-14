#include <SFML/Graphics.hpp>
#include <cmath>
using namespace sf;

float dist(Vector2f v){
    return sqrt(v.x*v.x+v.y*v.y); 
}