#include <vector>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class cell{
public:
    string type;
    Vector2u pos;   
    vector<Vector2u> out;
    bool charge;
    unsigned size;
    bool selected;
    RectangleShape visual;

    virtual void draw(RenderWindow &window){}

    virtual void update(){};

    virtual void broadcast(){};

    cell(unsigned cellsize, Vector2u position) : size(cellsize), charge(0), pos(position), selected(0){
        visual.setSize(Vector2f(size,size));
        visual.setPosition(Vector2f(position*size));
    }

    Vector2f getCenter() const{
        return Vector2f(size/2.f+pos.x,size/2.f+pos.y);
    }


};


