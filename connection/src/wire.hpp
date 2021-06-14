#include "cell.hpp"
using namespace std;
using namespace sf;

Color on = Color::Red, off = Color(100,0,0);


class wire : public cell{
public:
    wire(unsigned cellsize, Vector2u position) : cell(cellsize, position) {
        this->type = "wire";
        visual.setFillColor(off);       
    }

    void draw(RenderWindow &window) override{
        window.draw(visual);

    }

    void broadcast() override{        

        Vector2u top,bot,left,right;

        top = bot = left = right = pos;
        
        top.y--;
        bot.y++;
        left.x--;
        right.x++;
        
        out = {top, bot, left, right};
        
    }

    void update() override{
        if(charge)
            visual.setFillColor(on);
        else
            visual.setFillColor(off);

        




    }
        
    




};
